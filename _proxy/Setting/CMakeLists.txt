add_executable(settingApp main.cpp)
# target_link_libraries(settingApp common)
target_compile_options(settingApp PUBLIC -std=c++11)
target_link_libraries(settingApp Common Models Sockets)