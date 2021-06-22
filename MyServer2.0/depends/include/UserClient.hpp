#ifndef _doyou_io_UserClient_HPP_
#define _doyou_io_UserClient_HPP_

#include"INetClient.hpp"

namespace doyou {
	namespace io {
		class UserClient
		{
		private:
			INetClient _csGate;
		public:
			void Init()
			{
				auto csGateUrl = Config::Instance().getStr("csGateUrl", "127.0.0.1:4567");
				_csGate.connect("csGate", csGateUrl);

				_csGate.reg_msg_call("onopen", std::bind(&UserClient::onopen_csGate, this, std::placeholders::_1, std::placeholders::_2));

				//_csGate.reg_msg_call("cs_msg_login", std::bind(&UserClient::cs_msg_login, this, std::placeholders::_1, std::placeholders::_2));
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
				json.Add("username", "test001");
				json.Add("password", "abc1234");

				client->request("cs_msg_register", json, [](INetClient* client, neb::CJsonObject& msg) {
					CELLLog_Info(msg("data").c_str());
				});
			}

			//void cs_msg_login(INetClient* client, neb::CJsonObject& msg)
			//{
			//	CELLLog_Info("UserClient::cs_msg_login");
			//	neb::CJsonObject ret;
			//	ret.Add("data", "login successs.");
			//	client->response(msg, ret);
			//}
		};
	}
}
#endif // !_doyou_io_UserClient_HPP_
