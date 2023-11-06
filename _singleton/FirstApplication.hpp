#ifndef __FIRST_APPLICATION__
#define __FIRST_APPLICATION__

#include "Interface.hpp"
#include <iostream>
class Application_One {
    public:
        Application_One() 
        : m_pattern(PatternInterface::create()) {
            std::cout << " [Application_One] Pattern Address: " << &m_pattern << std::endl;
        }
        ~Application_One() {}

        void setValue(const int _va) {
            m_pattern->setValue(_va);
        }

        void printValue() {
            std::cout << " [Application_One] value: " << m_pattern->getValue() << std::endl;
        }
    protected:
        PatternInterface* m_pattern;
};

#endif