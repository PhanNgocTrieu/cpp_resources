#ifndef __PROXY_SERVICE_H__
#define __PROXY_SERVICE_H__
#include "Service.hpp"
#include "../Common/Variables.hpp"
#include <vector>
#include <unordered_map>
class ProxyService {
    public:
        ProxyService()
        : m_service {Service::instance()}
        , m_logger {LoggerService::getInstance("ProxyService")} {
            LOG_INFO(m_logger, " ProxyService was initialized ");
        }

        int requestValueInteger() const { 
            return m_service->getIntValue(); 
        }
        std::string requestValueString() const { 
            return m_service->getStringValue();
        }
        void requestSetValueInteger(const int _val) const { 
            return m_service->setIntValue(_val); 
        }
        void requestSetValueString(const std::string& _val) const { 
            return m_service->setStringValue(_val); 
        }

    protected:
        bool authenticate(const std::string username, const std::string password) {
            auto foundUsr = m_clients.find(username);
            if (foundUsr == m_clients.end()) {
                return false;
            }
            // Account other(username, password);
            // auto usr = foundUsr->second;
            // return other == usr;
            return true;
        }

    private:
        Service* m_service{nullptr};
        LoggerService* m_logger{nullptr};
        std::unordered_map<std::string, Account> m_clients;
};

#endif