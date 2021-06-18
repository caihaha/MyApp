#ifndef _doyou_io_TcpWebSocketServer_HPP_
#define _doyou_io_TcpWebSocketServer_HPP_

#include"TcpServerMgr.hpp"
#include"WebSocketClientS.hpp"

namespace doyou {
	namespace io {
		class TcpWebSocketServer :public TcpServerMgr
		{
			virtual Client* makeClientObj(SOCKET cSock)
			{
				return new WebSocketClientS(cSock, _nSendBuffSize, _nRecvBuffSize);
			}

			virtual void OnNetMsg(Server* pServer, Client* pClient, netmsg_DataHeader* header)
			{
				TcpServer::OnNetMsg(pServer, pClient, header);
				WebSocketClientS* pWSClient = dynamic_cast<WebSocketClientS*>(pClient);
				if (!pWSClient)
					return;

				pWSClient->resetDTHeart();

				if (clientState_join == pWSClient->state())
				{	
					//握手
					if (!pWSClient->getRequestInfo())
						return;

					if (pWSClient->handshake())
						pWSClient->state(clientState_run);
					else
						pWSClient->onClose();
				}
				else if (clientState_run == pWSClient->state()) {
					WebSocketHeader& wsh = pWSClient->WebsocketHeader();
					if (wsh.opcode == opcode_PING)
					{
						pWSClient->pong();
					}
					else {
						//处理数据帧
						OnNetMsgWS(pServer, pWSClient);
					}
				}
			}
		public:
			virtual void OnNetMsgWS(Server* pServer, WebSocketClientS* pWSClient)
			{

			}
		};
	}
}
#endif // !_doyou_io_TcpWebSocketServer_HPP_
