#ifndef _doyou_io_GateServer_HPP_
#define _doyou_io_GateServer_HPP_

#include"INetServer.hpp"
#include"INetTransfer.hpp"

namespace doyou {
	namespace io {
		class GateServer
		{
		private:
			INetServer _netserver;
			INetTransfer _transfer;
		public:
			void Init()
			{
				_netserver.Init();
				_netserver.on_other_msg = std::bind(&GateServer::on_other_msg, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
				_netserver.on_client_leave = std::bind(&GateServer::on_client_leave, this, std::placeholders::_1);
				_netserver.reg_msg_call("cs_msg_heart", std::bind(&GateServer::cs_msg_heart, this,std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
				_netserver.reg_msg_call("ss_reg_api", std::bind(&GateServer::ss_reg_api, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
				
			}

			void Close()
			{
				_netserver.Close();
			}

		private:
			void cs_msg_heart(Server* server, INetClientS* client, neb::CJsonObject& msg)
			{
				//CELLLog_Info("GateServer::cs_msg_heart");

				//neb::CJsonObject ret;
				//ret.Add("data", "wo ye bu ji dao.");
				//client->response(msg, ret);

				//client->respone(msg, "wo ye bu ji dao.");
			}

			void ss_reg_api(Server* server, INetClientS* client, neb::CJsonObject& msg)
			{
				auto sskey = msg["data"]("sskey");
				auto sskey_local = Config::Instance().getStr("sskey", "ssmm00@123456");
				if (sskey != sskey_local)
				{
					neb::CJsonObject ret;
					ret.Add("state", 0);
					ret.Add("msg", "sskey error.");
					client->response(msg, ret);
					return;
				}
				auto type = msg["data"]("type");
				auto name = msg["data"]("name");

				client->link_type(type);
				client->link_name(name);
				client->is_ss_link(true);

				auto apis = msg["data"]["apis"];

				if (!apis.IsArray())
				{
					neb::CJsonObject ret;
					ret.Add("state", 0);
					ret.Add("msg", "not found apis.");
					client->response(msg, ret);
					return;
				}

				int size = apis.GetArraySize();
				for (size_t i = 0; i < size; i++)
				{
					CELLLog_Info("ss_reg_api: %s >> %s", name.c_str(), apis(i).c_str());
					_transfer.add(apis(i), client);
				}

				client->response(msg, "ss_reg_api ok!");
			}

			void on_other_msg(Server* server, INetClientS* client, std::string& cmd, neb::CJsonObject& msg)
			{
				auto str = msg.ToString();
				if (!_transfer.on_net_msg_do(cmd, str))
				{
					CELLLog_Info("on_other_msg: transfer not found cmd<%s>.", cmd.c_str());
				}
			}

			void on_client_leave(INetClientS* client)
			{
				if(client->is_ss_link())
					_transfer.del(client);
			}
		};
	}
}
#endif // !_doyou_io_GateServer_HPP_
