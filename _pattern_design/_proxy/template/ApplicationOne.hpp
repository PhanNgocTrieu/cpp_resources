#ifndef __APPLICATION_ONE__
#define __APPLICATION_ONE__

#include "Proxy.hpp"

class Application_One {
    public:
        Application_One(ServiceWrapper* _service)
        : m_proxyService (ProxyService::instance()) {
            m_proxyService->setObject(_service);
        }

        ~Application_One() { }

        void requestValue() {
            m_proxyService->requestValue();
        }

        void setValue(const std::string _val) {
            m_proxyService->setStringValue(_val);
        }

    protected:
        ProxyService* m_proxyService {nullptr};
};

#endif // __APPLICATION_ONE__