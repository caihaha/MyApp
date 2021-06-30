#include"Log.hpp"
#include"Config.hpp"
#include"LoginServer.hpp"
#include"DBUser.hpp"

using namespace doyou::io;

int main(int argc, char* args[])
{
#if _WIN32 && _CONSOLE
	system("chcp 65001");
#endif // _WIN32 && _CONSOLE

	//设置运行日志名称
	Log::Instance().setLogPath("LoginServerLog", "w", false);
	Config::Instance().Init(argc, args);
	////////////////////
	DBUser db;
	db.init();
	neb::CJsonObject ret;
	auto b = db.findByKV("user_info", "sex","1", ret);
	if (b && ret.IsArray())
	{
		int length = ret.GetArraySize();
		for (size_t i = 0; i < length; i++)
		{
			std::string id = ret[i]("id");
			int64 userId = 0;
			ret[i].Get("userId", userId);
			std::string username =  ret[i]("username");
			std::string password = ret[i]("password");
			std::string nickname = ret[i]("nickname");
			std::string sex = ret[i]("sex");
			std::string state = ret[i]("state");
			std::string create_date = ret[i]("create_date");
			CELLLog_Info("userId=%d username=%s password=%s nickname=%s", userId, username.c_str(), password.c_str(), nickname.c_str());
		}
	}
	//db.add_user("user001", "mm123456", "asd", 0);
	//db.add_user("user002", "mm123456", "qbl", 0);
	db.close();
	///////////////////
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
