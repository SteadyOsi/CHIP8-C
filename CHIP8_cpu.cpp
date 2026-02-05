#include "CHIP8_cpu.h"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdint>

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




