#include <array>
#include <SDL2/SDL.h>
#include <iostream>
#include <cstdint>

class Graphics {
public:
    std::array<std::array<bool, 64>, 32> buffer;
    int scale;

private:
    int window_Height;
    int window_Width;

}