#include <iostream>
#include "Stack.hpp"
#include "Emulator.hpp"

//  commands_0 - without args
void Emulator::begin()
{
    running = true;
    outstream << "BEGIN command completed!\n";
}

void Emulator::end()
{
    running = false;
    outstream << "END command completed!\n";
}
  
void Emulator::pop()
{
    try
    {
        stack.pop();
    }
    catch(std::out_of_range e)
    {
        errstream << e.what() << std::endl;
        throw 201;
    }
    outstream << "END command completed!\n";
}
  
void Emulator::add()
{
    unsigned num1 = stack.get_top();
    stack.pop();
    unsigned num2 = stack.get_top();
    stack.push(num1);
    stack.push(num1 + num2);
    outstream << "ADD command completed!\n";
}
  
void Emulator::sub()
{
    unsigned num1 = stack.get_top();
    stack.pop();
    unsigned num2 = stack.get_top();
    stack.push(num1);
    stack.push(num1 - num2);
    outstream << "SUB command completed!\n";
}
  
void Emulator::mul()
{
    unsigned num1 = stack.get_top();
    stack.pop();
    unsigned num2 = stack.get_top();
    stack.push(num1);
    stack.push(num1 * num2);
    outstream << "MUL command completed!\n";
}
  
void Emulator::div()
{
    unsigned num1 = stack.get_top();
    stack.pop();
    unsigned num2 = stack.get_top();
    stack.push(num1);
    stack.push(num1 + num2);
    if (num2 == 0)
    {
        errstream << "Division by zero with args " << num1 << " " << num2 << std::endl;
        throw 101;
    }
    stack.push(num1 / num2);
    outstream << "DIV command completed!\n";
}
  
void Emulator::out()
{   
    try
    {
        unsigned num = stack.get_top();
        stack.pop();
        std::cout << "You got the number from the top: " << num << std::endl;
    }
    catch (std::out_of_range e) 
    {
        errstream << e.what() << std::endl;
        throw 201;
    }
    outstream << "OUT command completed!\n";
}

void Emulator::in()
{
    try
    {
        unsigned num;
        if (!(std::cin >> num))
        {
            throw 301;
        }
        stack.push(num);
    }
    catch (std::runtime_error e)
    {
        errstream << e.what() << std::endl;
        throw 302;
    }
    outstream << "IN command completed!\n";
}


//  commands_1 - with one arg
void Emulator::push(std::string arg)
{
    try
    {
        stack.push(std::move(std::stoul(arg)));
    }
    catch (std::invalid_argument e)
    {
        errstream << "Unexpected argument for push function: " << arg;
        errstream << "\t" << e.what() << std::endl;
        throw 303;
    }
    outstream << "PUSH " << arg << " command completed!\n";
}
  
void Emulator::pushr(std::string arg)
{
    try
    {
        // if user tries to get a value from random register - it would be an undefined behavior (he would be given a value left there by previous programms)
        unsigned value = registers[arg]; 
        stack.push(value);
    }
    catch (std::runtime_error e)
    {
        errstream << e.what() << std::endl;
        throw 302;
    }
    outstream << "PUSHR " << arg << " command completed!\n";
}

void Emulator::popr(std::string arg)
{
    try
    {
        unsigned value = stack.get_top();
        stack.pop();
        registers[arg] = value;
    }
    catch (std::out_of_range e)
    {
        errstream << e.what() << std::endl;
        throw 201;
    }
    outstream << std::string("POPR ") << arg << " command completed!\n";
}



void Emulator::repeat(unsigned count, void (Emulator::*f)())
{
    for (unsigned i = 0; i < count; i++)
    {
        (this->*f)();
    }
}

//  repeat function overloading for command_1 case
void Emulator::repeat(unsigned count, void (Emulator::*f)(std::string arg), std::string argument)
{
    for (unsigned i = 0; i < count; i++)
    {
        (this->*f)(argument);
    }
}