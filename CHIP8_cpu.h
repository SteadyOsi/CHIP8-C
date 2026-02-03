#include <array>
#include <cstdint>

class CHIP8_cpu {

public:
    CHIP8_cpu();

    std::array<uint8_t, 4096> memory;
    uint16_t PC; // program counter 

    std::array<uint16_t, 16> stack;
    uint8_t SP; // stack pointer 

    std::array<uint8_t, 16> V;
    uint16_t I; // index register
    uint8_t DT; // delay timer 
    uint8_t ST; // sound timer

    std::array<std::array<bool, 64>, 32> display;

    std::array<bool, 16> keys;

    bool draw_Dirty;
    bool running;
};