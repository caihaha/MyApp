#ifndef _TcpServerMgr_hpp_
#define _TcpServerMgr_hpp_

#if _WIN32
	#include"TcpIocpServer.hpp"
#elif __linux__
	#include"TcpEpollServer.hpp"
#else
	#include"TcpSelectServer.hpp"
#endif

namespace doyou {
	namespace io {
#if _WIN32
		typedef TcpIocpServer TcpServerMgr;
#elif __linux__
		typedef TcpEpollServer TcpServerMgr;
#else
		typedef TcpSelectServer TcpServerMgr;
#endif
	}
}
#endif // !_TcpServerMgr_hpp_
