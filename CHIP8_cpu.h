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
    void execute_CLS();

    // 00EE - RET
    void execute_RET();

    // 1nnn - JP addr
    void execute_JP(uint16_t nnn);

    // 2nnn - CALL addr
    void execute_CALL(uint16_t nnn);

    // 3xnn - SE Vx, byte
    void execute_SE_vx_kk(uint8_t vx, uint8_t kk);

    // 4xnn - SNE Vx, byte
    void execute_SNE_vx_kk(uint8_t vx, uint8_t kk);

    // 5xy0 - SE Vx, Vy
    void execute_SE_vx_vy(uint8_t vx, uint8_t vy);

    // 6xnn - LD Vx, byte
    void execute_LD_vx_kk(uint8_t vx, uint8_t kk)

    // 7xnn - ADD Vx, byte
    void execute_ADD_vx_kk(uint8_t vx, uint8_t kk);

    // 8xy0 - LD Vx, Vy
    void execute_LD_vx_vy(uint8_t vx, uint8_t vy);

    // 8xy1 - OR Vx, Vy
    void execute_OR_vx_vy(uint8_t vx, uint8_t vy);

    // 8xy2 - AND Vx, Vy
    void execute_AND_vx_vy(uint8_t vx, uint8_t vy);

    // 8xy3 - XOR Vx, Vy
    void execute_XOR_vx_vy(uint8_t vx, uint8_t vy);

    // 8xy4 - ADD Vx, Vy
    void execute_ADD_vx_vy(uint8_t vx, uint8_t vy);

    // 8xy5 - SUB Vx, Vy
    void execute_SUB_vx_vy(uint8_t vx, uint8_t vy);

    // 8xy6 - SHR Vx
    void execute_SHR_vx(uint8_t vx);

    // 8xy7 - SUBN Vx, Vy
    void execute_SUBN_vx_vy(uint8_t vx, uint8_t vy);

    // 8xyE - SHL Vx
    void execute_SHL_vx(uint8_t vx);

    // 9xy0 - SNE Vx, Vy
    void execute_SNE_vx_vy(uint8_t vx, uint8_t vy);

    // Annn - LD I, addr
    void execute_LD_i_nnn(uint16_t nnn);

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

