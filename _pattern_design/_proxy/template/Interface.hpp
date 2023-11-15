#ifndef __INTERFACE_H__
#define __INTERFACE_H__
#include <iostream>

class Interface {
    public:
        virtual std::string requestValue() = 0;
        virtual void setStringValue(const std::string& value) = 0;
};

#endif /* __INTERFACE_H__ */