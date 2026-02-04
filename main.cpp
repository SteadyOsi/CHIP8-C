#include "CHIP8_cpu.h"
#include <iostream>
#include <cstdint>

int main(){
    CHIP8_cpu cpu; 

    const std::string path = "hello";

    cpu.loadRom(path);

    std::cout << "this worked" << std::endl;

    return 0;
}