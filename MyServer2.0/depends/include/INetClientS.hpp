#ifndef _doyou_io_INetClientS_HPP_
#define _doyou_io_INetClientS_HPP_

#include"HttpClientS.hpp"
#include"sha1.hpp"
#include"base64.hpp"
#include"WebSocketObj.hpp"
#include"WebSocketClientS.hpp"

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
		};
	}
}
#endif // !_doyou_io_INetClientS_HPP_
