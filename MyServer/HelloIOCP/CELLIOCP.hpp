#ifndef _CELL_IOCP_HPP_
#define _CELL_IOCP_HPP_

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN

#include<windows.h>
#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#include<mswsock.h>
#include<stdio.h>

enum IO_TYPE
{
	ACCEPT = 10,
	RECV,
	SEND
};

//数据缓冲区空间大小
#define IO_DATA_BUFF_SIZE 1024
struct IO_DATA_BASE
{
	//重叠体
	OVERLAPPED overlapped;
	//
	SOCKET sockfd;
	//数据缓冲区
	char buffer[IO_DATA_BUFF_SIZE];
	//实际缓冲区数据长度
	int length;
	//操作类型
	IO_TYPE iotype;
};

struct IO_EVENT
{
	IO_DATA_BASE* pIoData;
	SOCKET sockfd = INVALID_SOCKET;
	DWORD bytesTrans = 0;
};

class CELLIOCP
{
public:
	~CELLIOCP()
	{
		destory();
	}

	//创建完成端口IOCP
	bool create()
	{
		_completionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
		if (NULL == _completionPort)
		{
			printf("CreateIoCompletionPort failed with error %d\n", GetLastError());
			return false;
		}
		return true;
	}

	void destory()
	{
		if (_completionPort)
		{
			CloseHandle(_completionPort);
			_completionPort = NULL;
		}
	}

	//关联IOCP与ServerSocket
	bool reg(SOCKET sockfd)
	{
		//完成键
		auto ret = CreateIoCompletionPort((HANDLE)sockfd, _completionPort, (ULONG_PTR)sockfd, 0);
		if (!ret)
		{
			printf("关联IOCP与ServerSocket失败,错误码=%d\n", GetLastError());
			return false;
		}
		return true;
	}

	//向IOCP投递接受连接的任务
	void postAccept(IO_DATA_BASE* pIO_DATA)
	{
		if (!_acceptEx)
			printf("error, postAccept _acceptEx is null\n");

		pIO_DATA->iotype = IO_TYPE::ACCEPT;
		pIO_DATA->sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (FALSE == _acceptEx(_sockServer
			, pIO_DATA->sockfd
			, pIO_DATA->buffer
			, 0
			, sizeof(sockaddr_in) + 16
			, sizeof(sockaddr_in) + 16
			, NULL
			, &pIO_DATA->overlapped
		))
		{
			int err = WSAGetLastError();
			if (ERROR_IO_PENDING != err)
			{
				printf("AcceptEx failed with error %d\n", err);
				return;
			}
		}
	}

	//向IOCP投递接收数据的任务
	void postRecv(IO_DATA_BASE* pIO_DATA)
	{
		pIO_DATA->iotype = IO_TYPE::RECV;
		WSABUF wsBuff = {};
		wsBuff.buf = pIO_DATA->buffer;
		wsBuff.len = IO_DATA_BUFF_SIZE;
		DWORD flags = 0;
		ZeroMemory(&pIO_DATA->overlapped, sizeof(OVERLAPPED));

		if (SOCKET_ERROR == WSARecv(pIO_DATA->sockfd, &wsBuff, 1, NULL, &flags, &pIO_DATA->overlapped, NULL))
		{
			int err = WSAGetLastError();
			if (ERROR_IO_PENDING != err)
			{
				printf("WSARecv failed with error %d\n", err);
				return;
			}
		}
	}
	//向IOCP投递发送数据的任务
	void postSend(IO_DATA_BASE* pIO_DATA)
	{
		pIO_DATA->iotype = IO_TYPE::SEND;
		WSABUF wsBuff = {};
		wsBuff.buf = pIO_DATA->buffer;
		wsBuff.len = pIO_DATA->length;
		DWORD flags = 0;
		ZeroMemory(&pIO_DATA->overlapped, sizeof(OVERLAPPED));

		if (SOCKET_ERROR == WSASend(pIO_DATA->sockfd, &wsBuff, 1, NULL, flags, &pIO_DATA->overlapped, NULL))
		{
			int err = WSAGetLastError();
			if (ERROR_IO_PENDING != err)
			{
				printf("WSASend failed with error %d\n", err);
				return;
			}
		}
	}

	int wait(IO_EVENT& ioEvent,int timeout)
	{
		ioEvent.bytesTrans = 0;
		ioEvent.pIoData = NULL;
		ioEvent.sockfd = INVALID_SOCKET;
		if (FALSE == GetQueuedCompletionStatus(_completionPort
			, &ioEvent.bytesTrans
			, (PULONG_PTR)&ioEvent.sockfd
			, (LPOVERLAPPED*)&ioEvent.pIoData
			, timeout))
		{
			int err = GetLastError();
			if (WAIT_TIMEOUT == err)
			{
				return 0;
			}
			if (ERROR_NETNAME_DELETED == err)
			{
				return 1;
			}
			printf("GetQueuedCompletionStatus failed with error %d\n", err);
			return -1;
		}
		return 1;
	}

	bool loadAcceptEx(SOCKET listenSocket)
	{
		if (INVALID_SOCKET != _sockServer)
		{
			printf("loadAcceptEx _sockServer != INVALID_SOCKET\n");
			return false;
		}
		if (_acceptEx)
		{
			printf("loadAcceptEx _acceptEx != NULL\n");
			return false;
		}
		_sockServer = listenSocket;
		GUID guidAcceptEx = WSAID_ACCEPTEX;
		DWORD dwBytes = 0;
		int iResult = WSAIoctl(listenSocket, SIO_GET_EXTENSION_FUNCTION_POINTER,
			&guidAcceptEx, sizeof(guidAcceptEx),
			&_acceptEx, sizeof(_acceptEx),
			&dwBytes, NULL, NULL);

		if (iResult == SOCKET_ERROR) {
			printf("WSAIoctl failed with error: %u\n", WSAGetLastError());
			return false;
		}
		return true;
	}
private:
	//将AcceptEx函数加载内存中，调用效率更高
	LPFN_ACCEPTEX _acceptEx = NULL;
	HANDLE _completionPort = NULL;
	SOCKET _sockServer = INVALID_SOCKET;
};

#endif //_WIN32

#endif // !_CELL_IOCP_HPP_