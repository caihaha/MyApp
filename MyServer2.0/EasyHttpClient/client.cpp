#include"Config.hpp"
#include"TcpHttpClient.hpp"

using namespace doyou::io;

class MyHttpClient : public TcpHttpClient
{
public:
	void test()
	{
		static int i = 0;
		if (++i > 100)
			return;
		char reqBuff[256] = {};
		if (i%100 > 66)
		{
			sprintf(reqBuff, "http://192.168.88.128:4567/add?a=%d&b=1", i);
			this->get(reqBuff, [this](HttpClientC* pHttpClient) {
				if (pHttpClient)
				{
					CELLLog_Info("recv server msg. len=%s %d| %s",
						pHttpClient->header_getStr("Content-Length", "?"),
						i, pHttpClient->content());
					//CELLLog_Info("%s", pHttpClient->content());
				}
				else
				{
					CELLLog_Info("server disconnect. %d", i);
				}
				test();
			});
		}
		else if (i % 100 > 33)
		{
			sprintf(reqBuff, "http://192.168.88.128:4567/sub?a=%d&b=1", i);
			this->get(reqBuff, [this](HttpClientC* pHttpClient) {
				if (pHttpClient)
				{
					CELLLog_Info("recv server msg. len=%s %d| %s",
						pHttpClient->header_getStr("Content-Length", "?"),
						i, pHttpClient->content());
					//CELLLog_Info("%s", pHttpClient->content());
				}
				else
				{
					CELLLog_Info("server disconnect. %d", i);
				}
				test();
			});
		}
		else {
			sprintf(reqBuff, "token=abc123&json={\"a\":%d,\"b\":32}", i);
			this->post("http://192.168.88.128:4567/jsonTest", reqBuff, [this](HttpClientC* pHttpClient) {
				if (pHttpClient)
				{
					CELLLog_Info("recv server msg. len=%s %d| %s",
						pHttpClient->header_getStr("Content-Length", "?"),
						i, pHttpClient->content());
					//CELLLog_Info("%s", pHttpClient->content());
				}
				else
				{
					CELLLog_Info("server disconnect. %d", i);
				}
				test();
			});
		}

	}
};

int main(int argc, char *args[])
{
#if _WIN32 && _CONSOLE
	system("chcp 65001");
#endif
	
	//设置运行日志名称
	Log::Instance().setLogPath("clientLog", "w", false);
	Config::Instance().Init(argc, args);

	MyHttpClient httpClient;
	httpClient.test();
	/*
	TcpHttpClient httpClient;
	//1
	httpClient.get("http://192.168.88.128:4567/add?a=1&b=1", [&httpClient](HttpClientC* pHttpClient) {
		if (!pHttpClient)
			return;
		CELLLog_Info("recv server msg.1 :%s", pHttpClient->content());
		httpClient.get("http://192.168.88.128:4567/add?a=2&b=1", [](HttpClientC* pHttpClient) {
			if (!pHttpClient)
				return;
			CELLLog_Info("recv server msg.2 :%s", pHttpClient->content());
		});
	});
	//2
	httpClient.post("http://192.168.88.128:4567/add?a=3&b=1", [&httpClient](HttpClientC* pHttpClient) {
		if (!pHttpClient)
			return;
		CELLLog_Info("recv server msg.3 :%s", pHttpClient->content());
		httpClient.post("http://192.168.88.128:4567/add?a=4&b=1", [](HttpClientC* pHttpClient) {
			if (!pHttpClient)
				return;
			CELLLog_Info("recv server msg.4 :%s", pHttpClient->content());
		});
	});
	//3
	httpClient.post("http://192.168.88.128:4567/add?a=5&b=1", [&httpClient](HttpClientC* pHttpClient) {
		if (!pHttpClient)
			return;
		CELLLog_Info("recv server msg.5 :%s", pHttpClient->content());
		httpClient.get("http://192.168.88.128:4567/add?a=6&b=1", [](HttpClientC* pHttpClient) {
			if (!pHttpClient)
				return;
			CELLLog_Info("recv server msg.6 :%s", pHttpClient->content());
		});
	});

	httpClient.post("http://192.168.88.128:4567/jsonTest", "token=abc123&json={\"a\":100,\"b\":32}", [&httpClient](HttpClientC* pHttpClient) {
		if (!pHttpClient)
			return;
		CELLLog_Info("recv json msg.1 :%s", pHttpClient->content());
		httpClient.post("http://192.168.88.128:4567/jsonTest?token=abc123&json={\"a\":200,\"b\":78}", [](HttpClientC* pHttpClient) {
			if (!pHttpClient)
				return;
			CELLLog_Info("recv json msg.2 :%s", pHttpClient->content());
		});
	});
	*/

	//httpClient.get("www.163.com"，callBack1);
	//httpClient.get("www.baidu.com"，callBack2);
	//httpClient.get("www.qq.com"，callBack3);
	//httpClient.get("www.cnblog.com"，callBack4);

	while (true)
	{
		httpClient.OnRun(1);
		//httpClient1.OnRun(1);
	}
	httpClient.Close();
	return 0;
}