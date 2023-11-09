#ifndef _SERVICE_INTERFACE_H
#define _SERVICE_INTERFACE_H
#include "../Models/Logger.hpp"
class Service {
    public:
        static Service* instance() {
            static Service _ins;
            return &_ins;
        }
        void setIntValue(const int val) { 
            LOG_INFO(m_logger, " setting integer value ");
            m_intValue = val; 
        }
        int getIntValue() const { 
            LOG_INFO(m_logger, " getting integer value ");
            return m_intValue;
        }

        void setStringValue(const std::string& val) { 
            LOG_INFO(m_logger, " setting string value ");
            m_stringValue = val; 
        }
        std::string getStringValue() const { 
            LOG_INFO(m_logger, " getting string value ");
            return m_stringValue; 
        }
    protected:
        int m_intValue{0};
        std::string m_stringValue{""};
    private:
        Service() :
        m_logger(LoggerService::getInstance("Service")) {

        }
        LoggerService* m_logger{nullptr};
};

#endif