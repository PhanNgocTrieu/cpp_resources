#ifndef __SQLITE_MANAGEMENT_H__
#define __SQLITE_MANAGEMENT_H__

#include "Logger.h"
#include <iostream>

namespace BackendLib {
    class SQLAccessor {
        public:
            static SQLAccessor* getInstance(const std::string& _file) {
                static SQLAccessor _ins(_file);
                return &_ins;
            }

            int create_table(const std::string& _command);
            int insert_table(const std::string& _command);


            const char* get_database_file_path() const;
            int _callback(void *, int, char**, char*);
        protected:

        protected:
            std::string m_dbPath{""};
            WLOG_DEF("SQLAccessor");

        private:
            SQLAccessor(const std::string& _file);
            SQLAccessor(const SQLAccessor&) = delete;
            SQLAccessor& operator=(SQLAccessor&&) = delete;
    };

    static int _callback_handle(void* data, int argc, char** argv, char** azColName);
}

#endif /* __SQLITE_MANAGEMENT */