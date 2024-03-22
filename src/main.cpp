#include <iostream>
#include <string>
#include "Emulator.hpp"
#include "commands.hpp"


int main(int argc, const char* argv[])
{
    Emulator em((argc > 2)? std::stoul(argv[2]) : 1024);
    
    std::string programm;
    std::cout << ">>> ";
    while (std::cin >> programm)
    {
        em.run(programm);
        std::cout << ">>> ";
    } 
    
    return 0;
}