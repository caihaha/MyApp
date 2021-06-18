#ifndef _doyou_io_HttpClientC_HPP_
#define _doyou_io_HttpClientC_HPP_

#include"Client.hpp"
#include"SplitString.hpp"
#include"KeyString.hpp"
#include<map>

namespace doyou {
	namespace io {
		//客户端数据类型
		class HttpClientC:public Client
		{
		public:
			HttpClientC(SOCKET sockfd = INVALID_SOCKET, int sendSize = SEND_BUFF_SZIE, int recvSize = RECV_BUFF_SZIE) :
				Client(sockfd, sendSize,recvSize)
			{

			}

			virtual bool hasMsg()
			{
				//完整的http消息一定超过20字节
				if (_recvBuff.dataLen() < 20)
					return false;

				int ret = checkHttpResponse();
				if (ret < 0)
					CELLLog_Info("HttpClientC: checkHttpResponse error msg.");
				return ret > 0;
			}
			// 0 消息不完整 继续等待消息
			// -1 不支持的消息类型
			// -2 异常消息
			int checkHttpResponse()
			{
				//查找http消息结束标记
				char* temp = strstr(_recvBuff.data(), "\r\n\r\n");
				//未找到表示消息还不完整
				if (!temp)
					return 0;
				//CELLLog_Info(_recvBuff.data());
				//偏移到消息结束位置
				//4=strlen("\r\n\r\n")
				temp += 4;
				//计算http响应消息的响应行+响应头长度
				_headerLen = temp - _recvBuff.data();
				//判断响应类型是否支持
				temp = _recvBuff.data();
				if (
					temp[0] == 'H' &&
					temp[1] == 'T' &&
					temp[2] == 'T' &&
					temp[3] == 'P')
				{
					//需要计算响应体长度
					char* p1 = strstr(_recvBuff.data(), "Content-Length: ");
					if (p1)
					{
						//Content-Length: 1024\r\n
						//16=strlen("Content-Length: ")
						p1 += 16;
						char* p2 = strchr(p1, '\r');
						if (!p2)
							return -2;
						//计算数字长度
						int n = p2 - p1;
						//6位数 99万9999 上限100万字节， 就是1MB
						//我们目前是靠接收缓冲区一次性接收
						//所以数据上限是接收缓冲区大小减去_headerLen
						if (n > 6)
							return -2;
						char lenStr[7] = {};
						strncpy(lenStr, p1, n);
						_bodyLen = atoi(lenStr);
						//数据异常
						if (_bodyLen < 0)
							return -2;
					}
					//消息数据超过了缓冲区可接收长度
					if (_headerLen + _bodyLen > _recvBuff.buffSize())
						return -2;
					//消息长度>已接收的数据长度，那么数据还没接收完
					if (_headerLen + _bodyLen > _recvBuff.dataLen())
						return 0;
				}
				else {
					return -1;
				}

				return _headerLen;
			}

			
			//解析http消息
			//确定收到完整http消息的时候才能调用
			bool getResponseInfo()
			{
				//判断是否已经收到了完整消息
				if (_headerLen <= 0)
					return false;
				
				char* pp = _recvBuff.data();
				pp[_headerLen-1] = '\0';

				SplitString ss;
				ss.set(_recvBuff.data());
				//响应行示例："HTTP/1.1 200 OK\r\n"
				char* temp = ss.get("\r\n");
				if (temp)
				{
					_header_map["ResponseLine"] = temp;
				}

				//响应头示例："Connection: Keep-Alive\r\n"
				while (true)
				{
					//响应头每一行都有一个\r\n
					temp = ss.get("\r\n");
					if (temp)
					{
						//"Connection: Keep-Alive\0\n"
						SplitString ss2;
						ss2.set(temp);
						//每个响应头字段都是"key: val\r\n"
						char* key = ss2.get(": ");
						char* val = ss2.get(": ");
						if (key && val)
						{
							//key = Connection
							//val = Keep-Alive
							_header_map[key] = val;
						}
					}
					else {
						break;
					}
				}

				//响应体
				if (_bodyLen > 0)
				{
					_args_map["Content"] = _recvBuff.data() + _headerLen;
				}
				//根据字段，做出相应处理
				const char* str = header_getStr("Connection", "");
				_keepalive = (0 == strcmp("keep-alive", str) || 0 == strcmp("Keep-Alive", str) || 0 == strcmp("Upgrade", str));
				
				return true;
			}
			
			//解析url参数内容
			//可以是html页面
			//不过呢，我们只要能解析http api返回的json文本字符串
			//或者其它格式的字符串数据就可以了，例如xml格式
			void SplitUrlArgs(char* args)
			{
				SplitString ss;
				ss.set(args);
				while (true)
				{
					char* temp = ss.get('&');
					if (temp)
					{
						SplitString ss2;
						ss2.set(temp);
						char* key = ss2.get('=');
						char* val = ss2.get('=');
						if (key && val)
							_args_map[key] = val;
					}
					else {
						break;
					}
				}
			}

			virtual void pop_front_msg()
			{
				if (_headerLen > 0)
				{
					_recvBuff.pop(_headerLen + _bodyLen);
					_headerLen = 0;
					_bodyLen = 0;
					//清除本次消息请求的数据
					_args_map.clear();
					_header_map.clear();
				}
			}

			bool has_args(const char* key)
			{
				return _args_map.find(key) != _args_map.end();
			}

			bool has_header(const char* key)
			{
				return _header_map.find(key) != _header_map.end();
			}

			int args_getInt(const char* argName, int def)
			{
				auto itr = _args_map.find(argName);
				if (itr != _args_map.end())
				{
					def = atoi(itr->second);
				}
				return def;
			}

			const char* args_getStr(const char* argName, const char* def)
			{
				auto itr = _args_map.find(argName);
				if (itr != _args_map.end())
				{
					return itr->second;
				}
				return def;
			}

			const char* header_getStr(const char* argName, const char* def)
			{
				auto itr = _header_map.find(argName);
				if (itr != _header_map.end())
				{
					return itr->second;
				}
				else {
					return def;
				}
			}

			virtual void onRecvComplete()
			{
				if (!_keepalive)
				{
					this->onClose();
				}
			}

			const char* content()
			{
				return args_getStr("Content", nullptr);
			}

		protected:
			int _headerLen = 0;
			int _bodyLen = 0;
			std::map<KeyString, char*> _header_map;
			std::map<KeyString, char*> _args_map;
			bool _keepalive = true;
		};
	}
}
#endif // !_doyou_io_HttpClientC_HPP_
