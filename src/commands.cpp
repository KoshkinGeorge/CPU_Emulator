#include <iostream>
#include "Stack.hpp"
#include "commands.hpp"
#include <map>
#include <sstream>
#include "my_funcs.hpp"


void Pass::exec(State &state, int arg) const
{
    
}

void Begin::exec(State &state, int arg) const
{
    state.running = true;
}


void End::exec(State &state, int arg) const
{
    state.running = false;
}


void Pop::exec(State &state, int arg) const
{
    //  all errors are being catched at the top level
    state.stack.pop(); 
}



void Add::exec(State &state, int arg) const
{
    state.running = true;
    unsigned num1 = state.stack.get_top();
    state.stack.pop();
    unsigned num2 = state.stack.get_top();
    state.stack.push(num1);
    state.stack.push(num1 + num2);
}



void Sub::exec(State &state, int arg) const
{
    unsigned num1 = state.stack.get_top();
    state.stack.pop();
    unsigned num2 = state.stack.get_top();
    state.stack.push(num1);
    state.stack.push(num1 - num2);
}




void Mul::exec(State &state, int arg) const
{
    unsigned num1 = state.stack.get_top();
    state.stack.pop();
    unsigned num2 = state.stack.get_top();
    state.stack.push(num1);
    state.stack.push(num1 * num2);
}



void Div::exec(State &state, int arg) const
{
    unsigned num1 = state.stack.get_top();
    state.stack.pop();
    unsigned num2 = state.stack.get_top();
    state.stack.push(num1);
    state.stack.push(num1 + num2);
    if (num2 == 0)
    {
        std::ostringstream oss;
        oss << num1;
        throw DivisionByZero(to_c_str(oss.str()));
    }
    state.stack.push(num1 / num2);
}



void Out::exec(State &state, int arg) const
{
    unsigned num = state.stack.get_top();
    state.stack.pop();
    std::cout << "You got the number from the top: " << num << std::endl;
}



void In::exec(State &state, int arg) const
{
    unsigned num;
    if (!(std::cin >> num))
    {
        throw ExpectedAnArgument("Num for IN command");
    }
    state.stack.push(num);
}



void Push::exec(State &state, int arg) const
{
    state.stack.push(arg);
}



void PushR::exec(State &state, int arg) const
{
    // if user tries to get a value from random register - he would be given a value left there from previous programms
    unsigned value = state.registers[arg]; 
    state.stack.push(value);
}



void PopR::exec(State &state, int arg) const
{
    unsigned value = state.stack.get_top();
    state.stack.pop();
    state.registers[arg] = value;
}


void Jmp::exec(State &state, int arg) const 
{
    state.cur_command = state.labels[arg];
}

void Jeq::exec(State &state, int arg) const 
{
    unsigned num1 = state.stack.get_top();
    state.stack.pop();
    unsigned num2 = state.stack.get_top();
    state.stack.push(num1);
    if (num1 == num2)
    {
        state.cur_command = state.labels[arg];
    }
}

void Jne::exec(State &state, int arg) const 
{
    unsigned num1 = state.stack.get_top();
    state.stack.pop();
    unsigned num2 = state.stack.get_top();
    state.stack.push(num1);
    if (num1 != num2)
    {
        state.cur_command = state.labels[arg];
    }
}

void Ja::exec(State &state, int arg) const 
{
    unsigned num1 = state.stack.get_top();
    state.stack.pop();
    unsigned num2 = state.stack.get_top();
    state.stack.push(num1);
    if (num1 > num2)
    {
        state.cur_command = state.labels[arg];
    }
}

void Jae::exec(State &state, int arg) const 
{
    unsigned num1 = state.stack.get_top();
    state.stack.pop();
    unsigned num2 = state.stack.get_top();
    state.stack.push(num1);
    if (num1 >= num2)
    {
        state.cur_command = state.labels[arg];
    }
}

void Jb::exec(State &state, int arg) const 
{
    unsigned num1 = state.stack.get_top();
    state.stack.pop();
    unsigned num2 = state.stack.get_top();
    state.stack.push(num1);
    if (num1 < num2)
    {
        state.cur_command = state.labels[arg];
    }
}

void Jbe::exec(State &state, int arg) const 
{
    unsigned num1 = state.stack.get_top();
    state.stack.pop();
    unsigned num2 = state.stack.get_top();
    state.stack.push(num1);
    if (num1 <= num2)
    {
        state.cur_command = state.labels[arg];
    }
}


void Call::exec(State &state, int arg) const 
{
    state.call_stack.push(state.cur_command);
    state.cur_command = state.labels[arg];
}

void Ret::exec(State &state, int arg) const 
{
    state.cur_command = state.call_stack.get_top();
    state.call_stack.pop();
}

void Save::exec(State &state, int arg) const
{
    unsigned value = state.stack.get_top();
    state.registers[arg] = value;
}