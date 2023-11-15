include_directories(inc)

# Include all the source files
set(SRC_FILE src/Logger.cpp 
            src/Timer.cpp
)

# Create a library
add_library(Models STATIC ${SRC_FILE})

# Public the include folder
target_include_directories(Models PUBLIC ./inc)

target_compile_options(Models PUBLIC -Wall -std=c++11)
