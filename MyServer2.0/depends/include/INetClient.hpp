#ifndef _doyou_io_INetClient_HPP_
#define _doyou_io_INetClient_HPP_

#include"TcpWebSocketClient.hpp"
#include"../json/CJsonObject.hpp"
#include"Config.hpp"

namespace doyou {
	namespace io {

		//客户端数据类型
		class INetClient
		{
		private:
			TcpWebSocketClient _client;

		public:
			INetClient(SOCKET sockfd = INVALID_SOCKET, int sendSize = SEND_BUFF_SZIE, int recvSize = RECV_BUFF_SZIE)
			{

			}

			bool connect(const char* url)
			{
				int sendBuffSize = Config::Instance().getInt("nSendBuffSize", SEND_BUFF_SZIE);
				int recvBuffSize = Config::Instance().getInt("nRecvBuffSize", RECV_BUFF_SZIE);

				_client.send_buff_size(sendBuffSize);
				_client.recv_buff_size(recvBuffSize);

				if (_client.connect(url))
				{
					return false;
				}
			}

			void response(int msgId, std::string data)
			{
				neb::CJsonObject ret;
				ret.Add("msgId", msgId);
				ret.Add("time", Time::getSystemClockNow());
				ret.Add("data", data);

				std::string retString = ret.ToString();
				_client.writeText(retString.c_str(), retString.length());
			}

			void response(neb::CJsonObject msg, std::string data)
			{
				int msgId;
				if (!msg.Get("msgId", msgId))
				{
					CELLLog_Error("error");
					return;
				}

				neb::CJsonObject ret;
				ret.Add("msgId", msgId);
				ret.Add("time", Time::getSystemClockNow());
				ret.Add("data", data);

				std::string retString = ret.ToString();
				_client.writeText(retString.c_str(), retString.length());
			}
		};
	}
}
#endif // !_doyou_io_INetClient_HPP_
