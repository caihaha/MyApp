#ifndef _doyou_io_TcpHttpClient_HPP_
#define _doyou_io_TcpHttpClient_HPP_

#include"TcpClientMgr.hpp"
#include"HttpClientC.hpp"

namespace doyou {
	namespace io {
		class TcpHttpClient :public TcpClientMgr
		{
		protected:
			virtual Client* makeClientObj(SOCKET cSock, int sendSize, int recvSize)
			{
				return new HttpClientC(cSock, sendSize, recvSize);
			}
		};
	}
}
#endif // !_doyou_io_TcpHttpClient_HPP_
