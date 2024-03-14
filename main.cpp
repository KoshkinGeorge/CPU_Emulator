#include <iostream>
#include <string>
#include "CPU_Em.hpp"

int main(int argc, const char **argv)
{
    CPU_Em em("./out.txt", "./err.txt", (argc > 2)? std::stoul(argv[2]) : 1024); 
    
    em.exec(argv[1]);
    return 0;
}