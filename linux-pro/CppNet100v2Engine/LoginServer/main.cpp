#include"Log.hpp"
#include"Config.hpp"
#include"LoginServer.hpp"


using namespace doyou::io;

int main(int argc, char* args[])
{
	//设置运行日志名称
	Log::Instance().setLogPath("LoginServerLog", "w", false);
	Config::Instance().Init(argc, args);

	LoginServer server;
	server.Init();
	while (true)
	{
		server.Run();
	}
	server.Close();

	////在主线程中等待用户输入命令
	//while (true)
	//{
	//	char cmdBuf[256] = {};
	//	scanf("%s", cmdBuf);
	//	if (0 == strcmp(cmdBuf, "exit"))
	//	{
	//		server.Close();
	//		break;
	//	}
	//	else {
	//		CELLLog_Info("undefine cmd");
	//	}
	//}

	CELLLog_Info("exit.");

	return 0;
}
