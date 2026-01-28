#include <iostream>
#include <fstream>
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
    std::ifstream file("");

    

    return 0;
}

int main() {
    
    taskFive();

    return 0;
}

// home computer: g++ 11.4.0
// laptop: 15.2.0