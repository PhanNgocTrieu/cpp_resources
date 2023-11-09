# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -Wall -Wextra -std=c++11

# Source files
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)

# Executable name
EXEC := setting
# COMMON_SRC="../Common/Variables.hpp"
# MODEL_SRC="../Models/Logger.hpp"
# SERVICE_SRC="Service/*.hpp"
# SOCKET_SRC="../Sockets/SocketService.hpp"

# all: ../Common/Variables.hpp ../Sockets/SocketService.hpp #$(COMMON_SRC) ${MODEL_SRC} ${SOCKET_SRC}
# 	g++ -o setting main.cpp

build: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)


valgrind: $(OBJS)
	valgrind $(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)