cmake_minimum_required(VERSION 3.10)
project(asynchronous)

find_package (Threads REQUIRED)

set(GCC_COMPILE_FLAGS "-lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_definitions(${GCC_COMPILE_FLAGS})
add_library(event_loop STATIC event_loop.h event_loop.c)

add_executable(demo_app demo_app.c)
add_executable(demo_app_mul_sum demo_app_mul_sum.c)
add_executable(demo_app_single_threaded_concurrent demo_app_single_threaded_concurrent.c)

target_link_libraries(event_loop ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(demo_app event_loop)
target_link_libraries(demo_app_mul_sum event_loop)
target_link_libraries(demo_app_single_threaded_concurrent event_loop)
