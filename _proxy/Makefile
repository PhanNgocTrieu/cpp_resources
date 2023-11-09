# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -Wall -Wextra -std=c++11

# Source files
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)

EXEC := main
build: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)
