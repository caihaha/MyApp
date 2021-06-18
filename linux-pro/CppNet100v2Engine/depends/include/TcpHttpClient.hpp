#ifndef _doyou_io_TcpHttpClient_HPP_
#define _doyou_io_TcpHttpClient_HPP_

#include"TcpClientMgr.hpp"
#include"HttpClientC.hpp"

#include<queue>

namespace doyou {
	namespace io {
		class TcpHttpClient :public TcpClientMgr
		{
		public:
			TcpHttpClient()
			{
				NetWork::Init();
			}
		protected:
			virtual Client* makeClientObj(SOCKET cSock, int sendSize, int recvSize)
			{
				return new HttpClientC(cSock, sendSize, recvSize);
			}
		private:
			typedef std::function<void(HttpClientC*)> EventCall;

			struct Event {
				std::string httpurl;
				EventCall onRespCall = nullptr;
				bool isGet = true;
				uint8_t qusetCount= 0;
				uint8_t maxQusetCount = 1;
			};

			std::queue<Event> _eventQueue;
			bool _b_nextRequest = false;
		public:
			virtual bool OnRun(int microseconds = 1)
			{
				if(_b_nextRequest)
					nextRequest();

				return TcpClientMgr::OnRun(microseconds);
			}

			virtual void OnNetMsg(netmsg_DataHeader* header)
			{
				HttpClientC* pHttpClient = dynamic_cast<HttpClientC*>(_pClient);
				if (!pHttpClient)
					return;

				if (!pHttpClient->getResponseInfo())
					return;

				if (_onRespCall)
				{
					_onRespCall(pHttpClient);
					_onRespCall = nullptr;
				}

				pHttpClient->onRecvComplete();

				if (!_eventQueue.empty())
					_eventQueue.pop();

				_b_nextRequest = true;
			}

			virtual void OnDisconnect() {
				if (_onRespCall)
				{
					_onRespCall(nullptr);
					_onRespCall = nullptr;
				}

				_b_nextRequest = true;
			};

			void get(const char* httpurl, EventCall onRespCall)
			{
				Event e;
				e.httpurl = httpurl;
				e.onRespCall = onRespCall;
				e.isGet = true;
				_eventQueue.push(e);

				_b_nextRequest = true;
			}

			void post(const char* httpurl, EventCall onRespCall)
			{
				Event e;
				e.httpurl = httpurl;
				e.onRespCall = onRespCall;
				e.isGet = false;
				_eventQueue.push(e);

				_b_nextRequest = true;
			}

			void post(const char* httpurl, const char* dataStr, EventCall onRespCall)
			{
				std::string httpurl_ = httpurl;
				httpurl_ += '?';
				httpurl_ += dataStr;
				post(httpurl_.c_str(), onRespCall);
			}

			int hostname2ip(const char* hostname, const char* port)
			{
				if (!hostname)
				{
					Log::Warring("hostname2ip(hostname is null ptr).");
					return -1;
				}

				if (!port)
				{
					Log::Warring("hostname2ip(port is null ptr).");
					return -1;
				}

				unsigned short port_ = 80;
				if (port, strlen(port) > 0)
					port_ = atoi(port);

				//主机名和端口号不变，就不重新连接服务端
				if (isRun() && _host0 == hostname && port_ == _port0)
					return 0;

				addrinfo hints = {};
				hints.ai_family = AF_UNSPEC;
				hints.ai_socktype = SOCK_STREAM;
				hints.ai_protocol = IPPROTO_IP;
				hints.ai_flags = AI_ALL;
				addrinfo* pAddrList = nullptr;
				int ret = getaddrinfo(hostname, nullptr, &hints, &pAddrList);
				if (0 != ret)
				{
					Log::PError("%s getaddrinfo", hostname);
					freeaddrinfo(pAddrList);
					return ret;
				}

				char ipStr[256] = {};
				for (auto pAddr = pAddrList; pAddr != nullptr; pAddr = pAddr->ai_next)
				{
					ret = getnameinfo(pAddr->ai_addr, pAddr->ai_addrlen, ipStr, 255, nullptr, 0, NI_NUMERICHOST);
					if (0 != ret)
					{
						Log::PError("%s getnameinfo", hostname);
						continue;
					}
					else {
						if (pAddr->ai_family == AF_INET6)
							Log::Info("%s ipv6: %s", hostname, ipStr);
						else if (pAddr->ai_family == AF_INET)
							Log::Info("%s ipv4: %s", hostname, ipStr);
						else {
							Log::Info("%s addr: %s", hostname, ipStr);
							continue;
						}

						if (connet2ip(pAddr->ai_family, ipStr, port_))
						{
							_host0 = _host;
							_port0 = port_;
							break;
						}
					}
				}

				freeaddrinfo(pAddrList);
				return ret;
			}

		private:
			void nextRequest()
			{
				_b_nextRequest = false;
				if (!_eventQueue.empty())
				{
					Event& e = _eventQueue.front();

					++e.qusetCount;
					if (e.qusetCount > e.maxQusetCount)
					{
						_eventQueue.pop();
						_b_nextRequest = true;
						return;
					}

					if (e.isGet)
					{
						deatch_http_url(e.httpurl);
						if (0 == hostname2ip(_host.c_str(), _port.c_str()))
						{
							url2get(_host.c_str(), _path.c_str(), _args.c_str());
							_onRespCall = e.onRespCall;
						}
					}
					else
					{
						deatch_http_url(e.httpurl);
						if (0 == hostname2ip(_host.c_str(), _port.c_str()))
						{
							url2post(_host.c_str(), _path.c_str(), _args.c_str());
							_onRespCall = e.onRespCall;
						}
					}
				}
			}

			void url2get(const char* host, const char* path, const char* args)
			{
				std::string msg = "GET ";

				if (path && strlen(path) > 0)
					msg += path;
				else
					msg += "/";

				if (args && strlen(args) > 0)
				{
					msg += "?";
					msg += args;
				}

				msg += " HTTP/1.1\r\n";

				msg += "Host: ";
				msg += host;
				msg += "\r\n";

				msg += "Connection: keep-alive\r\n";
				msg += "Accept: */*\r\n";

				msg += "Origin: ";
				msg += host;
				msg += "\r\n";

				msg += "\r\n";

				SendData(msg.c_str(), msg.length());
			}

			void url2post(const char* host, const char* path, const char* args)
			{
				std::string msg = "POST ";

				if (path && strlen(path) > 0)
					msg += path;
				else
					msg += "/";

				msg += " HTTP/1.1\r\n";

				msg += "Host: ";
				msg += host;
				msg += "\r\n";

				msg += "Connection: keep-alive\r\n";
				msg += "Accept: */*\r\n";

				msg += "Origin: ";
				msg += host;
				msg += "\r\n";

				int bodyLen = 0;
				if (args)
				{
					bodyLen = strlen(args);
				}

				char reqBodyLen[32] = {};
				sprintf(reqBodyLen, "Content-Length: %d\r\n", bodyLen);
				msg += reqBodyLen;

				msg += "\r\n";

				if (bodyLen > 0)
				{
					msg += args;
				}

				SendData(msg.c_str(), msg.length());
			}

			bool connet2ip(int af, const char* ip, unsigned short port)
			{
				if (!ip)
					return false;

				if (INVALID_SOCKET == InitSocket(af, 10240, 102400))
					return false;

				if (SOCKET_ERROR == Connect(ip, port))
					return false;

				CELLLog_Info("connet2ip(%s,%d)", ip, port);
				return true;
			}

			void deatch_http_url(std::string httpurl)
			{
				_httpType.clear();
				_host.clear();
				_port.clear();
				_path.clear();
				_args.clear();

				auto pos1 = httpurl.find("://");
				if (pos1 != std::string::npos)
				{
					_httpType = httpurl.substr(0, pos1);
					pos1 += 3;
				}
				else {
					pos1 = 0;
				}
				auto pos2 = httpurl.find('/', pos1);
				if (pos2 != std::string::npos)
				{
					_host = httpurl.substr(pos1, pos2 - pos1);
					_path = httpurl.substr(pos2);

					pos1 = _path.find('?');
					if (pos1 != std::string::npos)
					{
						_args = _path.substr(pos1 + 1);
						_path = _path.substr(0, pos1);
					}
				}
				else {
					_host = httpurl.substr(pos1);
				}

				pos1 = _host.find(':');
				if (pos1 != std::string::npos)
				{
					_port = _host.substr(pos1 + 1);
					_host = _host.substr(0, pos1);
				}
			}
		private:
			std::string _httpType;
			std::string _host;
			std::string _port;
			std::string _path;
			std::string _args;
			//上一次请求的域名/主机名
			std::string _host0;
			//上一次请求的端口号
			unsigned short _port0;

			EventCall _onRespCall = nullptr;

		};
	}
}
#endif // !_doyou_io_TcpHttpClient_HPP_
