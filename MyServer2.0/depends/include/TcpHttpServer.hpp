#ifndef _doyou_io_TcpHttpServer_HPP_
#define _doyou_io_TcpHttpServer_HPP_

#include"TcpServerMgr.hpp"
#include"HttpClientS.hpp"

namespace doyou {
	namespace io {
		class TcpHttpServer :public TcpServerMgr
		{
			virtual Client* makeClientObj(SOCKET cSock)
			{
				return new HttpClientS(cSock, _nSendBuffSize, _nRecvBuffSize);
			}

			virtual void OnNetMsg(Server* pServer, Client* pClient, netmsg_DataHeader* header)
			{
				TcpServer::OnNetMsg(pServer, pClient, header);
				HttpClientS* pHttpClient = dynamic_cast<HttpClientS*>(pClient);
				if (!pHttpClient)
					return;

				if (!pHttpClient->getRequestInfo())
					return;

				pHttpClient->resetDTHeart();

				OnNetMsgHttp(pServer, pHttpClient);
			}
		public:
			virtual void OnNetMsgHttp(Server* pServer, HttpClientS* pHttpClient)
			{

			}
		};
	}
}
#endif // !_doyou_io_TcpHttpServer_HPP_
