#ifndef _EasyIOCPServer_hpp_
#define _EasyIOCPServer_hpp_

#ifndef CELL_USE_IOCP
#define CELL_USE_IOCP
#endif // !CELL_USE_IOCP

#include"TcpServer.hpp"
#include"IocpServer.hpp"
#include"Iocp.hpp"
namespace doyou {
	namespace io {
		class TcpIocpServer : public TcpServer
		{
		public:
			void Start(int nCELLServer)
			{
				TcpServer::Start<IocpServer>(nCELLServer);
			}
		protected:
			//处理网络消息
			void OnRun(Thread* pThread)
			{
				Iocp iocp;
				iocp.create();
				iocp.reg(sockfd());
				iocp.loadAcceptEx(sockfd());
				//
				//const int len = 2 * (sizeof(sockaddr_in) + 16);
				//不需要客户端再连接后立即发送数据的情况下最低长度len
				const int len = 1024;
				char buf[len] = {};

				IO_DATA_BASE ioData = {};
				ioData.wsabuff.buf = buf;
				ioData.wsabuff.len = len;

				iocp.postAccept(&ioData, _address_family);
				//
				IO_EVENT ioEvent = {};
				while (pThread->isRun())
				{
					time4msg();
					//---
					int ret = iocp.wait(ioEvent, 1);
					if (ret < 0)
					{
						CELLLog_Error("TcpIocpServer.OnRun ep.wait exit.");
						pThread->Exit();
						break;
					}
					if (ret == 0)
					{
						continue;
					}
					//---
					//接受连接 完成
					if (IO_TYPE::ACCEPT == ioEvent.pIoData->iotype)
					{
						char* ip = iocp.getAcceptExAddrs(ioEvent.pIoData, _address_family);
						//
						IocpAccept(ioEvent.pIoData->sockfd,ip);
						//继续 向IOCP投递接受连接任务
						iocp.postAccept(&ioData,_address_family);
					}
				}
			}

			//接受客户端连接
			SOCKET IocpAccept(SOCKET cSock,char* ip)
			{
				if (INVALID_SOCKET == cSock)
				{
					CELLLog_PError("accept INVALID_SOCKET...");
				}
				else
				{
					AcceptClient(cSock, ip);
				}
				return cSock;
			}
		};
	}
}
#endif // !_EasyIOCPServer_hpp_
