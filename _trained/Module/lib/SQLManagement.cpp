#include "SQLManagement.h"
#include <sqlite3.h>
#include <functional>
#include <iomanip>

namespace BackendLib { 
    int SQLAccessor::create_table(const std::string& _command) {
        WLOG_INF("create_table");
        sqlite3* data_base;
        auto _create_table = [this](sqlite3* db,const std::string& _com, char* _errmsg) -> int {
            /* Open db file*/
            int retCode = sqlite3_open(this->get_database_file_path(), &db);
            /* Handle opening file */
            if (retCode != SQLITE_OK) {
                WLOG_ERR("Open database file failed");
                return retCode;
            }
            
            WLOG_INF("Open database file successfully");
            /* Executing the command of creating table */
            retCode = sqlite3_exec(db, _com.c_str(), nullptr, 0, &_errmsg);
            if (retCode != SQLITE_OK) {
                WLOG_ERR("Executed command: create table failed");
                return retCode;
            }
            WLOG_INF("Executed command: create table successfully");

            /* Close db file */
            sqlite3_close(db);
        };
        
        (void)_create_table(data_base, _command, nullptr);
    }


    int SQLAccessor::execute_sql_commands(const std::string& _command, bool is_title) {
        sqlite3* db;
        char* errmsg = nullptr;
        /* Open db file*/
        int retCode = sqlite3_open(this->get_database_file_path(), &db);
        if (retCode != SQLITE_OK) {
            WLOG_ERR("Open database file failed");
            return retCode;
        }
        
        /* Executing the command of creating table */
        if (is_title) {
            retCode = sqlite3_exec(db, _command.c_str(), _callback_title, 0, &errmsg);
        }
        else {
            retCode = sqlite3_exec(db, _command.c_str(), _callback_handle, 0, &errmsg);
        }
        if (retCode != SQLITE_OK) {
            WLOG_ERR("Executed command: \"" + _command + "\": failed => " + std::string(errmsg));
            return retCode;
        }
        /* Close db file */
        sqlite3_close(db);
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
        std::cout << "|";
        for (int i = 0; i < argc; i++) {
            std::cout << std::left << std::setw(20) << std::setfill(' ') << argv[i] << "|";
        }
        printf("\n");
        return 0;
    }

    int _callback_title(void* data, int argc, char** argv, char** azColName) {
        int count = 0;
        std::cout << "|";
        for (int i = 0; i < argc; i++) {
            std::cout << std::left << std::setw(20) << std::setfill(' ') << azColName[i] << "|";
            count++;
        }
        std::cout << std::endl;
        std::cout << "  ";
        for (int idex = 0; idex < count * 20; idex++)
        {
            std::cout << "-";
        }
        printf("\n");
        return 0;
    }

}

