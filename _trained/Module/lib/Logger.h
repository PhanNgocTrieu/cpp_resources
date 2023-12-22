#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <iostream>

#define WLOG_DEF(M) \
    mutable Modules::LoggerService* m_logger = Modules::LoggerService::get_instance(M); \

#define WLOG_INF(N)     m_logger->create_record(Modules::LoggerService::LogLevel::INFO,     N);
#define WLOG_DBG(N)     m_logger->create_record(Modules::LoggerService::LogLevel::DEBUG,    N);
#define WLOG_WRN(N)     m_logger->create_record(Modules::LoggerService::LogLevel::WARN,     N);
#define WLOG_ERR(N)     m_logger->create_record(Modules::LoggerService::LogLevel::ERROR,    N);
#define WLOG_FTL(N)     m_logger->create_record(Modules::LoggerService::LogLevel::FATAL,    N);


namespace Modules {
    class LoggerService {
        public:
            enum LogLevel {
                INFO = 0,
                DEBUG,
                WARN,
                ERROR,
                FATAL
            };

        public:
            static LoggerService* get_instance(const std::string& name);
            ~LoggerService();
            std::string get_module() const;
            void create_record(const LogLevel& _level, const std::string& message);

        protected:
            std::string _pretty(const LogLevel& _level);
            std::string m_module{"LOGGER"};

        private:
            LoggerService();
            LoggerService(const std::string& name);
    };
} // namespace Modules

#endif