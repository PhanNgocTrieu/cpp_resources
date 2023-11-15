#ifndef __PROXY_H__
#define __PROXY_H__

#include "Service.hpp"
#include "Interface.hpp"

class ProxyService : public Interface {
    public:

        static ProxyService* instance() {
            static ProxyService _ins;
            return &_ins;
        }

        virtual ~ProxyService() {
            release();
        }

        virtual std::string requestValue() override {
            if (checkAccess() && m_wrapper != nullptr) {
                std::string message = m_wrapper->requestValue();
                logMessage(message);
                return message;
            }
            logMessage("No message");
            return "No message";
        }

        virtual void setStringValue(const std::string& value) override { }
        
        void setObject(ServiceWrapper* _sevice) {
            m_wrapper = _sevice;
        }

        // In Proxy would use to checking something to make sure that the service object is correct one
        bool checkAccess() {
            std::cout << " [ProxyService][checkAccess]: perform checking... "<< std::endl;
            return true;
        }

        void logMessage(const std::string& message) {
            std::cout << " [ProxyService][logMessage]: message of service " << message << std::endl;
        }

    protected:
        void release() {
            std::cout << " [ProxyService][release]: service address " << &m_wrapper << std::endl;
        }
        // Initialize the ProxyService to the Service Object
        ProxyService() { }

        // Reference to ther service object which contains the data
        ServiceWrapper* m_wrapper {nullptr};
};

#endif // __PROXY_H__