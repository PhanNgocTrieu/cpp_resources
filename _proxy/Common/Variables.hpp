#ifndef _VARIABLE_H_
#define _VARIABLE_H_

#include <iostream>
#include "Logger.hpp"

class Account {
    public:
        Account(const std::string _usr, const std::string _pass)
        : m_logger(LoggerService::getInstance("Account")
        , m_usrName(_usr)
        , m_password(_pass)
        {
            LOG_INFO(m_logger, " Completed Create An Account " << _usr << " " << _pass);
        }

        std::string getName() const { return m_usrName; }
        std::string getPassword() const { return m_password; }

        bool operator==(const Account& other) {
            return (m_usrName == other.getName()) && (m_password == other.getPassword());
        }
    
    private:
        LoggerService* m_logger{nullptr};
        std::string m_usrName;
        std::string m_password;
};

#endif