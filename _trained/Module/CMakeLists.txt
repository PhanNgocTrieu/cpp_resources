cmake_minimum_required(VERSION 3.10)

project(Modules)

find_package(SQLite3)

include_directories(lib)
include_directories(${SQLITE3_INCLUDE_DIRS})

set(SOURCE  ContentProvider.h
            ContentProvider.cpp
)

set(SQL_LIB_SRC lib/SQLManagement.h
                lib/SQLManagement.cpp
)

set(LOGGER_LIB  lib/Logger.h
                lib/Logger.cpp
)

# Create libraries
add_library(libSql STATIC ${SQL_LIB_SRC})
target_link_libraries (libSql ${SQLite3_LIBRARIES})

add_library(libLogger STATIC ${LOGGER_LIB})

# Executable file
add_executable(application main.cpp)

link_directories(/usr/lib)

# Link the lib
target_link_libraries (application libSql libLogger )

if (SQLITE3_FOUND)
endif (SQLITE3_FOUND)
