include_directories(inc)
set(SRC_FILE src/SocketService.cpp
)
add_library(Sockets STATIC ${SRC_FILE})
target_include_directories(Sockets PUBLIC ./inc)
target_compile_options(Sockets PRIVATE -std=c++11)
target_link_libraries(Sockets Models)
# target_link_options(socketlib PRIVATE )
# target_compile_definitions()
# target_link_libraries(socketlib -lmodel)