cmake_minimum_required(VERSION 3.10)
project(asynchronous)

set(GCC_COMPILE_FLAGS "-lpthread")

add_definitions(${GCC_COMPILE_FLAGS})
add_library(event_loop STATIC event_loop.h event_loop.c)

add_executable(demo_app demo_app.c)
add_executable(demo_app_mul_sum demo_app_mul_sum.c)

target_link_libraries(demo_app event_loop)
target_link_libraries(demo_app_mul_sum event_loop)
