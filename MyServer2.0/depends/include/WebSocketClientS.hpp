#ifndef _doyou_io_WebSocketClientS_HPP_
#define _doyou_io_WebSocketClientS_HPP_

#include"HttpClientS.hpp"
#include"sha1.hpp"
#include"base64.hpp"
#include"WebSocketObj.hpp"

namespace doyou {
	namespace io {

		//客户端数据类型
		class WebSocketClientS :public HttpClientS
		{
		public:
			WebSocketClientS(SOCKET sockfd = INVALID_SOCKET, int sendSize = SEND_BUFF_SZIE, int recvSize = RECV_BUFF_SZIE) :
				HttpClientS(sockfd, sendSize, recvSize)
			{

			}

			bool handshake()
			{
				auto strUpgrade = this->header_getStr("Upgrade", "");
				if (0 != strcmp(strUpgrade, "websocket"))
				{
					CELLLog_Error("WebSocketClientS::handshake, not found Upgrade:websocket");
					return false;
				}

				auto cKey = this->header_getStr("Sec-WebSocket-Key", nullptr);
				if (!cKey)
				{
					CELLLog_Error("WebSocketClientS::handshake, not found Sec-WebSocket-Key");
					return false;
				}

				std::string sKey = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";

				sKey = cKey + sKey;

				unsigned char strSha1[20] = {};
				SHA1_String((const unsigned char*)sKey.c_str(), sKey.length(), strSha1);

				std::string sKeyAccept = Base64Encode(strSha1, 20);


				char resp[256] = {};
				strcat(resp, "HTTP/1.1 101 Switching Protocols\r\n");
				strcat(resp, "Connection: Upgrade\r\n");
				strcat(resp, "Upgrade: websocket\r\n");
				strcat(resp, "Sec-WebSocket-Accept: ");
				strcat(resp, sKeyAccept.c_str());
				strcat(resp, "\r\n\r\n");

				this->SendData(resp, strlen(resp));

				return true;
			}

			virtual bool hasMsg()
			{
				if (clientState_join == _clientState)
				{
					return HttpClientS::hasMsg();
				}
				else if (clientState_run == _clientState)
				{
					return hasMsgWS();
				}

				return false;
			}

			virtual void pop_front_msg()
			{
				HttpClientS::pop_front_msg();
				if (_wsh.header_size > 0)
				{
					_recvBuff.pop(_wsh.header_size + _wsh.len);
					_wsh.header_size = 0;
					_wsh.len = 0;
				}
				//if (clientState_join == _clientState)
				//{
				//	
				//}
				//else if (clientState_run == _clientState)
				//{
				//}
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

				if ((!_wsh.mask && opcode_PING != _wsh.opcode && opcode_PONG != _wsh.opcode)
					|| opcode_CLOSE == _wsh.opcode)
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
					CELLLog_Error("WebSocketClientS::hasMsgWS -> _wsh.header_size + _wsh.len > _recvBuff.buffSize()");
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

			int writeHeader(WebSocketOpcode opcode, uint64_t len)
			{
				uint8_t header[10] = {};
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

				int ret = SendData((const char*)header, header_size);
				if (SOCKET_ERROR == ret)
				{
					CELLLog_Error("WebSocketClientS::writeHeader -> SendData -> SOCKET_ERROR");
				}
				return ret;
			}

			int writeText(const char* pData, int len)
			{
				int ret = writeHeader(opcode_TEXT, len);
				if (SOCKET_ERROR != ret)
				{
					ret = SendData(pData, len);
					if (SOCKET_ERROR == ret)
					{
						CELLLog_Error("WebSocketClientS::writeText -> SendData -> SOCKET_ERROR");
					}
				}
				return ret;
			}

			int ping()
			{
				return writeHeader(opcode_PING, 0);
			}

			int pong()
			{
				return writeHeader(opcode_PONG, 0);
			}

			WebSocketHeader& WebsocketHeader()
			{
				return _wsh;
			}
		private:
			WebSocketHeader _wsh = {};
		};
	}
}
#endif // !_doyou_io_WebSocketClientS_HPP_
