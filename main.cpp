#include "CHIP8_cpu.h"
#include <iostream>
#include <cstdint>
#include <iomanip>

void debugMemory(){

}

int main(){
    CHIP8_cpu cpu; 

    const std::string path = "/home/minion/Documents/GitHub/CHIP8-Roms/chip8-roms/programs/IBM Logo.ch8";

    cpu.loadRom(path);

    while(cpu.running){
        uint16_t opcode = cpu.fetch();
        cpu.decodeEx(opcode);
    }

    for(int i = 0; i < 20; i+= 2){
        uint16_t opcode = (cpu.memory[0x200 + i] << 8) | cpu.memory[0x200 + i+1]; 

        std::cout << "Address: " << "0x" << std::hex << (0x200+i) << " opcode: ";

        std::cout 
            << "0x"
            << std::hex
            << std::setw(4)
            << std::setfill('0')
            << opcode 
            << std::endl;
    }

    return 0;
}