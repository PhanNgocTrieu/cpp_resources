#include "Logger.h"
#include <vector>
namespace Modules {
    LoggerService* LoggerService::get_instance(const std::string& name) {
        static LoggerService instance(name);
        return &instance;
    }

    void LoggerService::create_record(const LoggerService::LogLevel& _level, const std::string& message) {
        std::cout << "[\033[1;30m" << this->_pretty(_level) << "\033[0m][\033[1;31m" 
                    << this->get_module() << "\033[0m][\033[1;32m" 
                    << __FUNCTION__ << "\033[0m][" << __LINE__ << "]: " 
                    << message << std::endl; \
    }

    std::string LoggerService::_pretty(const LoggerService::LogLevel& _level) {
        static std::vector<std::string> _level_ = {
            "INFO",
            "DEBUG",
            "WARN",
            "ERROR",
            "FATAL"
        };

        auto idx = static_cast<int>(_level);
        if (idx < 0 || idx > _level_.size()) {
            return "LOGGER_LEVEL";
        }

        return _level_[idx];
    }

    std::string LoggerService::get_module() const{
        return m_module;
    }

    LoggerService::~LoggerService() {
    }

    
    LoggerService::LoggerService() {
    }

    LoggerService::LoggerService(const std::string& name)
    : m_module(name) 
    {
    }
}