
#pragma once

#include <map>
#include "Stack.hpp"


struct State
{
public:
    Stack<unsigned> stack;
    Stack<size_t> call_stack; // stack that remembers where to go after function call
    std::map<int, unsigned> registers; // know index - get register
    bool running;
    size_t cur_command;
    std::map<size_t, size_t> labels;
};