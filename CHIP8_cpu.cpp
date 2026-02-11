#include "CHIP8_cpu.h"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdint>
#include <cstdlib>

static constexpr std::array<uint8_t, 80> FONTSET = {
    0xF0,0x90,0x90,0x90,0xF0, // 0
    0x20,0x60,0x20,0x20,0x70, // 1
    0xF0,0x10,0xF0,0x80,0xF0, // 2
    0xF0,0x10,0xF0,0x10,0xF0, // 3
    0x90,0x90,0xF0,0x10,0x10, // 4
    0xF0,0x80,0xF0,0x10,0xF0, // 5
    0xF0,0x80,0xF0,0x90,0xF0, // 6
    0xF0,0x10,0x20,0x40,0x40, // 7
    0xF0,0x90,0xF0,0x90,0xF0, // 8
    0xF0,0x90,0xF0,0x10,0xF0, // 9
    0xF0,0x90,0xF0,0x90,0x90, // A
    0xE0,0x90,0xE0,0x90,0xE0, // B
    0xF0,0x80,0x80,0x80,0xF0, // C
    0xE0,0x90,0x90,0x90,0xE0, // D
    0xF0,0x80,0xF0,0x80,0xF0, // E
    0xF0,0x80,0xF0,0x80,0x80 // F
};

static constexpr uint16_t FONT_START = 0x50;

CHIP8_cpu::CHIP8_cpu()
    :I(0),
    PC(0x200),
    SP(0),
    DT(0),
    ST(0),
    draw_Dirty(false),
    running(true)
    {
        memory.fill(0);
        V.fill(0);
        stack.fill(0);
        keys.fill(false);

        for(size_t i = 0; i < display.size(); i++){
            for(size_t j = 0; j < display[i].size(); j++){
                display[i][j] = false; 
            }
        }

        // Loads Font sprites starting at mem addi 0x50
        for(size_t i = 0; i < FONTSET.size(); i++){
            memory[FONT_START + i] = FONTSET[i];
        }
    }

void CHIP8_cpu::reset() {
    I = 0;
    PC = 0x200;
    SP = 0;
    DT = 0;
    ST = 0;
    draw_Dirty = false;

    V.fill(0);
    stack.fill(0);
    keys.fill(false);

    for(size_t i = 0; i < display.size(); i++){
        for(size_t j = 0; j < display[i].size(); j++){
            display[i][j] = false; 
        }
    }
    
}

void CHIP8_cpu::loadRom(const std::string& path) {
    std::ifstream file(path, std::ios::binary);

    std::vector<uint8_t> buffer;

    if(!file){
        std::cerr << "File failed to open" << std::endl;
        running = false;
    }

    uint8_t current;

    while(file >> current){
        buffer.push_back(current);
    }

    // the rom is in buffer

    if(buffer.empty()){
        throw std::runtime_error("ROM load failed or file empty");
    }

    constexpr uint16_t start = 0x200;

    if(buffer.size() > memory.size() - start){
        throw std::runtime_error("ROM too big");
    }

    for(size_t i = 0; i < buffer.size(); i++){
        memory[0x200 + i] = buffer[i];
    }

    PC = 0x200;
}

uint16_t CHIP8_cpu::fetch(){
    uint8_t firstByte = memory[PC];
    uint8_t secondByte = memory[PC + 1];
    return (firstByte << 8) | secondByte;
}

void CHIP8_cpu::increment(){
    PC = PC + 2;
}

void CHIP8_cpu::timerUpdate(){
    if(DT > 0){
        DT -= 1;
    }
    if(ST > 0){
        ST -= 1;
    }
}

// 0nnn - SYS addr (ignored / legacy)

// 00E0 - CLS
void CHIP8_cpu::execute_CLS(){
    for(size_t i = 0; i < display.size(); i++){
        for(size_t j = 0; j < display[i].size(); j++){
            display[i][j] = false; 
        }
    }

    draw_Dirty = true;
    increment();
}

// 00EE - RET
void CHIP8_cpu::execute_RET(){
    SP -= 1;
    PC = stack[SP];
}

// 1nnn - JP addr
void CHIP8_cpu::execute_JP(uint16_t nnn){
    PC = nnn;
}

// 2nnn - CALL addr
void CHIP8_cpu::execute_CALL(uint16_t nnn){
    stack[SP] = (PC + 2);
    SP += 1;
    PC = nnn;
}

// 3xnn - SE Vx, byte
void CHIP8_cpu::execute_SE_vx_kk(uint8_t vx, uint8_t kk){
    if(V[vx] == kk){
        PC += 4;
    } else {
        increment();
    }
}

// 4xnn - SNE Vx, byte
void CHIP8_cpu::execute_SNE_vx_kk(uint8_t vx, uint8_t kk){
    if(V[vx] != kk){
        PC += 4;
    } else {
        increment();
    }
}

// 5xy0 - SE Vx, Vy
void CHIP8_cpu::execute_SE_vx_vy(uint8_t vx, uint8_t vy){
    if(V[vx] == V[vy]){
        PC += 4;
    } else {
        increment();
    }
}

// 6xnn - LD Vx, byte
void CHIP8_cpu::execute_LD_vx_kk(uint8_t vx, uint8_t kk) {
    V[vx] = kk;
    increment();
}

// 7xnn - ADD Vx, byte
void CHIP8_cpu::execute_ADD_vx_kk(uint8_t vx, uint8_t kk){
    V[vx] = (V[vx] + kk) & 0xFF;
    increment();
}

// 8xy0 - LD Vx, Vy
void CHIP8_cpu::execute_LD_vx_vy(uint8_t vx, uint8_t vy) {
    V[vx] = V[vy];
    increment();
}

// 8xy1 - OR Vx, Vy
void CHIP8_cpu::execute_OR_vx_vy(uint8_t vx, uint8_t vy){
    V[vx] = V[vx] | V[vy];
    increment(); 
}

// 8xy2 - AND Vx, Vy
void CHIP8_cpu::execute_AND_vx_vy(uint8_t vx, uint8_t vy){
    V[vx] = V[vx] & V[vy];
    increment();
}

// 8xy3 - XOR Vx, Vy
void CHIP8_cpu::execute_XOR_vx_vy(uint8_t vx, uint8_t vy){
    V[vx] = V[vx] ^ V[vy];
    increment();
}

// 8xy4 - ADD Vx, Vy
void CHIP8_cpu::execute_ADD_vx_vy(uint8_t vx, uint8_t vy){
    V[0xF] = (V[vx] + V[vy] > 255) ? 1 : 0;
    V[vx] = (V[vx] + V[vy]) & 0xFF;
    increment();
}

// 8xy5 - SUB Vx, Vy
void CHIP8_cpu::execute_SUB_vx_vy(uint8_t vx, uint8_t vy){
    V[0xF] = (V[vx] >= V[vy]) ? 1 : 0;
    V[vx] = (V[vx] - V[vy]) & 0xFF;
    increment();  
}

// 8xy6 - SHR Vx
void CHIP8_cpu::execute_SHR_vx(uint8_t vx){
    V[0xF] = (V[vx] & 0x01);
    V[vx] >>= 1;
    increment();
}

// 8xy7 - SUBN Vx, Vy
void CHIP8_cpu::execute_SUBN_vx_vy(uint8_t vx, uint8_t vy){
    uint8_t x = V[vx];
    uint8_t y = V[vy];

    V[0xF] = (y >= x) ? 1 : 0;
    V[x] = (V[y] - V[x]) & 0xFF;

    increment();
}

// 8xyE - SHL Vx
void CHIP8_cpu::execute_SHL_vx(uint8_t vx){
    V[0xF] = (V[vx] & 0x80) >> 7;
    V[vx] = (V[vx] << 1) & 0xFF;
    increment();
}

// 9xy0 - SNE Vx, Vy
void CHIP8_cpu::execute_SNE_vx_vy(uint8_t vx, uint8_t vy){
    if(V[vx] != V[vy]){
        PC += 4;
    } else {
        increment();
    }
}

// Annn - LD I, addr
void CHIP8_cpu::execute_LD_i_nnn(uint16_t nnn){
    I = nnn;
    increment();
}

// Bnnn - JP V0, addr
void CHIP8_cpu::execute_JP_v_nnn(uint16_t nnn){
    PC = nnn + V[0];
}

// Cxkk - RND Vx, byte
void CHIP8_cpu::execute_RND_vx_kk(uint8_t vx, uint8_t kk){
    V[vx] = (rand() % 256) & kk;
    increment();
}

// Dxyn - DRW Vx, Vy, nibble
void CHIP8_cpu::execute_DRW_vx_vy_n(uint8_t vx, uint8_t vy, uint8_t n){
    
}

// Ex9E - SKP Vx
void CHIP8_cpu::execute_SKP_vx(uint8_t vx){
    uint8_t regX = V[vx] & 0x0F;

    bool key = keys[regX];

    if(key){
        PC += 4;
    } else {
        increment();
    }
}

// ExA1 - SKNP Vx
void CHIP8_cpu::execute_SKNP_vx(uint8_t vx){
    uint8_t regX = V[vx] & 0x0F;

    bool key = keys[regX];

    if(!key){
        PC += 4;
    } else {
        increment();
    }
}

// Fx07 - LD Vx, DT
void CHIP8_cpu::execute_LD_vx_dt(uint8_t vx){
    V[vx] = DT;
    increment();
}

// Fx0A - LD Vx, K
void CHIP8_cpu::execute_LD_vx_k(uint8_t vx){
    for(int i = 0; i < 16; i++){
        if(keys[i]){
            V[vx] = i;
            increment();
            return;
        }
    }
}

// Fx15 - LD DT, Vx
void CHIP8_cpu::execute_LD_dt_vx(uint8_t vx){
    DT = V[vx];
    increment();
}

// Fx18 - LD ST, Vx
void CHIP8_cpu::execute_LD_st_vx(uint8_t vx){
    ST = V[vx];
    increment();
}

// Fx1E - ADD I, Vx
void CHIP8_cpu::execute_ADD_i_vx(uint8_t vx){
    I += V[vx];
    increment();
}

// Fx29 - LD F, Vx
void CHIP8_cpu::execute_LD_f_vx(uint8_t vx){
    I = FONT_START + (V[vx] & 0x0F) * 5;
    increment();
}

// Fx33 - LD B, Vx
void CHIP8_cpu::execute_LD_b_vx(uint8_t vx){
    uint8_t value = V[vx];

    memory[I] = value / 100;
    memory[I + 1] = (value / 10) % 10;
    memory[I + 2] = value % 10;

    increment();
}

// Fx55 - LD [I], Vx
void CHIP8_cpu::execute_LD_i_vx(uint8_t vx){
    uint8_t index = 0;

    while(index <= vx) {
        memory[I + index] = V[index];
        index += 1;
    }

    increment();
}

// Fx65 - LD Vx, [I]
void CHIP8_cpu::execute_LD_vx_i(uint8_t vx){
    uint8_t index = 0;

    while(index <= vx) {
        V[index] = memory[I + index];
        index += 1;
    }

    increment();
}

void CHIP8_cpu::decodeEx(uint16_t opcode){
    uint8_t firstByte = (opcode >> 8) & 0xF; 

    switch (firstByte)
    {
    case 0x0E:
        std::cout << "yo this is a opcode" << std::endl;
        increment();
        break;
    
    default:
        std::cout << "error at PC: " << std::hex << PC << std::endl;
        increment();
        break;
    }

}




