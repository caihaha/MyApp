#ifndef _doyou_io_INetClientS_HPP_
#define _doyou_io_INetClientS_HPP_

#include"HttpClientS.hpp"
#include"sha1.hpp"
#include"base64.hpp"
#include"WebSocketObj.hpp"
#include"WebSocketClientS.hpp"
#include"../json/CJsonObject.hpp"

namespace doyou {
	namespace io {

		//客户端数据类型
		class INetClientS :public WebSocketClientS
		{
		public:
			INetClientS(SOCKET sockfd = INVALID_SOCKET, int sendSize = SEND_BUFF_SZIE, int recvSize = RECV_BUFF_SZIE) :
				WebSocketClientS(sockfd, sendSize, recvSize)
			{

			}

			void response(int msgId, std::string data)
			{
				neb::CJsonObject ret;
				ret.Add("msgId", msgId);
				ret.Add("time", Time::getSystemClockNow());
				ret.Add("data", data);

				std::string retString = ret.ToString();
				writeText(retString.c_str(), retString.length());
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
				writeText(retString.c_str(), retString.length());
			}
		};
	}
}
#endif // !_doyou_io_INetClientS_HPP_
