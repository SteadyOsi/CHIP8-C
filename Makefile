# Kinda dont know how this works, gotta learn this bit.

CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic

TARGET = chip8

SRCS = main.cpp CHIP8_cpu.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
