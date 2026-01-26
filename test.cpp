#include <iostream>
#include <fstream>
#include <cstdint>

int main() {
    
    std::ifstream file("/home/minion/Documents/GitHub/CHIP8-Roms/chip8-roms/programs/IBM Logo.ch8", std::ios::binary);

    if (file) {
    
        int data;

        uint8_t bytes[2];
        
        while (file.read(reinterpret_cast<char*>(bytes), 2)) {

            uint16_t opcode = (bytes[0] << 8) | bytes[1];

            std::cout << std::hex << opcode << std::endl;
        }
        
        file.close();
    
    } else {
        std::cerr << "Error opening file." << std::endl;
    }
    
    return 0;
}

// home computer: g++ 11.4.0
// laptop: 15.2.0