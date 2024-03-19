#ifndef Emulator_HPP

#define Emulator_HPP

#include <iostream>
#include <fstream>
#include <map>
#include "Stack.hpp"


class Emulator
{
//  public type fields
public:
    class FileNotFound : public std::exception
    {
    private:
        std::string file_name{};
    public:
        FileNotFound(std::string filename)
            : file_name(filename) {}
        
        const char* what() const noexcept override 
        {
            return (std::string("File ") + file_name + " is not found").c_str();
        }
    };

    class InvalidSyntaxError : public std::exception
    {
    private:
        std::string lxm{};
    public:
        InvalidSyntaxError(std::string lexeme)
            : lxm(lexeme) {}
        
        const char* what() const noexcept override 
        {
            return (std::string("Invalid syntax used in programm\n") + lxm).c_str();
        }
    };
private:
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
    errstream << "Trying to open an unexisting file\n" << file_name << std::endl;
}
//  public fields
public:
    

//  public methods
public:
    Emulator(std::string out_file="out.txt",
    std::string err_file="err.txt", size_t bytes_for_stack=1024);

    void exec(std::string in_file);
//  friends

};

#endif