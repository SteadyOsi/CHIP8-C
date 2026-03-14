#include "CHIP8_cpu.h"
#include "Graphics.h"
#include <iostream>
#include <cstdint>
#include <iomanip>

void debugMemory(){

}

int main(){
    CHIP8_cpu cpu;
    Graphics screen; 

    const std::string path = "/home/minion/Documents/GitHub/CHIP8-Roms/chip8-roms/games/Cave.ch8";
    cpu.loadRom(path);

    screen.init_Graphics(20);

    SDL_Event e;
    
    while(cpu.running){ // main loop for cpu

        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
                cpu.running = false;
        }

        uint16_t opcode = cpu.fetch();
        cpu.decodeEx(opcode);

        screen.Render_Graphics(cpu.display);

        SDL_Delay(16);

    //     std::cout << "Address: " << "0x" << std::hex << (cpu.PC) << " opcode: ";

    //     std::cout 
    //         << "0x"
    //         << std::hex
    //         << std::setw(4)
    //         << std::setfill('0')
    //         << opcode 
    //         << std::endl;
    // }
    
    }

    return 0;
}