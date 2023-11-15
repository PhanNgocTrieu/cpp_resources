#ifndef _SERVICE_INTERFACE_H
#define _SERVICE_INTERFACE_H

#include "Logger.h"

class Service {
    public:
        static Service* instance();
        void setIntValue(const int val);
        int getIntValue() const;
        void setStringValue(const std::string& val);
        std::string getStringValue() const;

    protected:
        int m_intValue{0};
        std::string m_stringValue{""};

    private:
        Service();
        LoggerService* m_logger{nullptr};
};

#endif