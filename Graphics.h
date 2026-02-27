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

    init_Graphics();
    Render_Graphics();
    end_Game();

private:

};