#pragma once
#include <array>
#include <cstdint>
#include <string>

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
    std::array<std::array<uint8_t, 64>, 32> display;

    void reset();

    void loadRom(const std::string& path);

    uint16_t fetch();

    void timerUpdate();

    void decodeEx(uint16_t opcode);

private: 
    void increment();

    // 0nnn - SYS addr (ignored / legacy)
    // 00E0 - CLS
    // 00EE - RET

    // 1nnn - JP addr
    // 2nnn - CALL addr
    // 3xnn - SE Vx, byte
    // 4xnn - SNE Vx, byte
    // 5xy0 - SE Vx, Vy
    // 6xnn - LD Vx, byte
    // 7xnn - ADD Vx, byte

    // 8xy0 - LD Vx, Vy
    // 8xy1 - OR Vx, Vy
    // 8xy2 - AND Vx, Vy
    // 8xy3 - XOR Vx, Vy
    // 8xy4 - ADD Vx, Vy
    // 8xy5 - SUB Vx, Vy
    // 8xy6 - SHR Vx
    // 8xy7 - SUBN Vx, Vy
    // 8xyE - SHL Vx

    // 9xy0 - SNE Vx, Vy
    // Annn - LD I, addr
    // Bnnn - JP V0, addr
    // Cxnn - RND Vx, byte
    // Dxyn - DRW Vx, Vy, nibble

    // Ex9E - SKP Vx
    // ExA1 - SKNP Vx

    // Fx07 - LD Vx, DT
    // Fx0A - LD Vx, K
    // Fx15 - LD DT, Vx
    // Fx18 - LD ST, Vx
    // Fx1E - ADD I, Vx
    // Fx29 - LD F, Vx
    // Fx33 - LD B, Vx
    // Fx55 - LD [I], Vx
    // Fx65 - LD Vx, [I]

};

