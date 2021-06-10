#include"Log.hpp"
#include"Config.hpp"
#include"TcpHttpServer.hpp"

using namespace doyou::io;

class MyServer:public TcpHttpServer
{
public:
	virtual void OnNetMsgHttp(Server* pServer, HttpClientS* pHttpClient)
	{
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
		else if (pHttpClient->url_compre("/jsonTest"))
		{
			auto tokenStr = pHttpClient->args_getStr("token", nullptr);
			if (tokenStr)
			{
				//对tokenStr进行身份验证
				auto jsonStr = pHttpClient->args_getStr("json", "no json data");
				//使用第三方json库解析jsonStr
				//做出相应处理
				//反馈结果
				pHttpClient->resp200OK(jsonStr, strlen(jsonStr));
			}
			else
			{
				auto ret = "{\"status\":\"error\"}";
				pHttpClient->resp200OK(ret, strlen(ret));
			}
		}
		else {
			if (!respFile(pHttpClient))
			{
				pHttpClient->resp404NotFound();
			}
		}
	}

	bool respFile(HttpClientS* pHttpClient)
	{
		std::string filePath;

		if (pHttpClient->url_compre("/"))
		{
			filePath = _wwwRoot + pHttpClient->url() + _indexPage;
		}
		else {
			filePath = _wwwRoot + pHttpClient->url();
		}

		FILE * file = fopen(filePath.c_str(), "rb");
		if (!file)
			return false;

		//获取文件大小
		fseek(file, 0, SEEK_END);
		auto bytesize = ftell(file);
		rewind(file);

		//发送缓冲区是否能写入这么多数据
		if (!pHttpClient->canWrite(bytesize))
		{
			CELLLog_Warring("!pHttpClient->canWrite(bytesize), url=%s", filePath.c_str());
			fclose(file);
			return false;
		}

		//读取
		char* buff = new char[bytesize];
		auto readsize = fread(buff, 1, bytesize, file);
		if (readsize != bytesize)
		{
			CELLLog_Warring("readsize != bytesize, url=%s", filePath.c_str());
			//释放内存
			delete[] buff;
			//关闭文件
			fclose(file);
			return false;
		}

		pHttpClient->resp200OK(buff, readsize);

		//释放内存
		delete[] buff;
		//关闭文件
		fclose(file);

		return true;
	}

	void wwwRoot(const char* www)
	{
		_wwwRoot = www;
	}

	void indexPage(const char* index)
	{
		_indexPage = index;
	}
private:
	std::string _wwwRoot;
	std::string _indexPage;
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

	const char* wwwroot = Config::Instance().getStr("wwwroot", "E:/www");
	const char* indexpage = Config::Instance().getStr("indexpage", "index.html");
	server.wwwRoot(wwwroot);
	server.indexPage(indexpage);

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
