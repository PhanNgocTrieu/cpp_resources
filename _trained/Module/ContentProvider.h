#ifndef __CONTENT_PROVIDER_H__
#define __CONTENT_PROVIDER_H__
#include <iostream>
#include <string>
#include <sqlite3.h>
#include <unordered_map>

#define _SQL_FILE_PATH_ "/var/bin/sqlite.db"
#define _SQL_FILE_CONFIG_PATH_ "./config.cfg"

namespace Modules { 

    class ContentProvider {
        private:
            std::string m_sqlFileName{_SQL_FILE_CONFIG_PATH_};
            FILE* m_fileHandle{nullptr};
            bool m_isReady{false};
            std::unordered_map<std::string, std::string> m_configTableMap;

        public:
            static ContentProvider* getInstance();
            ~ContentProvider();
            void initialize();

        protected:
            ContentProvider();
            /* Block = operator and copy object */
            ContentProvider(const ContentProvider&) = delete;
            ContentProvider& operator=(ContentProvider&&) = delete;
    };
};

#endif