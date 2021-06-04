#ifndef _doyou_io_HttpClientC_HPP_
#define _doyou_io_HttpClientC_HPP_

#include<map>

#include"Client.hpp"
#include"SplitString.hpp"
#include"KeyString.hpp"

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
				//完整的http请求一定超过20字节
				if (_recvBuff.dataLen() < 20)
					return false;

				int ret = checkHttpResponse();
				//if (ret < 0)
				//	resp400BadRequest();
				return ret > 0;
			}
			// 0 响应的消息不完整 继续等待消息
			// -1 不支持的响应类型
			// -2 异常请求
			int checkHttpResponse()
			{
				//查找http响应消息结束标记
				char* temp = strstr(_recvBuff.data(), "\r\n\r\n");
				//未找到表示消息还不完整
				if (!temp)
					return 0;
				//CELLLog_Info(_recvBuff.data());
				//偏移到消息结束位置
				//4=strlen("\r\n\r\n")
				temp += 4;
				//计算http响应消息的请求行+请求头长度
				_headerLen = temp - _recvBuff.data();
				//判断响应类型是否正确
				temp = _recvBuff.data();
				if (
					temp[0] == 'H' &&
					temp[1] == 'T' &&
					temp[2] == 'T' &&
					temp[3] == 'P')
				{
					//Log::Info("%s", _recvBuff.data());
					//计算响应体长度
					char* p1 = strstr(_recvBuff.data(), "Content-Length: ");
					//未找到表示格式错误
					//返回错误码或者直接关闭客户端连接
					if (!p1)
						return -2;
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
					//所以数据长度上限是接收缓冲区大小减去_headerLen
					if (n > 6)
						return -2;
					char lenStr[7] = {};
					strncpy(lenStr, p1, n);
					_bodyLen = atoi(lenStr);
					//数据异常
					if(_bodyLen < 0)
						return -2;
					//响应数据超过了缓冲区可接收长度
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

			
			//解析http响应
			//确定收到完整http响应消息的时候才能调用
			bool getRequestInfo()
			{
				//判断是否已经收到了完整请求
				if (_headerLen <= 0)
					return false;
				//清除上一个消息请求的数据
				_header_map.clear();

				char* pp = _recvBuff.data();
				pp[_headerLen-1] = '\0';
				SplitString ss;
				ss.set(_recvBuff.data());
				//请求行示例："GET /login.php?a=5 HTTP/1.1\r\n"
				char* temp = ss.get("\r\n");
				if (temp)
				{
					_header_map["RequestLine"] = temp;
					request_args(temp);
				}

				//请求头示例："Connection: Keep-Alive\r\n"
				while (true)
				{
					//请求头每一行都有一个\r\n
					temp = ss.get("\r\n");
					if (temp)
					{
						//"Connection: Keep-Alive\0\n"
						SplitString ss2;
						ss2.set(temp);
						//每个请求头字段都是"key: val\r\n"
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
					//_args_map.clear();
					//SplitUrlArgs(_recvBuff.data() + _headerLen);
					_args_map["Content"] = _recvBuff.data() + _headerLen;
				}
				//根据请求头，做出相应处理
				const char* str = header_getStr("Connection", "");
				_keepalive = (0 == strcmp("keep-alive", str) || 0 == strcmp("Keep-Alive", str));
				
				return true;
			}
			//解析响应内容
			//可以是html页面
			//不过我们只要能解析http api返回的json或者其它格式的字符串数据就可以了
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

			bool request_args(char* requestLine)
			{
				//requestLine="GET /login.php?a=5 HTTP/1.1"
				SplitString ss;
				ss.set(requestLine);
				//requestLine="GET\0/login.php?a=5 HTTP/1.1"
				_method = ss.get(' ');
				if (!_method)
					return false;

				_url = ss.get(' ');
				if (!_url)
					return false;

				_httpVersion = ss.get(' ');
				if (!_httpVersion)
					return false;

				ss.set(_url);
				_url_path = ss.get('?');
				if (!_url_path)
					return false;

				_url_args = ss.get('?');
				if (!_url_args)
					return true;

				_args_map.clear();
				SplitUrlArgs(_url_args);

				return true;
			}

			virtual void pop_front_msg()
			{
				if (_headerLen > 0)
				{
					_recvBuff.pop(_headerLen + _bodyLen);
					_headerLen = 0;
					_bodyLen = 0;
				}
			}

			bool canWrite(int size)
			{
				return _sendBuff.canWrite(size);
			}

			void resp400BadRequest()
			{
				writeResponse("400 Bad Request", "Only support GET or POST.", 25);
			}

			void resp404NotFound()
			{
				writeResponse("404 Not Found", "(^o^): 404!", 11);
			}

			void resp200OK(const char* bodyBuff, int bodyLen)
			{
				writeResponse("200 OK", bodyBuff, bodyLen);
			}

			void writeResponse(const char* code, const char* bodyBuff, int bodyLen)
			{
				//响应体内存长度
				char respBodyLen[32] = {};
				sprintf(respBodyLen, "Content-Length: %d\r\n", bodyLen);
				//响应行+响应头缓冲区 256字节足够了
				char response[256] = {};
				//响应行
				strcat(response, "HTTP/1.1 ");
				strcat(response, code);
				strcat(response, "\r\n");
				//响应头
				strcat(response, "Content-Type: text/html;charset=UTF-8\r\n");
				strcat(response, "Access-Control-Allow-Origin: *\r\n");
				strcat(response, respBodyLen);
				strcat(response, "\r\n");
				//发送响应体
				SendData(response, strlen(response));
				SendData(bodyBuff, bodyLen);
			}

			char* url()
			{
				return _url_path;
			}

			bool url_compre(const char* str)
			{
				return 0 == strcmp(_url_path, str);
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
				if (itr == _args_map.end())
				{
					//CELLLog_Error("Config::getStr not find <%s>", argName);
				}
				else {
					def = atoi(itr->second);
				}
				//CELLLog_Info("Config::getInt %s=%d", argName, def);
				return def;
			}

			const char* args_getStr(const char* argName, const char* def)
			{
				auto itr = _args_map.find(argName);
				if (itr != _args_map.end())
				{
					return itr->second;
				}
				else {
					return def;
				}
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

			virtual void onSendComplete()
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
			char* _method;
			char* _url;
			char* _url_path;
			char* _url_args;
			char* _httpVersion;
			bool _keepalive = true;
		};
	}
}
#endif // !_doyou_io_HttpClientC_HPP_
