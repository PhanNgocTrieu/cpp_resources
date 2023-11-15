
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(inc)
set(SRC_HDR src/ServiceProxy.cpp
    src/Service.cpp
)
add_library(Service STATIC ${SRC_HDR})

target_compile_options(Service PUBLIC -std=c++11)
target_link_libraries(Service PRIVATE Common Models)