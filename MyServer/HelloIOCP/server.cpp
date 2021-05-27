#include"CELLIOCP.hpp"

#define nClient 3

//-- 用Socket API建立简易TCP服务端
//-- IOCP Server基础流程
int main()
{
	//启动Windows socket 2.x环境
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);
	//------------//
	// 1 建立一个socket
	// 当使用socket函数创建套接字时，会默认设置WSA_FLAG_OVERLAPPED标志
	//////
	// 注意这里也可以用 WSASocket函数创建socket
	// 最后一个参数需要设置为重叠标志（WSA_FLAG_OVERLAPPED）
	// SOCKET sockServer = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	//////
	SOCKET sockServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// 2.1 设置对外IP与端口信息 
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);//host to net unsigned short
	_sin.sin_addr.s_addr = INADDR_ANY;
	// 2.2 绑定sockaddr与ServerSocket
	if (SOCKET_ERROR == bind(sockServer, (sockaddr*)&_sin, sizeof(_sin)))
	{
		printf("错误,绑定网络端口失败...\n");
	}
	else {
		printf("绑定网络端口成功...\n");
	}

	// 3 监听ServerSocket
	if (SOCKET_ERROR == listen(sockServer, 64))
	{
		printf("错误,监听网络端口失败...\n");
	}
	else {
		printf("监听网络端口成功...\n");
	}
	//-------IOCP Begin-------//
	//4 创建完成端口IOCP
	CELLIOCP iocp;
	iocp.create();
	
	//5 关联IOCP与ServerSocket
	//完成键
	iocp.reg(sockServer);

	//6 向IOCP投递接受连接的任务
	iocp.loadAcceptEx(sockServer);


	IO_DATA_BASE ioData[nClient] = {};
	for (int n = 0; n < nClient; n++)
	{
		iocp.postAccept(&ioData[n]);
	}
		
	IO_EVENT ioEvent = {};
	int msgCount = 0;
	while (true)
	{
		int ret = iocp.wait(ioEvent, 1);
		if (ret < 0)
		{
			break;
		}
		if (ret == 0)
		{
			continue;
		}
		//7.1 接受连接 完成
		if (IO_TYPE::ACCEPT == ioEvent.pIoData->iotype)
		{
			printf("新客户端加入 sockfd=%d\n", ioEvent.pIoData->sockfd);
			//7.2 关联IOCP与ClientSocket
			if (!iocp.reg(ioEvent.pIoData->sockfd))
			{
				//printf("关联IOCP与ClientSocket=%d失败\n", ioEvent.pIoData->sockfd);
				closesocket(ioEvent.pIoData->sockfd);
				iocp.postAccept(ioEvent.pIoData);
				continue;
			}
			//7.3 向IOCP投递接收数据任务
			iocp.postRecv(ioEvent.pIoData);
		}
		//8.1 接收数据 完成 Completion
		else if (IO_TYPE::RECV == ioEvent.pIoData->iotype)
		{
			if (ioEvent.bytesTrans <= 0)
			{//客户端断开处理
				printf("关闭 sockfd=%d, RECV bytesTrans=%d\n", ioEvent.pIoData->sockfd, ioEvent.bytesTrans);
				closesocket(ioEvent.pIoData->sockfd);
				iocp.postAccept(ioEvent.pIoData);
				continue;
			}
			//printf("收到数据: sockfd=%d, bytesTrans=%d msgCount=%d\n", ioEvent.pIoData->sockfd, ioEvent.bytesTrans, ++msgCount);
			ioEvent.pIoData->length = ioEvent.bytesTrans;
			//8.2 向IOCP投递发送数据任务
			iocp.postSend(ioEvent.pIoData);
		}
		//9.1 发送数据 完成 Completion
		else if (IO_TYPE::SEND == ioEvent.pIoData->iotype)
		{
			if (ioEvent.bytesTrans <= 0)
			{//客户端断开处理
				printf("关闭 sockfd=%d, SEND bytesTrans=%d\n", ioEvent.pIoData->sockfd, ioEvent.bytesTrans);
				closesocket(ioEvent.pIoData->sockfd);
				iocp.postAccept(ioEvent.pIoData);
				continue;
			}
			//printf("发送数据: sockfd=%d, bytesTrans=%d msgCount=%d\n", ioEvent.pIoData->sockfd, ioEvent.bytesTrans, msgCount);
			//9.2 向IOCP投递接收数据任务
			iocp.postRecv(ioEvent.pIoData);
		}
		else {
			printf("未定义行为 sockfd=%d", ioEvent.sockfd);
		}
	}

	//------------//
	//10.1 关闭ClientSocket
	for (int n = 0; n < nClient; n++)
	{
		closesocket(ioData[n].sockfd);
	}
	//10.2 关闭ServerSocket
	closesocket(sockServer);
	//10.3 关闭完成端口
	iocp.destory();
	//清除Windows socket环境
	WSACleanup();
	return 0;
}