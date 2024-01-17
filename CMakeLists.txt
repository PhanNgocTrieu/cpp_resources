cmake_minimum_required(VERSION 3.0.0)
project(challanges VERSION 0.1.0)

set(THREADS_PREFER_PTHREAD_FLAG TRUE)

add_subdirectory(_graph_model)
add_subdirectory(_solving)
