#include "CHIP8_cpu.h"
#include <SDL2/SDL.h>

class Input {
public:
    void processInputs(bool& CPUrunning, CHIP8_cpu& cpu);

private:
    int mapKey(SDL_Keycode key);
};