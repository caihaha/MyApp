#ifndef _doyou_io_TcpHttpServer_HPP_
#define _doyou_io_TcpHttpServer_HPP_

#include"TcpServerMgr.hpp"
#include"HttpClient.hpp"

namespace doyou {
	namespace io {
		class TcpHttpServer :public TcpServerMgr
		{
			virtual Client* makeClientObj(SOCKET cSock)
			{
				return new HttpClient(cSock, _nSendBuffSize, _nRecvBuffSize);
			}
		};
	}
}
#endif // !_doyou_io_TcpHttpServer_HPP_
