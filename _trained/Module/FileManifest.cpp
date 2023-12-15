#include "FileManifest.h"

namespace Modules {
    FileManifest::FileManifest() {}
    FileManifest::~FileManifest() {}

    FileManifest::RetCode FileManifest::write_file(const char* filename) {
        if (filename == nullptr) return;

        try
        {
            FILE* file = fopen(filename, "w+");

            if (file != nullptr) {
                
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        
    }

    FileManifest::RetCode FileManifest::read_file(const char* filename) {
        try
        {
            FILE* file = fopen(filename, "r");
            if (file != nullptr) {
                
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
};