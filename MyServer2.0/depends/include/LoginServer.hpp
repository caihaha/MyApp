#ifndef _doyou_io_LoginServer_HPP_
#define _doyou_io_LoginServer_HPP_

#include<regex>

#include"INetClient.hpp"
#include"DBUser.hpp"

namespace doyou {
	namespace io {
		class LoginServer
		{
		private:
			INetClient _csGate;
			DBUser _dbuser;
		public:
			void Init()
			{
				_dbuser.init();

				auto csGateUrl = Config::Instance().getStr("csGateUrl", "ws://127.0.0.1:4567");
				_csGate.connect("csGate", csGateUrl);

				_csGate.reg_msg_call("onopen", std::bind(&LoginServer::onopen_csGate, this, std::placeholders::_1, std::placeholders::_2));

				_csGate.reg_msg_call("cs_msg_login", std::bind(&LoginServer::cs_msg_login, this, std::placeholders::_1, std::placeholders::_2));
				_csGate.reg_msg_call("cs_msg_register", std::bind(&LoginServer::cs_msg_register, this, std::placeholders::_1, std::placeholders::_2));
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

				client->request("ss_reg_api", json, [](INetClient* client, neb::CJsonObject& msg) {
					CELLLog_Info(msg("data").c_str());
				});
			}

			void cs_msg_login(INetClient* client, neb::CJsonObject& msg)
			{
				int clientId = 0;
				if (!msg.Get("clientId", clientId))
				{
					CELLLog_Error("not found key<%s>.", "clientId");
					return;
				}

				int msgId = 0;
				if (!msg.Get("msgId", msgId))
				{
					CELLLog_Error("not found key<%s>.", "msgId");
					return;
				}

				client->response(clientId, msgId, "login successs.");
			}

			void cs_msg_register(INetClient* client, neb::CJsonObject& msg)
			{
				//通用基础字段获取与验证
				int clientId = 0;
				if (!msg.Get("clientId", clientId))
				{
					CELLLog_Error("not found key<%s>.", "clientId");
					return;
				}

				int msgId = 0;
				if (!msg.Get("msgId", msgId))
				{
					CELLLog_Error("not found key<%s>.", "msgId");
					return;
				}

				//当前请求字段获取与验证
				std::string username;
				std::string password;
				std::string nickname;
				int sex = -1;
				{
					if (!msg["data"].Get("username", username))
					{
						client->resp_error(clientId, msgId, "not found key <username>.", 1);
						return;
					}

					if (username.empty())
					{
						client->resp_error(clientId, msgId, "<username> can not be empty!", 1);
						return;
					}
					//正则表达式
					std::regex reg1("^[0-9a-zA-Z]{6,16}$");
					if (!regex_match(username, reg1))
					{
						client->resp_error(clientId, msgId, "<username> format is incorrect!", 1);
						return;
					}

					if (!msg["data"].Get("password", password))
					{
						client->resp_error(clientId, msgId, "not found key<password>.", 1);
						return;
					}

					if (password.empty())
					{
						client->resp_error(clientId, msgId, "<password> can not be empty!", 1);
						return;
					}

					//正则表达式
					if (!regex_match(password, reg1))
					{
						client->resp_error(clientId, msgId, "<password> format is incorrect!", 1);
						return;
					}

					if (!msg["data"].Get("nickname", nickname))
					{
						client->resp_error(clientId, msgId, "not found key<nickname>.", 1);
						return;
					}

					if (nickname.empty())
					{
						client->resp_error(clientId, msgId, "<nickname> can not be empty!", 1);
						return;
					}

					if (nickname.length() <3 || nickname.length() > 16)
					{
						client->resp_error(clientId, msgId, "<nickname> format is incorrect!", 1);
						return;
					}

					if (!msg["data"].Get("sex", sex))
					{
						client->resp_error(clientId, msgId, "not found key<sex>.", 1);
						return;
					}

					if (sex !=0 && sex != 1)
					{
						client->resp_error(clientId, msgId, "<sex> is only 0 or 1!", 1);
						return;
					}
				}
				//
				CELLLog_Info("LoginServer::cs_msg_register: msgId=%d username=%s password=%s",msgId , username.c_str(), password.c_str());
				//判断用户名是否已存在
				if (_dbuser.has_username(username))
				{
					client->resp_error(clientId, msgId, "username already exists");
					return;
				}
				//判断昵称是否已存在
				if (_dbuser.has_nickname(nickname))
				{
					client->resp_error(clientId, msgId, "nickname already exists");
					return;
				}
				//新增用户数据
				auto userId = _dbuser.add_user(username, password, nickname, sex);
				if (userId > 0)
				{
					neb::CJsonObject ret;
					ret.Add("userId", userId);
					client->response(clientId, msgId, ret);
				}
				else {
					client->resp_error(clientId, msgId, "unkown error.");
				}
			}
		};
	}
}
#endif // !_doyou_io_LoginServer_HPP_
