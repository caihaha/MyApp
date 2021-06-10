#include"Config.hpp"
#include"TcpWebSocketClient.hpp"

using namespace doyou::io;

int main(int argc, char *args[])
{
#if _WIN32 && _CONSOLE
	system("chcp 65001");
#endif

	//设置运行日志名称
	Log::Instance().setLogPath("clientLog", "w", false);
	Config::Instance().Init(argc, args);

	TcpWebSocketClient wsClient;
	wsClient.connect("ws://192.168.0.100:4567/");

	wsClient.onopen = [](WebSocketClientC* pWSClient)
	{
		std::string msg = "bu hao.";
		for (int i = 0; i < 10; i++)
			msg += "-hello web";
		msg += "===";
		pWSClient->writeText(msg.c_str(), msg.length());

		pWSClient->ping();
	};

	wsClient.onmessage = [&wsClient](WebSocketClientC* pWSClient)
	{
		WebSocketHeader& wsh = pWSClient->WebsocketHeader();
		if (wsh.opcode == opcode_PONG)
		{
			CELLLog_Info("websocket server say: PONG");
			return;
		}

		auto data = pWSClient->fetch_data();
		CELLLog_Info("websocket server say: %s", data);
		
		//pWSClient->writeText(data, wsh.len);

		//pWSClient->onClose();
	};

	wsClient.onclose = [](WebSocketClientC* pWSClient)
	{
		CELLLog_Info("websocket client onclose!");
	};

	wsClient.onerror = [](WebSocketClientC* pWSClient)
	{
		CELLLog_Info("websocket client onerror!");
	};

	while (wsClient.isRun())
	{
		wsClient.OnRun(1);
		//httpClient1.OnRun(1);
	}
	wsClient.Close();
	return 0;
}