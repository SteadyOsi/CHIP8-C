#include <array>
#include <SDL2/SDL.h>
#include <iostream>
#include <cstdint>

class Graphics {
public:
    Graphics();

    std::array<std::array<bool, 64>, 32> buffer;
    int scale = 20;
    int window_Height = 32 * scale;
    int window_Width = 64 * scale;

    void init_Graphics(int scale);
    void Render_Graphics(CHIP8_cpu cpu);
    void end_Game();

private:

};