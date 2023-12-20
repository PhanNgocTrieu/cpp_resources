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
        public:
            enum FileMode {
                READ = 0,
                WRITE,
                RDWD
            };

            struct ConfigurationManager {
                std::string m_sqlFileName{_SQL_FILE_CONFIG_PATH};
                FileMode m_mode;
            };

        public:
            static ContentProvider* getInstance();
            ~ContentProvider();
            void initialize();

        protected:
            ContentProvider();
            void readContentProvider();
            /* Block = operator and copy object */
            ContentProvider(const ContentProvider&) = delete;
            ContentProvider& operator=(ContentProvider&&) = delete;

        private:
            std::unordered_map<std::string, std::string> m_configTableMap;
            ConfigurationManager* m_configManager;
            bool m_isReady{false};
    };
};

#endif