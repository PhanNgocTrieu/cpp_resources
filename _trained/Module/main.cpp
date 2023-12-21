#include <sqlite3.h>
#include "Logger.h"

class Module {
    public:
        void trace() {
            WLOG_INF("Hello World!");
        }

    private:
        WLOG_DEF("Module");  
};

int main(int argc, char** argv) {
    Module module_;
    module_.trace();
    return 0;
}