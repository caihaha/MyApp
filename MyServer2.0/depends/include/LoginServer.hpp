#ifndef _doyou_io_LoginServer_HPP_
#define _doyou_io_LoginServer_HPP_

#include"INetClient.hpp"

namespace doyou {
	namespace io {
		class LoginServer
		{
		private:
			INetClient _csGate;

		public:
			void Init()
			{
				_csGate.connect("csGate", "127.0.0.1:4567");
				_csGate.reg_msg_call("cs_msg_login", std::bind(&LoginServer::cs_msg_login, this, std::placeholders::_1, std::placeholders::_2));
				_csGate.reg_msg_call("cs_msg_heart", std::bind(&LoginServer::cs_msg_heart, this, std::placeholders::_1, std::placeholders::_2));
				_csGate.reg_msg_call("onopen", std::bind(&LoginServer::onopen_csGate, this, std::placeholders::_1, std::placeholders::_2));
			}

			void Run()
			{
				_csGate.run(1);
			}

			void Close()
			{
				_csGate.close();
			}

		private:
			void onopen_csGate(INetClient* client, neb::CJsonObject& msg)
			{
				neb::CJsonObject tmp;
				tmp.Add("type", "LoginServer");
				tmp.Add("name", "LoginServer001");
				client->request("ss_reg_api", tmp);
			}

			void cs_msg_heart(INetClient* client, neb::CJsonObject& msg)
			{
				CELLLog_Info("cs_msg_heart");

				int msgId;
				if (!msg.Get("msgId", msgId))
				{
					CELLLog_Error("error");
					return;
				}

				client->response(msgId, "hello");
			}

			void cs_msg_login(INetClient* client, neb::CJsonObject& msg)
			{
				CELLLog_Info("cs_msg_login");

				int msgId;
				if (!msg.Get("msgId", msgId))
				{
					CELLLog_Error("error");
					return;
				}

				client->response(msgId, "hello");
			}
		};
	}
}
#endif // !_doyou_io_LoginServer_HPP_
