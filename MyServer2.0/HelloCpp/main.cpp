#include"Log.hpp"
using namespace doyou::io;

int main()
{
	Log::Instance().setLogPath("HelloCpp.log","w",false);

	CELLLog_Info("a=%s","dasdas");
	{
		std::string log1 = "µÚ¶þ¶Î×Ö·û´®";
		char log2[] = "µÚÈý¶Î×Ö·û´®";
		const char* log3 = "µÚËÄ¶Î×Ö·û´®";
		Log::Info("µÚÒ»¶Î×Ö·û´®");
		Log::Info(log1.c_str());
		Log::Info(log2);
		Log::Info(log3);
	}

	return 0;
}