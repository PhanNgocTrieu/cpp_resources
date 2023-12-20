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
        this->readContentProvider();     
    }

    void ContentProvider::readContentProvider() {
        
    }
    
} // namespace Module
