#include "Service.h"

Service *Service::instance()
{
    static Service _ins;
    return &_ins;
}

void Service::setIntValue(const int val)
{
    LOG_INFO(m_logger, " setting integer value ");
    m_intValue = val;
}

int Service::getIntValue() const
{
    LOG_INFO(m_logger, " getting integer value ");
    return m_intValue;
}

void Service::setStringValue(const std::string &val)
{
    LOG_INFO(m_logger, " setting string value ");
    m_stringValue = val;
}

std::string Service::getStringValue() const
{
    LOG_INFO(m_logger, " getting string value ");
    return m_stringValue;
}

Service::Service() : m_logger(LoggerService::getInstance("Service"))
{
}