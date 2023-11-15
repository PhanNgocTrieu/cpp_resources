#ifndef __SERVICE_H__
#define __SERVICE_H__

#include "Interface.hpp"

class ServiceWrapper :  public Interface {
    public:
        ServiceWrapper() = default;
        virtual std::string requestValue() override { return m_value; }
        virtual void setStringValue(const std::string& value) override { }

    private:
        std::string m_value {"Hello world!"};
};

#endif