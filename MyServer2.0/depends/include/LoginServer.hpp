#ifndef _doyou_io_LoginServer_HPP_
#define _doyou_io_LoginServer_HPP_

#include"INetServer.hpp"

namespace doyou {
	namespace io {
		class LoginServer
		{
		private:
			INetServer _netServer;

		public:
			void Init()
			{
				_netServer.Init();
				_netServer.reg_msg_call("cs_msg_heart", std::bind(&LoginServer::cs_msg_heart, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
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

				client->response(msgId, "hello");
			}
		};
	}
}
#endif // !_doyou_io_LoginServer_HPP_
