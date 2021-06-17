#ifndef _doyou_io_INetClient_HPP_
#define _doyou_io_INetClient_HPP_

#include"TcpWebSocketClient.hpp"
#include"CJsonObject.hpp"
#include"Config.hpp"

namespace doyou {
	namespace io {

		//客户端数据类型
		class INetClient
		{
		private:
			TcpWebSocketClient _client;
			//
			std::string _link_name;
			std::string _url;
			//
			int msgId = 0;
		private:
			typedef std::function<void(INetClient*, neb::CJsonObject&)> NetEventCall;
			std::map<std::string, NetEventCall> _map_msg_call;
		public:
			bool connect(const char* link_name,const char* url)
			{
				_link_name = link_name;
				_url = url;

				int s_size = Config::Instance().getInt("nSendBuffSize", SEND_BUFF_SZIE);
				int r_size = Config::Instance().getInt("nRecvBuffSize", RECV_BUFF_SZIE);

				_client.send_buff_size(s_size);
				_client.recv_buff_size(r_size);

				if (!_client.connect(url))
				{
					CELLLog_Warring("%s::INetClient::connect(%s) failed.", _link_name.c_str(), _url.c_str());
					return false;
				}

				//do
				_client.onopen = [this](WebSocketClientC* pWSClient)
				{
					CELLLog_Info("%s::INetClient::connect(%s) success.", _link_name.c_str(), _url.c_str());
					neb::CJsonObject json;
					json.Add("link_name", _link_name);
					json.Add("url", _url);
					on_net_msg_do("onopen", json);
				};

				_client.onmessage = [this](WebSocketClientC* pWSClient)
				{
					WebSocketHeader& wsh = pWSClient->WebsocketHeader();
					if (wsh.opcode == opcode_PONG)
					{
						CELLLog_Info("websocket server say: PONG");
						return;
					}

					auto dataStr = pWSClient->fetch_data();
					//CELLLog_Info("websocket server say: %s", dataStr);

					neb::CJsonObject json;
					if (!json.Parse(dataStr))
					{
						CELLLog_Error("json.Parse error : %s", json.GetErrMsg().c_str());
						return;
					}

					int msgId = 0;
					if (!json.Get("msgId", msgId))
					{
						CELLLog_Error("not found key<%s>.", "msgId");
						return;
					}

					time_t time = 0;
					if (!json.Get("time", time))
					{
						CELLLog_Error("not found key<%s>.", "time");
						return;
					}

					std::string cmd;
					if (!json.Get("cmd", cmd))
					{
						CELLLog_Error("not found key<%s>.", "cmd");
						return;
					}

					std::string data;
					if (!json.Get("data", data))
					{
						CELLLog_Error("not found key<%s>.", "data");
						return;
					}

					on_net_msg_do(cmd, json);
				};

				_client.onclose = [this](WebSocketClientC* pWSClient)
				{
					neb::CJsonObject json;
					json.Add("link_name", _link_name);
					json.Add("url", _url);
					on_net_msg_do("onclose", json);
				};

				_client.onerror = [this](WebSocketClientC* pWSClient)
				{
					neb::CJsonObject json;
					json.Add("link_name", _link_name);
					json.Add("url", _url);
					on_net_msg_do("onerror", json);
				};

			}

			bool run(int microseconds = 1)
			{
				return _client.OnRun(microseconds);
			}

			void close()
			{
				_client.Close();
			}

			void reg_msg_call(std::string cmd, NetEventCall call)
			{
				_map_msg_call[cmd] = call;
			}

			bool on_net_msg_do(const std::string& cmd, neb::CJsonObject& msgJson)
			{
				auto itr = _map_msg_call.find(cmd);
				if (itr != _map_msg_call.end())
				{
					itr->second(this, msgJson);
					return true;
				}
				CELLLog_Info("%s::INetClient::on_net_msg_do not found cmd<%s>.", _link_name.c_str(),cmd.c_str());
				return false;
			}


			void request(const std::string& cmd, neb::CJsonObject& data)
			{
				neb::CJsonObject msg;
				msg.Add("cmd", cmd);
				msg.Add("msgId", ++msgId);
				msg.Add("time", Time::system_clock_now());
				msg.Add("data", data);

				std::string retStr = msg.ToString();
				_client.writeText(retStr.c_str(), retStr.length());
			}

			void response(int msgId, std::string data)
			{
				neb::CJsonObject ret;
				ret.Add("msgId", msgId);
				ret.Add("time", Time::system_clock_now());
				ret.Add("data", data);

				std::string retStr = ret.ToString();
				_client.writeText(retStr.c_str(), retStr.length());
			}

			void response(neb::CJsonObject& msg, std::string data)
			{
				int msgId = 0;
				if (!msg.Get("msgId", msgId))
				{
					CELLLog_Error("not found key<%s>.", "msgId");
					return;
				}

				neb::CJsonObject ret;
				ret.Add("msgId", msgId);
				ret.Add("time", Time::system_clock_now());
				ret.Add("data", data);

				std::string retStr = ret.ToString();
				_client.writeText(retStr.c_str(), retStr.length());
			}

			void response(neb::CJsonObject& msg, neb::CJsonObject& ret)
			{
				int msgId = 0;
				if (!msg.Get("msgId", msgId))
				{
					CELLLog_Error("not found key<%s>.", "msgId");
					return;
				}

				ret.Add("msgId", msgId);
				ret.Add("time", Time::system_clock_now());

				std::string retStr = ret.ToString();
				_client.writeText(retStr.c_str(), retStr.length());
			}
		};
	}
}
#endif // !_doyou_io_INetClient_HPP_
