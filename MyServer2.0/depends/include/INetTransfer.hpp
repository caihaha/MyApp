#ifndef _doyou_io_INetTransfer_HPP_
#define _doyou_io_INetTransfer_HPP_

#include"CJsonObject.hpp"
#include"INetClientS.hpp"
#include<vector>

namespace doyou {
	namespace io {

		//消息分发
		class INetTransfer
		{
			//服务监听者(服务集群)
			class Listeners
			{
			public:
				void add(INetClientS* client)
				{
					auto itr = std::find(_listeners.begin(), _listeners.end(), client);
					if (itr == _listeners.end())
					{
						_listeners.push_back(client);
					}
				}

				void del(INetClientS* client)
				{
					auto itr = std::find(_listeners.begin(), _listeners.end(), client);
					if (itr != _listeners.end())
					{
						_listeners.erase(itr);
					}
				}

				INetClientS* get()
				{
					auto size = _listeners.size();

					if (size == 0)
						return nullptr;

					if (size == 1)
						return _listeners[0];

					if (index >= size)
						index = 0;

					return _listeners[index++];
				}
			private:
				std::vector<INetClientS*> _listeners;
				int index = 0;
			};
		private:
			std::map<std::string, Listeners> _msg_listeners;
		public:
			void add(std::string cmd, INetClientS* client)
			{
				auto itr = _msg_listeners.find(cmd);
				if (itr != _msg_listeners.end())
				{
					itr->second.add(client);
				}
				else {
					Listeners a;
					a.add(client);
					_msg_listeners[cmd] = a;
				}
			}

			void del(INetClientS* client)
			{
				for (auto& itr: _msg_listeners)
				{
					itr.second.del(client);
				}
			}

			void del(std::string cmd, INetClientS* client)
			{
				auto itr = _msg_listeners.find(cmd);
				if (itr != _msg_listeners.end())
				{
					itr->second.del(client);
				}
			}

			bool on_net_msg_do(std::string& cmd, std::string& data)
			{
				auto itr = _msg_listeners.find(cmd);
				if (itr == _msg_listeners.end())
					return false;

				auto s = itr->second.get();
				if (s)
				{
					s->writeText(data.c_str(), data.length());
					return true;
				}

				return false;
			}
		};
	}
}
#endif // !_doyou_io_INetTransfer_HPP_
