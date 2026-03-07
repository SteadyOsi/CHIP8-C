#include <array>
#include <SDL2/SDL.h>
#include <iostream>
#include <cstdint>

class Graphics {
public:
    Graphics();

    void init_Graphics(int scale);
    void Render_Graphics(const std::array<std::array<bool, 64>, 32>& cpuBuffer);
    void end_Game();

private:
    int scale;
    int window_Height = 32;
    int window_Width = 64;

    SDL_Window* window;
    SDL_Renderer* renderer;
};