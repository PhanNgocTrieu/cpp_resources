#include "Logger.h"

LoggerService *LoggerService::getInstance(const std::string &name)
{
    static LoggerService ins(name);
    return &ins;
}

std::string LoggerService::getName() const { return m_app; }