#ifndef _doyou_io_DBUser_HPP_
#define _doyou_io_DBUser_HPP_

#include"Log.hpp"
#include"DBManager.hpp"

namespace doyou {
	namespace io {

		//消息分发
		class DBUser:public DBManager
		{
		protected:
			int64 _max_userId = 100000;
		public:
			~DBUser()
			{
				close();
			}
		protected:
			int64 makeId()
			{
				return _max_userId+1;
			}

			void load_id()
			{
				try
				{
					CppSQLite3Query query = _db.execQuery("SELECT MAX(userId) FROM user_info;");
					if (query.eof())
						return;
					
					auto max_id = query.getInt64Field("MAX(userId)", 0);
					if (max_id == 0)
						return;

					_max_userId = max_id;
				}
				catch (CppSQLite3Exception& e)
				{
					CELLLog_Error("DBManager::hasByKV(%s) error: %s", _db_name.c_str(), e.errorMessage());
				}
			}

			bool create_table_user_info()
			{
				auto sql =
					"\
CREATE TABLE user_info(\
	id          INTEGER PRIMARY KEY,\
	userId      INTEGER UNIQUE,\
	username    TEXT    UNIQUE,\
	password    TEXT    NOT NULL,\
	nickname    TEXT    UNIQUE,\
	sex         INTEGER,\
	state       INTEGER,\
	create_date INTEGER\
);\
";
				try
				{
					if (!_db.tableExists("user_info"))
					{
						_db.execDML(sql);
					}
					return true;
				}
				catch (CppSQLite3Exception& e)
				{
					CELLLog_Error("DBManager::create_table_user_info(%s) error: %s", _db_name.c_str(), e.errorMessage());
				}
				return false;
			}
		public:
			void init()
			{
				if (!open("user.db"))
					return;

				if (!create_table_user_info())
					return;

				load_id();
			}

			bool has_username(const std::string& username)
			{
				return hasByKV("user_info", "username", username.c_str());
			}

			bool has_nickname(const std::string& nickname)
			{
				return hasByKV("user_info", "nickname", nickname.c_str());
			}

			int64 add_user(const std::string& username, const std::string& password, const std::string& nickname, int sex)
			{
				int64 userId = makeId();
				char sql_buff[1024] = {};
#ifdef _WIN32
				auto sql = "INSERT INTO user_info (userId, username, password, nickname, sex, state, create_date) VALUES (%I64d, '%s', '%s', '%s', %d, %d, %I64d);";
#else
				auto sql = "INSERT INTO user_info (userId, username, password, nickname, sex, state, create_date) VALUES (%lld, '%s', '%s', '%s', %d, %d, %lld);";
#endif
				sprintf(sql_buff, sql, userId, username.c_str(), password.c_str(), nickname.c_str(), sex, 0, Time::system_clock_now());
				try
				{
					int changes = _db.execDML(sql_buff);
					CELLLog_Info("DBUser::add_user changes=%d", changes);
					if (changes > 0)
					{
						++_max_userId;
						return userId;
					}
				}
				catch (CppSQLite3Exception& e)
				{
					CELLLog_Error("DBUser::add_user(%s) error: %s", _db_name.c_str(), e.errorMessage());
				}
				return 0;
			}


		};
	}
}
#endif // !_doyou_io_DBUser_HPP_
