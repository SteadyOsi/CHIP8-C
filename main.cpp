#include "CHIP8_cpu.h"
#include "Graphics.h"
#include "Input.h"
#include <iostream>
#include <cstdint>
#include <iomanip>
#include <chrono> 
#include <cmath>

int main(){

    using clock = std::chrono::steady_clock;
    CHIP8_cpu cpu;
    Graphics screen; 
    Input controls;
    

    double cpuHz = 1.0/700.0;
    double screenHz = 1.0/60.0;

    const std::string path = "/home/jk/Documents/GitHub/chip8-roms/programs/Keypad Test [Hap, 2006].ch8";
    cpu.loadRom(path);

    screen.init_Graphics(20);

    SDL_Event e;

    double cpuTimer = 0.0;
    double renderTimer = 0.0;
    
    auto lastTimer = clock::now();


    while(cpu.running){ // main loop for cpu
        auto nowTimer = clock::now();
        double time_dif = std::chrono::duration<double>(nowTimer - lastTimer).count();
        lastTimer = nowTimer;

        cpuTimer += time_dif;
        renderTimer += time_dif;

        controls.processInputs(cpu.running, cpu); // handles inputs

        while(cpuTimer >= cpuHz){
            uint16_t opcode = cpu.fetch();
            cpu.decodeEx(opcode);

            cpuTimer -= cpuHz;
        }
        

        while(renderTimer >= screenHz){
            screen.Render_Graphics(cpu.display);

            renderTimer -= screenHz;
        }
    }

    screen.end_Game();

    return 0;
}