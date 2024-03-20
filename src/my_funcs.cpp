#include <iostream>
#include "my_funcs.hpp"


char * to_c_str(std::string line)
{
    char *ans = new char[line.size() + 1];
    int i = 0;
    for (char sim : line)
    {
        ans[i++] = sim;
    }
    ans[i] = '\0';
    return ans;
}