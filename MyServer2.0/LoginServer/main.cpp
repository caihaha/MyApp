#include"Log.hpp"
#include"Config.hpp"
#include"LoginServer.hpp"
#include"CJsonObject.hpp"

using namespace doyou::io;

int main(int argc, char* args[])
{
	//����������־����
	Log::Instance().setLogPath("LoginServerLog", "w", false);
	Config::Instance().Init(argc, args);

	LoginServer server;
	server.Init();

	//�����߳��еȴ��û���������
	while (true)
	{
		char cmdBuf[256] = {};
		scanf("%s", cmdBuf);
		if (0 == strcmp(cmdBuf, "exit"))
		{
			server.Close();
			break;
		}
		else {
			CELLLog_Info("undefine cmd");
		}
	}

	CELLLog_Info("exit.");

	return 0;
}
