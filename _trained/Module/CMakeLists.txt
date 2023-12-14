cmake_minimum_required(VERSION 3.10)

project(Modules)

set(SROUCE  ContentProvider.h
            ContentProvider.cpp
)

add_executable(ContentProvider main.cpp ${SOURCE})

find_package(SQLite3)

include_directories(${SQLITE3_INCLUDE_DIRS})
target_link_libraries (ContentProvider ${SQLITE3_LIBRARIES})
if (SQLITE3_FOUND)
endif (SQLITE3_FOUND)
