#include"Log.hpp"
#include"Config.hpp"
#include"TcpHttpServer.hpp"

using namespace doyou::io;

class MyServer:public TcpHttpServer
{
public:
	virtual void OnNetMsg(Server* pServer, Client* pClient, netmsg_DataHeader* header)
	{
		HttpClient* pHttpClient = dynamic_cast<HttpClient*>(pClient);
		if (!pHttpClient)
			return;

		if(!pHttpClient->getRequestInfo())
			return;

		if (pHttpClient->url_compre("/add"))
		{
			int a = pHttpClient->args_getInt("a", 0);
			int b = pHttpClient->args_getInt("b", 0);
			int c = a + b;

			char respBodyBuff[32] = {};
			sprintf(respBodyBuff, "a+b=%d", c);

			pHttpClient->resp200OK(respBodyBuff, strlen(respBodyBuff));
		}
		else if (pHttpClient->url_compre("/sub"))
		{
			int a = pHttpClient->args_getInt("a", 0);
			int b = pHttpClient->args_getInt("b", 0);
			int c = a - b;

			char respBodyBuff[32] = {};
			sprintf(respBodyBuff, "a-b=%d", c);

			pHttpClient->resp200OK(respBodyBuff, strlen(respBodyBuff));
		}
		else {
			std::string www = "E:/dev/www";
			www += pHttpClient->url();
			FILE * file = fopen(www.c_str(), "rb");
			if (file)
			{
				//获取文件大小
				fseek(file, 0, SEEK_END);
				auto bytesize = ftell(file);
				rewind(file);
				//
				char* buff = new char[bytesize];
				//读取
				auto readsize = fread(buff, 1, bytesize, file);
				if (readsize == readsize)
				{
					pHttpClient->resp200OK(buff, readsize);
					//释放内存
					delete[] buff;
					//关闭文件
					fclose(file);
					return;
				}
				//释放内存
				delete[] buff;
				//关闭文件
				fclose(file);
			}

			pHttpClient->resp404NotFound();
		}
	}
private:

};

int main(int argc, char* args[])
{
	//设置运行日志名称
	Log::Instance().setLogPath("serverLog", "w", false);
	Config::Instance().Init(argc, args);

	const char* strIP = Config::Instance().getStr("strIP", "any");
	uint16_t nPort = Config::Instance().getInt("nPort", 4567);
	int nThread = Config::Instance().getInt("nThread", 1);

	if (strcmp(strIP, "any") == 0)
	{
		strIP = nullptr;
	}

	MyServer server;
	if (Config::Instance().hasKey("-ipv6"))
	{
		CELLLog_Info("-ipv6");
		server.InitSocket(AF_INET6);
	}
	else {
		CELLLog_Info("-ipv4");
		server.InitSocket();
	}
	server.Bind(strIP, nPort);
	server.Listen(SOMAXCONN);
	server.Start(nThread);

	//在主线程中等待用户输入命令
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

//char htmlStr[] = 
//"\
//<!DOCTYPE html>\
//<html>\
//<head>\
//<title>HelloWeb</title>\
//</head>\
//<body>\
//    <button>GET</button>\
//	<button>POST</button>\
//</body>\
//</html>\
//";