#include <iostream>
#include <string>
#include "CPU_Em.hpp"

int main()
{
    CPU_Em em("./out.txt", "./err.txt"); 
    em.print("barabashka");
    return 0;
}