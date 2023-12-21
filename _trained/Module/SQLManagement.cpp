#include "SQLManagement.h"
#include <sqlite3.h>
#include <functional>



namespace BackendLib { 
    int SQLAccessor::create_table(const std::string& _command) {
        WLOG_INF("create_table");
        sqlite3* data_base;
        char *errmsg;
        auto _create_table = [this](sqlite3* db,const std::string& _com, char* _errmsg) -> int {
            int retCode = sqlite3_open(this->get_database_file_path(), &db);
            if (retCode != SQLITE_OK) {
                WLOG_ERR("Open database file failed");
                return retCode;
            }

            retCode = sqlite3_exec(db, _com.c_str(), _callback_handle, 0, &_errmsg);
        };
        

    }

    int SQLAccessor::insert_table(const std::string& _command) {
    }

    const char* SQLAccessor::get_database_file_path() const {
        return this->m_dbPath.c_str();
    }

    SQLAccessor::SQLAccessor(const std::string& _file) :
    m_dbPath(_file)
    {}


    int _callback_handle(void* data, int argc, char** argv, char** azColName) {
    }
}

