#ifndef _CELL_STREAM_HPP_
#define _CELL_STREAM_HPP_

#include"Log.hpp"
#include<cstdint>
#include<string>
namespace doyou {
	namespace io {
		//字节流BYTE
		class ByteStream
		{
		public:

			ByteStream(char* pData, int nSize, bool bDelete = false)
			{
				_nSize = nSize;
				_pBuff = pData;
				_bDelete = bDelete;
			}


			ByteStream(int nSize = 1024)
			{
				_nSize = nSize;
				_pBuff = new char[_nSize];
				_bDelete = true;
			}

			virtual ~ByteStream()
			{
				if (_bDelete && _pBuff)
				{
					delete[] _pBuff;
					_pBuff = nullptr;
				}
			}
		public:

			char* data()
			{
				return _pBuff;
			}

			int length()
			{
				return _nWritePos;
			}

			//内联函数
			//还能读出n字节的数据吗?
			inline bool canRead(int n)
			{
				return _nSize - _nReadPos >= n;
			}
			//还能写入n字节的数据吗?
			inline bool canWrite(int n)
			{
				return _nSize - _nWritePos >= n;
			}
			//已写入位置，添加n字节长度
			inline void push(int n)
			{
				_nWritePos += n;
			}
			//已读取位置，添加n字节长度
			inline void pop(int n)
			{
				_nReadPos += n;
			}

			inline void setWritePos(int n)
			{
				_nWritePos = n;
			}
		protected:
			//数据缓冲区
			char* _pBuff = nullptr;
			//缓冲区总的空间大小，字节长度
			int _nSize = 0;
			//已写入数据的尾部位置，已写入数据长度
			int _nWritePos = 0;
			//已读取数据的尾部位置
			int _nReadPos = 0;
			//_pBuff是外部传入的数据块时是否应该被释放
			bool _bDelete = true;
		};
	}
}

#endif // !_CELL_STREAM_HPP_
