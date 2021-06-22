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
		};
	}
}
#endif // !_doyou_io_DBManager_HPP_
