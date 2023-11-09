#include "ApplicationOne.hpp"
#include "ApplicationTwo.hpp"
#include "Proxy.hpp"
int main() {
    ServiceWrapper _service;
    
    Application_One app_one(&_service);
    Application_Two app_two(&_service);

    app_one.requestValue();
    app_one.setValue("Goodbye!");
    std::cout << std::endl;
    app_two.requestValue();

    return 0;
}