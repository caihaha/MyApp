#ifndef _doyou_io_INetServer_HPP_
#define _doyou_io_INetServer_HPP_

#include"TcpServerMgr.hpp"
#include"INetClientS.hpp"
#include"TcpWebSocketServer.hpp"
#include"../json/CJsonObject.hpp"

namespace doyou {
	namespace io {
		class INetServer :public TcpWebSocketServer
		{
		private:
			typedef std::function<void(Server*, INetClientS*, neb::CJsonObject&)> NetEventCall;
			std::map<std::string, NetEventCall> _map_msg_call;


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
		public:
			void Init()
			{
				const char* strIP = Config::Instance().getStr("strIP", "any");
				uint16_t nPort = Config::Instance().getInt("nPort", 4567);
				int nThread = Config::Instance().getInt("nThread", 1);

				if (strcmp(strIP, "any") == 0)
				{
					strIP = nullptr;
				}

				if (Config::Instance().hasKey("-ipv6"))
				{
					CELLLog_Info("-ipv6");
					InitSocket(AF_INET6);
				}
				else {
					CELLLog_Info("-ipv4");
					InitSocket();
				}

				Bind(strIP, nPort);
				Listen(SOMAXCONN);
				Start(nThread);
			}

			virtual void OnNetMsgWS(Server* pServer, INetClientS* pWSClient)
			{
				WebSocketHeader& wsh = pWSClient->WebsocketHeader();
				if (wsh.opcode == opcode_PONG)
				{
					CELLLog_Info("websocket server say: PONG");
					return;
				}
				auto data = pWSClient->fetch_data();
				CELLLog_Info("websocket client say: %s", data);
				// pWSClient->writeText(data, wsh.len);
				neb::CJsonObject json;
				if (!json.Parse(data))
				{
					CELLLog_Error("json.Parse error %s", json.GetErrMsg().c_str());
					return;
				}

				std::string cmd;
				if (!json.Get("msgId", cmd))
				{
					CELLLog_Error("error");
				}

				time_t time = 0;
				if (!json.Get("time", time))
				{
					CELLLog_Error("error");
				}

				std::string msgData;
				if (!json.Get("data", msgData))
				{
					CELLLog_Error("error");
				}

				on_net_msg_do(pServer, pWSClient, cmd, json);

				//std::string resp;
				//for (size_t i = 0; i < 130; i++)
				//{
				//	resp += "HelloHello";
				//}
				//resp += "=";
				//pWSClient->writeText(resp.c_str(), resp.length());

				// pWSClient->ping();
			}

			void reg_msg_call(std::string cmd, NetEventCall call)
			{
				_map_msg_call[cmd] = call;
			}

			bool on_net_msg_do(Server* pServer, INetClientS* pClient, std::string cmd, neb::CJsonObject& msgJson)
			{
				auto iter = _map_msg_call.find(cmd);
				if (iter != _map_msg_call.end())
				{
					iter->second(pServer, pClient, msgJson);
					return true;
				}
				return false;
			}
		};
	}
}
#endif // !_doyou_io_INetServer_HPP_
