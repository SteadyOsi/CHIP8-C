#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <iomanip>
#include <cstdint>

int taskOne() {
    std::ifstream file("input.txt");

    if(!file){
        std::cerr << "File failed to open";
    }

    char value[20];  
    file >> value;

    std::cout << value << std::endl;

    return 0;
}

int taskTwo() { // read enteire line. 
    std::ifstream file("input.txt");

    if(!file){
        std::cerr << "File failed to open";
    }

    std::string value;
    while(std::getline(file, value)) {
        std::cout << value << std::endl;
    }

    return 0;
}

int taskThree() { // Read Numbers and Compute Sum

    std::ifstream file("input.txt");

    int sum = 0;

    if(!file){
        std::cerr << "File failed to open";
    }

    int value;

    while(file >> value){
        // std::cout << value << std::endl;
        sum = sum + value;
    }

    std::cout << sum << std::endl;


    return 0;
}

int taskFour() { // Read numbers from numbers.txt, compute sum, write result to result.txt.
    std::ifstream file("numbers.txt");
    std::ofstream outp("result.txt");

    int sum = 0;

    if(!file and !outp){
        std::cerr << "File failed to open";
    }

    int value;

    while(file >> value){
        // std::cout << value << std::endl;
        sum = sum + value;
    }

    outp << sum;

    return 0;
}

int taskFive() { // Determine File Size (Binary Thinking)
    std::ifstream file("numbers.txt");

    if(!file){
        std::cerr << "File failed to open";
    }


    file.seekg(0, std::ios::end);

    float bytes = static_cast<float>(file.tellg());

    float kb = bytes/1024; 
    float mb = bytes/(1024 * 1024);

    // there is a package you can include to not have chage the cout traling size 
    std::cout << "file in Bytes : " << file.tellg() << std::endl;
    std::cout << "file in KB    : " << kb << std::endl;
    std::cout << "file in MB    : " << mb << std::endl;

    return 0;

}

int taskSix() { // Read Binary File into Memory
    // Open with ios::binary
    std::ifstream file("/home/jk/Documents/GitHub/chip8-roms/programs/IBM Logo.ch8", std::ios::binary);

    if(!file){
        std::cerr << "File failed to open" << std::endl;
        return 1;
    }
    
    // Determine file size
    file.seekg(0, std::ios::end);
    std::cout << "file in Bytes : " << file.tellg() << std::endl;

    // Allocate std::vector<uint8_t>

    std::vector<uint8_t> buffer; 

    // Read entire file into it
    file.seekg(0);

    uint8_t current;

    while(file >> current){
        buffer.push_back(current);    
    }

    std::cout << "Bytes loaded:"<< std::endl;

    // Stretch: print first 16 bytes as hex
    for(uint8_t i = 0; i < 16 && i < buffer.size(); i++){
        std::cout 
        << "0x"
        << std::hex 
        << int(buffer[i]) 
        << std::endl;
    }
    
    return 0;
}

int taskSeven(){ // Task 7 — Interpret Binary Bytes
    std::ifstream file("/home/jk/Documents/GitHub/chip8-roms/programs/IBM Logo.ch8", std::ios::binary);

    if(!file){
        std::cerr << "File failed to open" << std::endl;
        return 1;
    }

    std::vector<uint8_t> buffer; 

    uint8_t current;

    while(file >> current){
        buffer.push_back(current);    
    }

        // Stretch: print first 16 bytes as hex
    for(uint8_t i = 0;i < buffer.size()-1; i++){
        uint16_t opcode = (buffer[i] << 8) | buffer[i+1]; 
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

int taskEight() {
    std::ifstream file("/home/jk/Documents/GitHub/chip8-roms/programs/IBM Logo.ch8", std::ios::binary);

    if(!file){
        std::cerr << "File failed to open" << std::endl;
        return 1;
    }

    
    return 0;
}

int main() {
    
    taskSeven();

    return 0;
}

// home computer: g++ 11.4.0
// laptop: 15.2.0