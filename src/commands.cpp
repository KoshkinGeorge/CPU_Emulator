#include <iostream>
#include "Stack.hpp"
#include "Emulator.hpp"

//  commands_0 - without args
void Emulator::begin()
{
    running = true;
    print("BEGIN command complited!\n");
}

void Emulator::end()
{
    running = false;
    print("END command complited!\n");
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
    print("END command complited!\n");
}
  
void Emulator::add()
{
    stack_ptr num1 = stack.get_top();
    stack_ptr num2 = num1->next;
    stack.push(num1->value + num2->value);
    print("ADD command complited!\n");
}
  
void Emulator::sub()
{
    stack_ptr num1 = stack.get_top();
    stack_ptr num2 = num1->next;
    stack.push(num1->value - num2->value);
    print("SUB command complited!\n");
}
  
void Emulator::mul()
{
    stack_ptr num1 = stack.get_top();
    stack_ptr num2 = num1->next;
    stack.push(num1->value * num2->value);
    print("MUL command complited!\n");
}
  
void Emulator::div()
{
    stack_ptr num1 = stack.get_top();
    stack_ptr num2 = num1->next;
    if (num2->value == 0)
    {
        errstream << "Division by zero with args " << num1->value << " " << num2->value << std::endl;
        throw 101;
    }
    stack.push(num1->value / num2->value);
    print("DIV command complited!\n");
}
  
void Emulator::out()
{   
    try
    {
        unsigned num = stack.get_top()->value;
        stack.pop();
        std::cout << "You got the number from the top: " << num << std::endl;
    }
    catch (std::out_of_range e) 
    {
        errstream << e.what() << std::endl;
        throw 201;
    }
    print("OUT command complited!\n");
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
    print("IN command complited!\n");
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
    print(std::string("PUSH ") + arg + " command complited!\n");
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
    print(std::string("PUSHR") + arg + " command complited!\n");
}

void Emulator::popr(std::string arg)
{
    try
    {
        unsigned value = stack.get_top()->value;
        stack.pop();
        registers[arg] = value;
    }
    catch (std::out_of_range e)
    {
        errstream << e.what() << std::endl;
        throw 201;
    }
    print(std::string("POPR") + arg + " command complited!\n");
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