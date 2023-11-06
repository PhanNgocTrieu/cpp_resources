#ifndef __SECOND_APPLICATION__
#define __SECOND_APPLICATION__

#include "Interface.hpp"
#include <iostream>
class Application_Two {
    public:
        Application_Two() 
        : m_pattern(PatternInterface::create()) {
            std::cout << " [Application_Two] Pattern Address: " << &m_pattern << std::endl;
        }
        ~Application_Two() {}

        void setValue(const int _va) {
            m_pattern->setValue(_va);
        }

        void printValue() {
            std::cout << " [Application_Two] value: " << m_pattern->getValue() << std::endl;
        }
    protected:
        PatternInterface* m_pattern;
};

#endif