#pragma once
#include <array>
#include <cstdint>

class CHIP8_cpu {

public:
    CHIP8_cpu();
    uint16_t I; // index register
    uint16_t PC; // program counter 
    uint8_t SP; // stack pointer 
    uint8_t DT; // delay timer 
    uint8_t ST; // sound timer
    bool draw_Dirty;
    bool running;

    std::array<uint8_t, 4096> memory;
    std::array<uint8_t, 16> V;
    std::array<uint16_t, 16> stack;
    std::array<bool, 16> keys;
    std::array<std::array<bool, 64>, 32> display;

    void reset();
};