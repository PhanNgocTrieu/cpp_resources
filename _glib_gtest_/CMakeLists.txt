# cmake_minimum_required(VERSION 3.10)
# project(GlibDemo)

# Enable testing
enable_testing()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# =====> GoogleTest <=======
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(glibDem main.cpp)
target_link_libraries(glibDem GTest::gtest_main ${GLIB_LIBRARIES})

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GLIB REQUIRED glib-2.0)
INCLUDE_DIRECTORIES(
    ${GLIB_INCLUDE_DIRS}
)

LINK_DIRECTORIES(${GLIB_LIBRARY_DIRS})
add_definitions(${GLIB_CFLAGS_OTHER})


include(GoogleTest)
gtest_discover_tests(glibDem)