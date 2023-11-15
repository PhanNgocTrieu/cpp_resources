cmake_minimum_required(VERSION 3.16)
project(ProxySocket)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(Common)
add_subdirectory(Models)
add_subdirectory(Service)
add_subdirectory(Sockets)
add_subdirectory(Setting)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Common
    Models
    Service
    Sockets
)
