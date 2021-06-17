#ifndef _doyou_io_TcpWebSocketClient_HPP_
#define _doyou_io_TcpWebSocketClient_HPP_

#include"TcpClientMgr.hpp"
#include"WebSocketClientC.hpp"

#include"sha1.hpp"
#include"base64.hpp"

#include<queue>

namespace doyou {
	namespace io {
		class TcpWebSocketClient :public TcpClientMgr
		{
		public:
			TcpWebSocketClient()
			{
				NetWork::Init();
			}
		protected:
			virtual Client* makeClientObj(SOCKET cSock, int sendSize, int recvSize)
			{
				_pWSClient = new WebSocketClientC(cSock, sendSize, recvSize);
				return _pWSClient;
			}

			virtual void OnDisconnect() {
				if (onclose)
				{
					//WebSocketClientC* pWSClient = dynamic_cast<WebSocketClientC*>(_pClient);
					if(_pWSClient)
						onclose(_pWSClient);
				}
			};
		public:
			virtual void OnNetMsg(netmsg_DataHeader* header)
			{
				WebSocketClientC* pWSClient = dynamic_cast<WebSocketClientC*>(_pClient);
				if (!pWSClient)
					return;

				if (clientState_join == pWSClient->state())
				{
					if (!pWSClient->getResponseInfo())
						return;

					if (handshake())
					{
						CELLLog_Info("WebSocketClientC::handshake, Good.");
						pWSClient->state(clientState_run);

						if (onopen)
						{
							onopen(pWSClient);
						}
					}
					else {
						CELLLog_Warring("WebSocketClientC::handshake, Bad.");
						pWSClient->onClose();
						if (onerror)
						{
							onerror(pWSClient);
						}
					}
				}
				else if (clientState_run == pWSClient->state()) {
					WebSocketHeader& wsh = pWSClient->WebsocketHeader();
					if (wsh.opcode == opcode_PING)
					{
						pWSClient->pong();
					}
					else {
						//处理数据帧
						if (onmessage)
						{
							onmessage(pWSClient);
						}
					}
				}
			}

			bool handshake()
			{

				WebSocketClientC* pWSClient = dynamic_cast<WebSocketClientC*>(_pClient);
				if (!pWSClient)
					return false;

				auto strUpgrade = pWSClient->header_getStr("Upgrade", "");
				if (0 != strcmp(strUpgrade, "websocket"))
				{
					CELLLog_Error("WebSocketClientC::handshake, not found Upgrade:websocket");
					return false;
				}

				auto sKeyAccept = pWSClient->header_getStr("Sec-WebSocket-Accept", nullptr);
				if (!sKeyAccept)
				{
					CELLLog_Error("WebSocketClientC::handshake, not found Sec-WebSocket-Key");
					return false;
				}

				std::string cKeyAccept = _cKey + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";

				unsigned char strSha1[20] = {};
				SHA1_String((const unsigned char*)cKeyAccept.c_str(), cKeyAccept.length(), strSha1);

				cKeyAccept = Base64Encode(strSha1, 20);

				if (cKeyAccept != sKeyAccept)
				{
					CELLLog_Error("WebSocketClientC::handshake, cKeyAccept != sKeyAccept!");
					return false;
				}
				return true;
			}

			bool connect(const char* httpurl)
			{
				deatch_http_url(httpurl);
				if (0 == hostname2ip(_host.c_str(), _port.c_str()))
				{
					_pClient->state(clientState_join);

					_cKey = "1234567890123456";
					_cKey = Base64Encode((const unsigned char*)_cKey.c_str(), _cKey.length());

					url2get(_host.c_str(), _path.c_str(), _args.c_str());
					return true;
				}
				return false;
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
				if (isRun())
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
							return 0;
						}
					}
				}

				freeaddrinfo(pAddrList);
				return -1;
			}

			int writeText(const char* pData, int len)
			{
				if (_pWSClient)
					return _pWSClient->writeText(pData, len);
				return 0;
			}

			void send_buff_size(int n)
			{
				_nSendBuffSize = n;
			}

			void recv_buff_size(int n)
			{
				_nRecvBuffSize = n;
			}
		private:
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

				//msg += "Connection: keep-alive\r\n";
				msg += "Accept: */*\r\n";

				msg += "Origin: ";
				msg += host;
				msg += "\r\n";
				////
				msg += "Connection: Upgrade\r\n";
				msg += "Upgrade: websocket\r\n";
				msg += "Sec-WebSocket-Version: 13\r\n";

				msg += "Sec-WebSocket-Key: ";
				msg += _cKey;
				msg += "\r\n";
				////

				msg += "\r\n";

				SendData(msg.c_str(), msg.length());
			}

			bool connet2ip(int af, const char* ip, unsigned short port)
			{
				if (!ip)
					return false;

				if (INVALID_SOCKET == InitSocket(af, _nSendBuffSize, _nRecvBuffSize))
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
			////
			std::string _cKey;
			//
			WebSocketClientC* _pWSClient = nullptr;
			//客户端发送缓冲区大小
			int _nSendBuffSize = SEND_BUFF_SZIE;
			//客户端接收缓冲区大小
			int _nRecvBuffSize = RECV_BUFF_SZIE;
		public:
			typedef std::function<void(WebSocketClientC*)> EventCall;
			EventCall onopen = nullptr;
			EventCall onclose = nullptr;
			EventCall onmessage = nullptr;
			EventCall onerror = nullptr;
		};
	}
}
#endif // !_doyou_io_TcpWebSocketClient_HPP_
