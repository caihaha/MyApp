#ifndef _CELLIOCPServer_HPP_
#define _CELLIOCPServer_HPP_

#include"Server.hpp"
#include"Iocp.hpp"

namespace doyou {
	namespace io {
		//网络消息接收处理服务类
		class IocpServer :public Server
		{
		public:
			IocpServer()
			{
				_iocp.create();
			}

			~IocpServer() noexcept
			{
				Close();
			}

			bool DoNetEvents()
			{
				Client* pClient = nullptr;
				for (auto iter = _clients.begin(); iter != _clients.end(); iter++)
				{
					pClient = iter->second;
					//需要写数据的客户端,才postSend
					if (pClient->needWrite())
					{
						auto pIoData = pClient->makeSendIoData();
						if (pIoData)
						{
							if (!_iocp.postSend(pIoData))
							{
								pClient->postSendComplete();
								pClient->onClose();
								continue;
							}
						}
						//--
						pIoData = pClient->makeRecvIoData();
						if (pIoData)
						{
							if (!_iocp.postRecv(pIoData))
							{
								pClient->postRecvComplete();
								pClient->onClose();
							}
						}
					}
					else {
						auto pIoData = pClient->makeRecvIoData();
						if (pIoData)
						{
							if (!_iocp.postRecv(pIoData))
							{
								pClient->postRecvComplete();
								pClient->onClose();
							}
						}
					}
				}
				//---
				while (true)
				{
					int ret = DoIocpNetEvents();
					if (ret < 0)
					{
						return false;
					}
					else if (ret == 0)
					{
						return true;
					}
				}
				return true;
			}
			//每次只处理一件网络事件
			//ret = -1 iocp出错
			//ret =  0 没有事件
			//ret =  1 有事件发生
			int DoIocpNetEvents()
			{
				int ret = _iocp.wait(_ioEvent, 1);
				if (ret < 0)
				{
					CELLLog_Error("IocpServer%d.OnRun.wait", _id);
					return ret;
				}
				else if (ret == 0)
				{
					return ret;
				}
				//---

				//接收数据 完成 Completion
				if (IO_TYPE::RECV == _ioEvent.pIoData->iotype)
				{
					Client* pClient = (Client*)_ioEvent.data.ptr;
					if (pClient)
					{
						if (_ioEvent.bytesTrans <= 0)
						{//客户端断开处理
						 //CELLLog_Info("rmClient sockfd=%d, IO_TYPE::RECV bytesTrans=%d", _ioEvent.pIoData->sockfd, _ioEvent.bytesTrans);
							pClient->postRecvComplete();
							pClient->onClose();
							return ret;
						}
						//
						pClient->recv4iocp(_ioEvent.bytesTrans);
						OnNetRecv(pClient);
					}
					//
					//CELLLog_Info("IO_TYPE::RECV sockfd=%d, bytesTrans=%d", _ioEvent.pIoData->sockfd, _ioEvent.bytesTrans);
				}
				//发送数据 完成 Completion
				else if (IO_TYPE::SEND == _ioEvent.pIoData->iotype)
				{
					Client* pClient = (Client*)_ioEvent.data.ptr;
					if (pClient)
					{
						if (_ioEvent.bytesTrans <= 0)
						{//客户端断开处理
						 //CELLLog_Info("rmClient sockfd=%d, IO_TYPE::SEND bytesTrans=%d", _ioEvent.pIoData->sockfd, _ioEvent.bytesTrans);
							pClient->postSendComplete();
							pClient->onClose();
							return ret;
						}
						//
						pClient->send2iocp(_ioEvent.bytesTrans);
					}
					//
					//CELLLog_Info("IO_TYPE::SEND sockfd=%d, bytesTrans=%d", _ioEvent.pIoData->sockfd, _ioEvent.bytesTrans);
				}
				else {
					CELLLog_Warring("undefine io type.");
				}
				return ret;
			}

			void OnClientJoin(Client* pClient)
			{
				_iocp.reg(pClient->sockfd(), pClient);
			}
		private:
			Iocp _iocp;
			IO_EVENT _ioEvent = {};
		};
	}
}
#endif // !_CELLIOCPServer_HPP_
