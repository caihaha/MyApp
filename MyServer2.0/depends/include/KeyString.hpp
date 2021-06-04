#ifndef _doyou_io_KeyString_HPP_
#define _doyou_io_KeyString_HPP_

#include<cstring>

namespace doyou {
	namespace io {
		class KeyString
		{
		private:
			const char* _str = nullptr;
		public:
			KeyString(const char* str)
			{
				set(str);
			}

			void set(const char* str)
			{
				_str = str;
			}

			const char* get()
			{
				return _str;
			}

			//bool operator < (const KeyString& right)
			//{
			//	return strcmp(this->_str, right._str) < 0;
			//}

			friend bool operator < (const KeyString& left, const KeyString& right);
		};

		bool operator < (const KeyString& left, const KeyString& right)
		{
			return strcmp(left._str, right._str) < 0;
		}

		//bool operator < (const KeyString& left, const KeyString& right)
		//{
		//	return left < right;
		//}
	}
}
#endif // !_doyou_io_KeyString_HPP_
