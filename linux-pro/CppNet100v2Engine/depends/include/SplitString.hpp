#ifndef _doyou_io_SplitString_HPP_
#define _doyou_io_SplitString_HPP_

#include<string>

namespace doyou {
	namespace io {
		class SplitString
		{
		private:
			char* _str = nullptr;
			bool _first = true;
		public:
			void set(char* str)
			{
				_str = str;
				_first = true;
			}

			char* get(char end)
			{
				if (!_str)
					return nullptr;
				//str="GET /login.php?a=5 HTTP/1.1"
				char* temp = strchr(_str, end);
				if (!temp)
				{
					if (_first)
					{
						_first = false;
						return _str;
					}
					return nullptr;
				}
				//str="GET\0/login.php?a=5 HTTP/1.1"
				temp[0] = '\0';
				//ret="GET\0
				char* ret = _str;
				//str="/login.php?a=5 HTTP/1.1"
				_str = temp + 1;

				return ret;
			}

			char* get(const char* end)
			{
				if (!_str || !end)
					return nullptr;

				char* temp = strstr(_str, end);
				if (!temp)
				{
					if (_first)
					{
						_first = false;
						return _str;
					}
					return nullptr;
				}
				temp[0] = '\0';
				char* ret = _str;
				_str = temp + strlen(end);

				return ret;
			}
		};
	}
}
#endif // !_doyou_io_SplitString_HPP_
