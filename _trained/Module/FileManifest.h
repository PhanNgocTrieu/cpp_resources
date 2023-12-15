#ifndef __FILE_MANIFEST_H__
#define __FILE_MANIFEST_H__

#include <iostream>

namespace Modules {
    class FileManifest {
        public:
            enum class RetCode {
                SUCCESS = 0,
                FAILED
            };

        public:
            FileManifest();
            ~FileManifest();

            RetCode _read_file(const char* filename) {
                return this->read_file(filename);
            }

            RetCode _write_file(const char* filename) {
                return this->write_file(filename);
            }

        protected:
            RetCode write_file(const char* filename);
            RetCode read_file(const char* filename);

        private:
            char* m_file_path;
            int m_mode;

    };
}
#endif