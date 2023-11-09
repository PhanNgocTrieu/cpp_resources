#ifndef __APPLICATION_TWO__
#define __APPLICATION_TWO__

#include "Proxy.hpp"

class Application_Two {
    public:
        Application_Two(ServiceWrapper* _service)
        : m_proxyService (ProxyService::instance()) {
            m_proxyService->setObject(_service);
        }

        ~Application_Two() { }
        
        void requestValue() {
            m_proxyService->requestValue();
        }
    
    protected:
        ProxyService* m_proxyService;
};

#endif // __APPLICATION_TWO__