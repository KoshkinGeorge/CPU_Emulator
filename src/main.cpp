#include <iostream>
#include <string>
#include "Emulator.hpp"

int main(int argc, const char **argv)
{
    Emulator em("out.txt", "err.txt", (argc > 2)? std::stoul(argv[2]) : 1024); 
    
    em.exec(argv[1]);
    return 0;
}