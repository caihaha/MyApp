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
			std::string _linkName;
			std::string _url;
			int _msgId;

			typedef std::function<void(INetClient*, neb::CJsonObject&)> NetEventCall;
			std::map<std::string, NetEventCall> _map_msg_call;

		public:
			void reg_msg_call(const std::string &cmd, NetEventCall call)
			{
				_map_msg_call[cmd] = call;
			}

			bool on_net_msg_do(const std::string &cmd, neb::CJsonObject& msgJson)
			{
				auto iter = _map_msg_call.find(cmd);
				if (iter != _map_msg_call.end())
				{
					iter->second(this, msgJson);
					return true;
				}

				CELLLog_Error("unregist cmd %s", cmd);
				return false;
			}

			bool connect(const char *linkName, const char* url)
			{
				_url = url;
				_linkName = linkName;

				int sendBuffSize = Config::Instance().getInt("nSendBuffSize", SEND_BUFF_SZIE);
				int recvBuffSize = Config::Instance().getInt("nRecvBuffSize", RECV_BUFF_SZIE);

				_client.send_buff_size(sendBuffSize);
				_client.recv_buff_size(recvBuffSize);

				if (!_client.connect(url))
				{
					CELLLog_Warring("INetClient:connect(%s) failed", url);
					return false;
				}

				_client.onopen = [this](WebSocketClientC* pWSClient)
				{
					CELLLog_Info("open");
					neb::CJsonObject msg;
					msg.Add("linkName", _linkName);
					msg.Add("url", "_url");
					on_net_msg_do("onopen", msg);
				};

				_client.onmessage = [this](WebSocketClientC* pWSClient)
				{
					WebSocketHeader& wsh = pWSClient->WebsocketHeader();
					if (wsh.opcode == opcode_PONG)
					{
						CELLLog_Info("websocket server say: PONG");
						return;
					}

					auto data = pWSClient->fetch_data();
					CELLLog_Info("websocket server say: %s", data);

					neb::CJsonObject json;
					if (!json.Parse(data))
					{
						CELLLog_Error("json.Parse error %s", json.GetErrMsg().c_str());
						return;
					}

					int msgId;
					if (!json.Get("msgId", msgId))
					{
						CELLLog_Error("error");
						return;
					}

					std::string cmd;
					if (!json.Get("cmd", cmd))
					{
						CELLLog_Error("error");
						return;
					}

					time_t time = 0;
					if (!json.Get("time", time))
					{
						CELLLog_Error("error");
					}

					std::string msgData;
					if (!json.Get("data", msgData))
					{
						CELLLog_Error("error");
					}

					on_net_msg_do(cmd,json);
				};

				_client.onclose = [](WebSocketClientC* pWSClient)
				{
					CELLLog_Info("websocket client onclose!");
				};

				_client.onerror = [](WebSocketClientC* pWSClient)
				{
					CELLLog_Info("websocket client onerror!");
				};
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

			void request(const std::string cmd, neb::CJsonObject &msg)
			{
				msg.Add("msgId", ++_msgId);
				msg.Add("cmd", cmd);
				msg.Add("time", Time::getSystemClockNow());

				std::string retString = msg.ToString();
				_client.writeText(retString.c_str(), retString.length());
			}

			void close()
			{
				_client.Close();
			}

			bool run(int microseconds = 1)
			{
				return _client.OnRun(microseconds);
			}
		};
	}
}
#endif // !_doyou_io_INetClient_HPP_
