#include "ContentProvider.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
namespace Modules {
    ContentProvider* ContentProvider::getInstance() {
        static ContentProvider instance;
        return &instance;
    }

    ContentProvider::ContentProvider() {
        this->initialize();
        m_isReady = true;
    }

    ContentProvider::~ContentProvider() {}

    void ContentProvider::initialize() {
        // Run config
        FILE* configFile = fopen("config.ini", "r");
        char line[500];
        while (fgets(line, sizeof(line),configFile))
        {
            /* code */
            char* tmp = strstr(line, "=");
            if (tmp == nullptr) {
                continue;
            }

            char* name = &line[0];
            char* temp = &line[0];
            

        }
        
    }
    
} // namespace Module
