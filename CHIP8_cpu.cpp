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

