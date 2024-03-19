#ifndef Emulator_HPP

#define Emulator_HPP

#include <iostream>
#include <fstream>
#include <map>
#include "Stack.hpp"

class Emulator
{
//  private type fields
private:
    using stack_ptr = Stack<unsigned>::node*;
//  private fields
private:
    Stack<unsigned> stack;

    std::ifstream programm; //  in.txt file
    std::ofstream outstream;
    std::ofstream errstream;

    // commands 
    std::map<std::string, void (Emulator::*)()> commands_0;
    std::map<std::string, void (Emulator::*)(std::string)> commands_1;
    std::map<std::string, unsigned> registers;

    bool running = false;
//  private methods
private:
    void begin();

    void end();

    void pop();

    void add();

    void sub();

    void mul();

    void div();

    void out();

    void in();


    // commands with one argument
    void push(std::string);

    void pushr(std::string);

    void popr(std::string);


    //  repeat command - the special one
    void repeat(unsigned count, void (Emulator::*f)());

    void repeat(unsigned count, void (Emulator::*f)(std::string arg), std::string argument);

inline void file_not_found_error(std::string file_name)
{
    errstream << "Trying to open an unexisting file\n" << file_name <<
    std::string(" in file ") << __FILE__ << "\nfunction: " << __func__ << "\nLine: " << std::to_string(__LINE__) << std::endl;
}

inline void raise_error(std::string message)
{
    errstream << message << std::endl;
}
//  public fields
public:
    

//  public methods
public:
    Emulator(std::string out_file="out.txt",
    std::string err_file="err.txt", size_t bytes_for_stack=1024);

    void print(std::string mes);



    void exec(std::string in_file);
//  friends

};

#endif