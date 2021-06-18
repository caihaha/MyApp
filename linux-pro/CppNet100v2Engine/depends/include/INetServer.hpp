#ifndef _doyou_io_INetServer_HPP_
#define _doyou_io_INetServer_HPP_

#include"TcpWebSocketServer.hpp"
#include "CJsonObject.hpp"
#include"INetClientS.hpp"

namespace doyou {
	namespace io {
		class INetServer :public TcpWebSocketServer
		{
		private:
			typedef std::function<void(Server*, INetClientS*, neb::CJsonObject&)> NetEventCall;
			std::map<std::string, NetEventCall> _map_msg_call;
		public:
			std::function<void(Server*, INetClientS*, std::string&, neb::CJsonObject&)> on_other_msg = nullptr;
			std::function<void(INetClientS*)> on_client_leave = nullptr;
		private:
			virtual Client* makeClientObj(SOCKET cSock)
			{
				return new INetClientS(cSock, _nSendBuffSize, _nRecvBuffSize);
			}

			virtual void OnNetMsg(Server* pServer, Client* pClient, netmsg_DataHeader* header)
			{
				TcpServer::OnNetMsg(pServer, pClient, header);
				INetClientS* pWSClient = dynamic_cast<INetClientS*>(pClient);
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

			//virtual void OnNetJoin(Client* pClient)
			//{
			//	TcpServer::OnNetJoin(pClient);
			//}

			virtual void OnNetLeave(Client* pClient)
			{
				TcpServer::OnNetLeave(pClient);

				INetClientS* pWSClient = dynamic_cast<INetClientS*>(pClient);
				if (!pWSClient)
					return;

				if (on_client_leave)
					on_client_leave(pWSClient);
			}
		public:
			virtual void OnNetMsgWS(Server* pServer, INetClientS* pWSClient)
			{
				WebSocketHeader& wsh = pWSClient->WebsocketHeader();
				if (wsh.opcode == opcode_PONG)
				{
					//CELLLog_Info("websocket client say: PONG");
					return;
				}
				auto dataStr = pWSClient->fetch_data();
				//CELLLog_Info("websocket client say: %s", dataStr);

				neb::CJsonObject json;
				if (!json.Parse(dataStr))
				{
					CELLLog_Error("json.Parse error : %s", json.GetErrMsg().c_str());
					return;
				}

				int msgId = 0;
				if (!json.Get("msgId", msgId))
				{
					CELLLog_Error("not found key<%s>.", "msgId");
					return;
				}

				int64 time = 0;
				if (!json.Get("time", time))
				{
					CELLLog_Error("not found key<%s>.", "time");
					return;
				}
				
				//服务端响应
				bool is_resp = false;
				if (json.Get("is_resp", is_resp) && is_resp)
				{
					if (!pWSClient->is_ss_link())
					{
						CELLLog_Error("pWSClient->is_ss_link=false, is_resp=true.");
						return;
					}

					int clientId = 0;
					if (!json.Get("clientId", clientId))
					{
						CELLLog_Error("not found key<%s>.", "clientId");
						return;
					}

					auto client = dynamic_cast<INetClientS*>( pServer->find_client(clientId));
					if (!client)
					{
						CELLLog_Error("INetServer::OnNetMsgWS::pServer->find_client(%d) miss.", clientId);
						return;
					}
					if (SOCKET_ERROR == client->writeText(dataStr, wsh.len))
					{
						CELLLog_Error("INetServer::OnNetMsgWS::sslink(%s)->clientId(%d) writeText SOCKET_ERROR.", pWSClient->link_name().c_str(), clientId);
					}

					return;
				}

				bool is_req = false;
				if (!json.Get("is_req", is_req))
				{
					CELLLog_Error("not found key<%s>.", "is_req");
					return;
				}
				//用户端请求
				//服务端请求
				if (is_req)
				{
					std::string cmd;
					if (!json.Get("cmd", cmd))
					{
						CELLLog_Error("not found key<%s>.", "cmd");
						return;
					}

					int clientId = (int)pWSClient->sockfd();
					json.Add("clientId", clientId);

					if (on_net_msg_do(pServer, pWSClient, cmd, json))
						return;

					on_other_msg(pServer, pWSClient, cmd, json);

					return;
				}

				CELLLog_Error("INetServer::OnNetMsgWS:: is_req=false,  is_resp=false.");
			}

			void Init()
			{
				const char* strIP = Config::Instance().getStr("strIP", "any");
				uint16_t nPort = Config::Instance().getInt("nPort", 4567);
				int nThread = 1;//Config::Instance().getInt("nThread", 1);

				if (strcmp(strIP, "any") == 0)
				{
					strIP = nullptr;
				}

				if (Config::Instance().hasKey("-ipv6"))
				{
					CELLLog_Info("-ipv6");
					this->InitSocket(AF_INET6);
				}
				else {
					CELLLog_Info("-ipv4");
					this->InitSocket();
				}

				this->Bind(strIP, nPort);
				this->Listen(SOMAXCONN);
				this->Start(nThread);
			}

			void reg_msg_call(std::string cmd, NetEventCall call)
			{
				_map_msg_call[cmd] = call;
				CELLLog_Info("INetServer::reg_msg_call cmd<%s>.", cmd.c_str());
			}

			bool on_net_msg_do(Server* pServer, INetClientS* pWSClient, std::string& cmd, neb::CJsonObject& msgJson)
			{
				auto itr = _map_msg_call.find(cmd);
				if (itr != _map_msg_call.end())
				{
					itr->second(pServer, pWSClient, msgJson);
					return true;
				}
				CELLLog_Info("%s::INetServer::on_net_msg_do not found cmd<%s>.", pWSClient->link_name().c_str(), cmd.c_str());
				return false;
			}
		};
	}
}
#endif // !_doyou_io_INetServer_HPP_
