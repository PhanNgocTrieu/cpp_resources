cmake_minimum_required(VERSION 3.10)

project(Modules)

set(SOURCE  ContentProvider.h
            ContentProvider.cpp
)

set(SQL_LIB_SRC SQLManagement.h
                SQLManagement.cpp
)

set(LOGGER_SRC main.cpp Logger.h
                Logger.cpp
)

# add_executable(ContentProvider main.cpp ${SOURCE})
# add_library(libSql PUBLIC ${SQL_LIB_SRC})
add_executable(logger ${LOGGER_SRC})

find_package(SQLite3)

include_directories(${SQLITE3_INCLUDE_DIRS})
# target_link_libraries (ContentProvider ${SQLITE3_LIBRARIES})
if (SQLITE3_FOUND)
endif (SQLITE3_FOUND)
