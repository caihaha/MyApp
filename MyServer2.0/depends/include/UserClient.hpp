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
				json.Add("password", "123456");

				client->request("cs_msg_regist", json, [](INetClient* client, neb::CJsonObject& msg) {
					CELLLog_Info(msg("data").c_str());
				});
			}
		};
	}
}
#endif // !_doyou_io_UserClient_HPP_
