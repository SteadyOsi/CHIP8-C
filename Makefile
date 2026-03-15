CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic
SDLFLAGS = $(shell pkg-config --cflags --libs sdl2)

TARGET = chip8

SRCS = main.cpp CHIP8_cpu.cpp Graphics.cpp Input.cpp Audio.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(SDLFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(SDLFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)