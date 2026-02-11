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
    void execute_LD_vx_kk(uint8_t vx, uint8_t kk);

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
    void execute_JP_v_nnn(uint16_t nnn);

    // Cxnn - RND Vx, byte
    void execute_RND_vx_kk(uint8_t vx, uint8_t kk);

    // Dxyn - DRW Vx, Vy, nibble
    void execute_DRW_vx_vy_n(uint8_t vx, uint8_t vy, uint8_t n);

    // Ex9E - SKP Vx
    void execute_SKP_vx(uint8_t vx);

    // ExA1 - SKNP Vx
    void execute_SKNP_vx(uint8_t vx);

    // Fx07 - LD Vx, DT
    void execute_LD_vx_dt(uint8_t vx);

    // Fx0A - LD Vx, K
    void execute_LD_vx_k(uint8_t vx);

    // Fx15 - LD DT, Vx
    void execute_LD_dt_vx(uint8_t vx);

    // Fx18 - LD ST, Vx
    void execute_LD_st_vx(uint8_t vx);

    // Fx1E - ADD I, Vx
    void execute_ADD_i_vx(uint8_t vx);

    // Fx29 - LD F, Vx
    void execute_LD_f_vx(uint8_t vx);

    // Fx33 - LD B, Vx
    void execute_LD_b_vx(uint8_t vx);

    // Fx55 - LD [I], Vx
    void execute_LD_i_vx(uint8_t vx);

    // Fx65 - LD Vx, [I]
    void execute_LD_vx_i(uint8_t vx);
};

