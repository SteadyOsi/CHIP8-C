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

    return 0;

}

int main() {
    
    taskFour();

    return 0;
}

// home computer: g++ 11.4.0
// laptop: 15.2.0