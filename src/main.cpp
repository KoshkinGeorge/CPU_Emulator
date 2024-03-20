#include <iostream>
#include <string>
#include "Emulator.hpp"


int main(int argc, const char **argv)
{
    Emulator em((argc > 2)? std::stoul(argv[2]) : 1024); 
    
    em.preprocess(argv[1]);
    return 0;
}