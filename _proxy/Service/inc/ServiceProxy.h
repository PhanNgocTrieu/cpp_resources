#ifndef __PROXY_SERVICE_H__
#define __PROXY_SERVICE_H__
#include "Service.h"
#include "../../Common/Variables.hpp"
#include <vector>
#include <unordered_map>

class ProxyService {
    public:
        ProxyService();
        int requestValueInteger() const;
        std::string requestValueString() const;
        void requestSetValueInteger(const int _val) const;
        void requestSetValueString(const std::string& _val) const;

    protected:
        bool authenticate(const std::string username, const std::string password);

    private:
        Service* m_service{nullptr};
        LoggerService* m_logger{nullptr};
        std::unordered_map<std::string, Account> m_clients;
};

#endif