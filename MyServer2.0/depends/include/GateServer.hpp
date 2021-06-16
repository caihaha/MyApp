#ifndef _doyou_io_GateServer_HPP_
#define _doyou_io_GateServer_HPP_

#include"INetServer.hpp"

namespace doyou {
	namespace io {
		class GateServer
		{
		private:
			INetServer _netServer;

		public:
			void Init()
			{
				_netServer.Init();
				_netServer.reg_msg_call("cs_msg_heart", std::bind(&GateServer::cs_msg_heart, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
				_netServer.reg_msg_call("ss_reg_api", std::bind(&GateServer::ss_reg_api, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
			}

			void Close()
			{
				_netServer.Close();
			}

		private:
			void cs_msg_heart(Server* pServer, INetClientS* client, neb::CJsonObject& msg)
			{
				CELLLog_Info("cs_msg_heart");

				int msgId;
				if (!msg.Get("msgId", msgId))
				{
					CELLLog_Error("error");
					return;
				}

				client->response(msgId, "hello1");
			}

			void ss_reg_api(Server* pServer, INetClientS* client, neb::CJsonObject& msg)
			{
				CELLLog_Info("ss_reg_api");

				int msgId;
				if (!msg.Get("msgId", msgId))
				{
					CELLLog_Error("error");
					return;
				}

				client->response(msgId, "hello2");
			}
		};
	}
}
#endif // !_doyou_io_GateServer_HPP_
