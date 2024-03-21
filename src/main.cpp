#include <iostream>
#include <string>
#include "Emulator.hpp"


int main(int argc, const char* argv[])
{
    Emulator em((argc > 2)? std::stoul(argv[2]) : 1024);
    
    std::string programm;
    std::cout << ">>> ";
    while (std::cin >> programm)
    {
        em.preprocess(programm);
        std::cout << '\n' << programm << " is preprocessed. View log.txt and out.txt for details...\n>>> ";
    } 
    
    return 0;
}