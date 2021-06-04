#include"Log.hpp"
#include"Config.hpp"
#include"TcpHttpClient.hpp"

using namespace std;
using namespace doyou::io;

class MyClient : public TcpHttpClient
{
public:
	MyClient()
	{
	}

	virtual void OnNetMsg(netmsg_DataHeader* header) override
	{

	}

	void getData(const char* url)
	{
		Connect("127.0.0.1", 4567);
	}

private:

};

int main(int argc, char* args[])
{
	//设置运行日志名称
	Log::Instance().setLogPath("clientLog", "w", false);

	Config::Instance().Init(argc, args);

	MyClient* pClient = new MyClient();
	pClient->InitSocket(AF_INET, 10240, 10240);
	pClient->getData("www.com");

	pClient->Close();

}