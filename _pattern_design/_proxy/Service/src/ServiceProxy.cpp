#include "ServiceProxy.h"

ProxyService::ProxyService()
    : m_service{Service::instance()}, m_logger{LoggerService::getInstance("ProxyService")}
{
    LOG_INFO(m_logger, " ProxyService was initialized ");
}

int ProxyService::requestValueInteger() const
{
    return m_service->getIntValue();
}

std::string ProxyService::requestValueString() const
{
    return m_service->getStringValue();
}

void ProxyService::requestSetValueInteger(const int _val) const
{
    return m_service->setIntValue(_val);
}

void ProxyService::requestSetValueString(const std::string &_val) const
{
    return m_service->setStringValue(_val);
}

bool ProxyService::authenticate(const std::string username, const std::string password)
{
    auto foundUsr = m_clients.find(username);
    if (foundUsr == m_clients.end())
    {
        return false;
    }
    // Account other(username, password);
    // auto usr = foundUsr->second;
    // return other == usr;
    return true;
}