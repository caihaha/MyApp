#ifndef _TcpClientMgr_hpp_
#define _TcpClientMgr_hpp_

#if _WIN32
	#include"TcpIocpClient.hpp"
#elif __linux__
	#include"TcpEpollClient.hpp"
#else
	#include"TcpSelectClient.hpp"
#endif

namespace doyou {
	namespace io {
#if _WIN32
		typedef TcpIocpClient TcpClientMgr;
#elif __linux__
		typedef TcpEpollClient TcpClientMgr;
#else
		typedef TcpSelectClient TcpClientMgr;
#endif
	}
}
#endif // !_TcpClientMgr_hpp_
