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

				_csGate.reg_msg_call("onopen", std::bind(&LoginServer::onopen_csGate, this, std::placeholders::_1, std::placeholders::_2));

				_csGate.reg_msg_call("cs_msg_heart", std::bind(&LoginServer::cs_msg_heart, this,std::placeholders::_1, std::placeholders::_2));
				_csGate.reg_msg_call("cs_msg_login", std::bind(&LoginServer::cs_msg_login, this, std::placeholders::_1, std::placeholders::_2));
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
				neb::CJsonObject json;
				json.Add("type", "LoginServer");
				json.Add("name", "LoginServer001");
				json.Add("sskey", "ssmm00@123456");
				json.AddEmptySubArray("apis");
				json["apis"].Add("cs_msg_login");
				json["apis"].Add("cs_msg_register");
				json["apis"].Add("cs_msg_change_pw");

				client->request("ss_reg_api", json);
			}

			void cs_msg_heart(INetClient* client, neb::CJsonObject& msg)
			{
				CELLLog_Info("LoginServer::cs_msg_heart");

				neb::CJsonObject ret;
				ret.Add("data", "wo ye bu ji dao.");
				client->response(msg, ret);

				//client->respone(msg, "wo ye bu ji dao.");
			}

			void cs_msg_login(INetClient* client, neb::CJsonObject& msg)
			{
				CELLLog_Info("LoginServer::cs_msg_login");
			}
		};
	}
}
#endif // !_doyou_io_LoginServer_HPP_
