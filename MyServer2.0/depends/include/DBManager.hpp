#ifndef _doyou_io_DBManager_HPP_
#define _doyou_io_DBManager_HPP_

#include"Log.hpp"
#include"CppSQLite3.h"

namespace doyou {
	namespace io {
		class DBManager
		{
		protected:
			CppSQLite3DB _db;
			std::string _db_name;
		public:
			bool open(const char* db_name)
			{
				_db_name = db_name;
				try
				{
					_db.open(db_name);
					return true;
				}
				catch (CppSQLite3Exception& e)
				{
					CELLLog_Error("DBManager::open(%s) error: %s", db_name, e.errorMessage());
				}
				return false;
			}

			bool close()
			{
				try
				{
					_db.close();
					return true;
				}
				catch (CppSQLite3Exception& e)
				{
					CELLLog_Error("DBManager::close(%s) error: %s", _db_name.c_str(), e.errorMessage());
				}
				return false;
			}

			bool hasByKV(const char* table, const char* k, const char* v)
			{
				char sql_buff[1024] = {};
				auto sql = "SELECT 1 FROM %s WHERE %s='%s' LIMIT 1;";
				sprintf(sql_buff, sql, table, k, v);

				try
				{
					CppSQLite3Query query = _db.execQuery(sql_buff);
					return !query.eof();
				}
				catch (CppSQLite3Exception& e)
				{
					CELLLog_Error("DBManager::hasByKV(%s) error: %s", _db_name.c_str(), e.errorMessage());
				}
				return false;
			}

			bool findByKV(const char* table, const char* k, const char* v, neb::CJsonObject& json)
			{
				char sql_buff[1024] = {};
				auto sql = "SELECT * FROM %s WHERE %s='%s';";
				sprintf(sql_buff, sql, table, k, v);

				try
				{
					CppSQLite3Query query = _db.execQuery(sql_buff);
					while (!query.eof())
					{
						neb::CJsonObject row;
						int num = query.numFields();
						for (int n = 0; n < num; n++)
						{
							auto k = query.fieldName(n);
							auto kType = query.fieldDataType(n);
							if (SQLITE_INTEGER== kType)
							{
								int64 v = query.getInt64Field(k, 0);
								row.Add(k, v);
							}
							else if (SQLITE_TEXT == kType)
							{
								auto v = query.getStringField(k);
								row.Add(k, v);
							}
							else if (SQLITE_FLOAT == kType)
							{
								auto v = query.getFloatField(k);
								row.Add(k, v);
							}
							else if (SQLITE_BLOB == kType)
							{
								//int nLen = 0;
								//auto v = query.getBlobField(k, nLen);
								//将数据拷贝到由我们控制的BLOB数据内存中管理
								//row.Add新的BLOB数据地址
								//row.Add(k, (uint64)v);
							}
							else if (SQLITE_NULL == kType)
							{
								//row.Add(k, "NULL");
							}
						}
						json.Add(row);
						query.nextRow();
					}
				}
				catch (CppSQLite3Exception& e)
				{
					CELLLog_Error("DBManager::findByKV(%s) error: %s", _db_name.c_str(), e.errorMessage());
					return false;
				}
				return true;
			}
		};
	}
}
#endif // !_doyou_io_DBManager_HPP_
