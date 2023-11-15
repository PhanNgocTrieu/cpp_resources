#include "FirstApplication.hpp"
#include "SecondApplication.hpp"

int main() {
    Application_One m_firstApp;
    Application_Two m_secondApp;
    m_firstApp.setValue(25231);
    m_secondApp.printValue();
    return 0;
}