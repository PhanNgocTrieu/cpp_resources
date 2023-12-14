#include "ContentProvider.h"

namespace Modules {
    ContentProvider* ContentProvider::getInstance() {
        static ContentProvider instance;
        return &instance;
    }

    ContentProvider::ContentProvider() {
        this->initialize();
    }

    ContentProvider::~ContentProvider() {}

    void ContentProvider::initialize() {
        // Run config
        
    }
    
} // namespace Module
