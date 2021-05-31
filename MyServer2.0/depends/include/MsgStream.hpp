#ifndef _CELL_MSG_STREAM_HPP_
#define _CELL_MSG_STREAM_HPP_

#include"MessageHeader.hpp"
#include"ByteStream.hpp"
namespace doyou {
	namespace io {
		//消息数据字节流
		class ReadByteStream :public ByteStream
		{
		public:
			ReadByteStream(netmsg_DataHeader* header)
				:ReadByteStream((char*)header, header->dataLength)
			{

			}

			ReadByteStream(char* pData, int nSize, bool bDelete = false)
				:ByteStream(pData, nSize, bDelete)
			{
				push(nSize);
				////预先读取消息长度
				//ReadInt16();
				////预先读取消息命令
				//getNetCmd();
			}

			uint16_t getNetCmd()
			{
				uint16_t cmd = CMD_ERROR;
				Read<uint16_t>(cmd);
				return cmd;
			}
			//////Read
			template<typename T>
			bool Read(T& n, bool bOffset = true)
			{
				//
				//计算要读取数据的字节长度
				auto nLen = sizeof(T);
				//判断能不能读
				if (canRead(nLen))
				{
					//将要读取的数据 拷贝出来
					memcpy(&n, _pBuff + _nReadPos, nLen);
					//计算已读数据位置
					if (bOffset)
						pop(nLen);
					return true;
				}
				//断言assert
				//错误日志
				CELLLog_Error("error, ByteStream::Read failed.");
				return false;
			}

			template<typename T>
			bool onlyRead(T& n)
			{
				return Read(n, false);
			}

			template<typename T>
			uint32_t ReadArray(T* pArr, uint32_t len)
			{
				uint32_t len1 = 0;
				//读取数组元素个数,但不偏移读取位置
				Read(len1, false);
				//判断缓存数组能否放得下
				if (len1 <= len)
				{
					//计算数组的字节长度
					auto nLen = len1 * sizeof(T);
					//判断能不能读出
					if (canRead(nLen + sizeof(uint32_t)))
					{
						//计算已读位置+数组长度所占有空间
						pop(sizeof(uint32_t));
						//将要读取的数据 拷贝出来
						memcpy(pArr, _pBuff + _nReadPos, nLen);
						//计算已读数据位置
						pop(nLen);
						return len1;
					}
				}
				CELLLog_Error("ByteStream::ReadArray failed.");
				return 0;
			}

			//char size_t c# char2 char 1 
			int8_t ReadInt8(int8_t def = 0)
			{
				Read(def);
				return def;
			}
			//short
			int16_t ReadInt16(int16_t n = 0)
			{
				Read(n);
				return n;
			}
			//int
			int32_t ReadInt32(int32_t n = 0)
			{
				Read(n);
				return n;
			}

			int64_t ReadInt64(int64_t n = 0)
			{
				Read(n);
				return n;
			}

			uint8_t ReadUInt8(uint8_t def = 0)
			{
				Read(def);
				return def;
			}
			//short
			uint16_t ReadUInt16(uint16_t n = 0)
			{
				Read(n);
				return n;
			}
			//int
			uint32_t ReadUInt32(uint32_t n = 0)
			{
				Read(n);
				return n;
			}

			uint64_t ReadUInt64(uint64_t n = 0)
			{
				Read(n);
				return n;
			}

			float ReadFloat(float n = 0.0f)
			{
				Read(n);
				return n;
			}
			double ReadDouble(double n = 0.0f)
			{
				Read(n);
				return n;
			}

			bool ReadString(std::string& str)
			{
				uint32_t nLen = 0;
				Read(nLen, false);
				if (nLen > 0)
				{
					//判断能不能读出
					if (canRead(nLen + sizeof(uint32_t)))
					{
						//计算已读位置+数组长度所占有空间
						pop(sizeof(uint32_t));
						//将要读取的数据 拷贝出来
						str.insert(0, _pBuff + _nReadPos, nLen);
						//计算已读数据位置
						pop(nLen);
						return true;
					}
				}
				return false;
			}
		};

		//消息数据字节流
		class WriteByteStream :public ByteStream
		{
		public:
			WriteByteStream(char* pData, int nSize, bool bDelete = false)
				:ByteStream(pData, nSize, bDelete)
			{
				//预先占领消息长度所需空间
				Write<uint16_t>(0);
			}

			WriteByteStream(int nSize = 1024)
				:ByteStream(nSize)
			{
				//预先占领消息长度所需空间
				Write<uint16_t>(0);
			}

			void setNetCmd(uint16_t cmd)
			{
				Write<uint16_t>(cmd);
			}

			bool WriteString(const char* str, int len)
			{
				return WriteArray(str, len);
			}

			bool WriteString(const char* str)
			{
				return WriteArray(str, strlen(str));
			}

			bool WriteString(std::string& str)
			{
				return WriteArray(str.c_str(), str.length());
			}

			void finsh()
			{
				int pos = length();
				setWritePos(0);
				Write<uint16_t>(pos);
				setWritePos(pos);
			}

			//////Write
			template<typename T>
			bool Write(T n)
			{
				//计算要写入数据的字节长度
				auto nLen = sizeof(T);
				//判断能不能写入
				if (canWrite(nLen))
				{
					//将要写入的数据 拷贝到缓冲区尾部
					memcpy(_pBuff + _nWritePos, &n, nLen);
					//计算已写入数据尾部位置
					push(nLen);
					return true;
				}
				CELLLog_Error("ByteStream::Write failed.");
				return false;
			}
			template<typename T>
			bool WriteArray(T* pData, uint32_t len)
			{
				//计算要写入数组的字节长度
				auto nLen = sizeof(T)*len;
				//判断能不能写入
				if (canWrite(nLen + sizeof(uint32_t)))
				{
					//先写入数组的元素数量
					Write(len);
					//将要写入的数据 拷贝到缓冲区尾部
					memcpy(_pBuff + _nWritePos, pData, nLen);
					//计算数据尾部位置
					push(nLen);
					return true;
				}
				CELLLog_Error("ByteStream::WriteArray failed.");
				return false;
			}

			//char
			bool WriteInt8(int8_t n)
			{
				return Write(n);
			}
			//short
			bool WriteInt16(int16_t n)
			{
				return Write(n);
			}

			//int
			bool WriteInt32(int32_t n)
			{
				return Write(n);
			}

			bool WriteFloat(float n)
			{
				return Write(n);
			}

			bool WriteDouble(double n)
			{
				return Write(n);
			}
		};

	}
}
#endif // !_CELL_MSG_STREAM_HPP_
