#ifndef _doyou_io_WebSocketClientC_HPP_
#define _doyou_io_WebSocketClientC_HPP_

#include"HttpClientC.hpp"
#include"sha1.hpp"
#include"base64.hpp"
#include"WebSocketObj.hpp"

namespace doyou {
	namespace io {

		//客户端数据类型
		class WebSocketClientC :public HttpClientC
		{
		public:
			WebSocketClientC(SOCKET sockfd = INVALID_SOCKET, int sendSize = SEND_BUFF_SZIE, int recvSize = RECV_BUFF_SZIE) :
				HttpClientC(sockfd, sendSize, recvSize)
			{

			}

			virtual bool hasMsg()
			{
				if (clientState_join == _clientState)
				{
					return HttpClientC::hasMsg();
				}
				else if (clientState_run == _clientState)
				{
					return hasMsgWS();
				}

				return false;
			}

			virtual void pop_front_msg()
			{
				HttpClientC::pop_front_msg();
				if (_wsh.header_size > 0)
				{
					_recvBuff.pop(_wsh.header_size + _wsh.len);
					_wsh.header_size = 0;
					_wsh.len = 0;
				}
			}

			virtual bool hasMsgWS()
			{
				//完整的WebSocket数据帧头部数据一定不小于2字节
				if (_recvBuff.dataLen() < 2)
					return false;
				//将数据转化为无符号整数数据
				const uint8_t *data = (const uint8_t *)_recvBuff.data();
				//
				_wsh.header_size = 2;
				_wsh.fin = ((data[0] & 0x80) == 0x80);
				//
				_wsh.opcode = static_cast<WebSocketOpcode>(data[0] & 0xF);
				//
				_wsh.mask = ((data[1] & 0x80) == 0x80);
				if (_wsh.mask)
				{
					_wsh.header_size += 4;
				}
				//
				if (opcode_CLOSE == _wsh.opcode)
				{
					onClose();
					return true;
				}
				//
				_wsh.len0 = (data[1] & 0x7F);

				if (_wsh.len0 == 126)
				{
					_wsh.header_size += 2;
				}
				else if (_wsh.len0 == 127)
				{
					_wsh.header_size += 8;
				}

				//数据帧头部数据一定不小于header_size字节
				if (_recvBuff.dataLen() < _wsh.header_size)
					return false;

				//
				if (_wsh.len0 == 126)
				{
					//_wsh.len = 0
					//0000 0000 0000 0000

					//0000 1111 0000 0000
					_wsh.len |= data[2] << 8;
					//0000 1111 0000 0000

					//0000 0000 0000 1111
					_wsh.len |= data[3] << 0;
					//0000 1111 0000 1111
				}
				else if (_wsh.len0 == 127)
				{
					_wsh.len |= (uint64_t)data[2] << 56;
					_wsh.len |= (uint64_t)data[3] << 48;
					_wsh.len |= (uint64_t)data[4] << 40;
					_wsh.len |= (uint64_t)data[5] << 32;
					_wsh.len |= data[6] << 24;
					_wsh.len |= data[7] << 16;
					_wsh.len |= data[8] << 8;
					_wsh.len |= data[9] << 0;
				}
				else {
					_wsh.len = _wsh.len0;
				}
				//消息数据超过了缓冲区可接收长度
				if (_wsh.header_size + _wsh.len > _recvBuff.buffSize())
				{
					CELLLog_Error("WebSocketClientC::hasMsgWS -> _wsh.header_size + _wsh.len > _recvBuff.buffSize()");
					onClose();
					return false;
				}
				//判断数据收完没有
				if(_recvBuff.dataLen() < _wsh.header_size + _wsh.len)
					return false;

				return true;
			}

			char * fetch_data()
			{
				char *rbuf = _recvBuff.data() + _wsh.header_size;

				//将数据转化为无符号整数数据
				if (_wsh.mask)
				{
					const uint8_t *data = (const uint8_t *)_recvBuff.data();
					_wsh.masking_key[0] = data[_wsh.header_size - 4];
					_wsh.masking_key[1] = data[_wsh.header_size - 3];
					_wsh.masking_key[2] = data[_wsh.header_size - 2];
					_wsh.masking_key[3] = data[_wsh.header_size - 1];

					for (uint64_t i = 0; i < _wsh.len; ++i)
					{
						rbuf[i] ^= _wsh.masking_key[i & 0x3];
					}
				}

				return rbuf;
			}

			void do_mask(int len)
			{
				if (_sendBuff.dataLen() < len)
					return;

				char *rbuf = _sendBuff.data() + (_sendBuff.dataLen() - len);
				const uint8_t * masking_key = (const uint8_t *) &_mask_key;
				for (int i = 0; i < len; i++)
				{
					rbuf[i] ^= masking_key[i & 0x3];
				}
			}

			int writeHeader(WebSocketOpcode opcode, uint64_t len, bool mask, int32_t mask_key)
			{
				uint8_t header[14] = {};
				uint8_t header_size = 0;

				if (len < 126)
				{
					header_size = 2;
				}
				else if (len < 65536) {
					header_size = 4;
				}
				else {
					header_size = 10;
				}
				//FIN | opcode;
				header[0] = 0x80 | opcode;

				if (len < 126)
				{
					header[1] = (len & 0x7F);
				}
				else if (len < 65536) {

					header[1] = 126;
					//1111 1011 1111 1111
					//1111 1011
					header[2] = (len >> 8) & 0xFF;
					//1111 1011 1111 1111
					header[3] = (len >> 0) & 0xFF;
				}
				else {
					header[1] = 127;
					header[2] = (len >> 56) & 0xFF;
					header[3] = (len >> 48) & 0xFF;
					header[4] = (len >> 40) & 0xFF;
					header[5] = (len >> 32) & 0xFF;
					header[6] = (len >> 24) & 0xFF;
					header[7] = (len >> 16) & 0xFF;
					header[8] = (len >> 8) & 0xFF;
					header[9] = (len >> 0) & 0xFF;
				}

				if (mask)
				{
					_mask_key = rand();
					header[1] |= 0x80;
					header_size += 4;
					const uint8_t * masking_key = (const uint8_t *)&_mask_key;
					header[header_size - 4] = masking_key[0];
					header[header_size - 3] = masking_key[1];
					header[header_size - 2] = masking_key[2];
					header[header_size - 1] = masking_key[3];
				}

				int ret = SendData((const char*)header, header_size);
				if (SOCKET_ERROR == ret)
				{
					CELLLog_Error("WebSocketClientC::writeHeader -> SendData -> SOCKET_ERROR");
				}
				return ret;
			}

			int writeText(const char* pData, int len)
			{
				int ret = writeHeader(opcode_TEXT, len, true, _mask_key);
				if (SOCKET_ERROR != ret)
				{
					ret = SendData(pData, len);
					if (SOCKET_ERROR == ret)
					{
						CELLLog_Error("WebSocketClientC::writeText -> SendData -> SOCKET_ERROR");
						return ret;
					}
					do_mask(len);
				}
				return ret;
			}

			int ping()
			{
				return writeHeader(opcode_PING, 0, false, 0);
			}

			int pong()
			{
				return writeHeader(opcode_PONG, 0, false, 0);
			}

			WebSocketHeader& WebsocketHeader()
			{
				return _wsh;
			}
		private:
			WebSocketHeader _wsh = {};
			int32_t _mask_key = rand();
		};
	}
}
#endif // !_doyou_io_WebSocketClientC_HPP_
