#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include "Stack.hpp"
#include "commands.hpp"
#include "Preprocessor.hpp"


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

//  private fields
private:
    Preprocessor preprocessor;
    Stack<unsigned> stack;
    std::string next_lexeme;

    std::ifstream programm; //  in.txt file
    std::ofstream outstream;
    std::ofstream errstream;

    // commands 
    std::map<std::string, Command> commands;
    std::map<std::string, unsigned> registers;

    bool running = false;
//  private methods
private:

//  public fields
public:
    

//  public methods
public:
    Emulator(size_t bytes_for_stack=1024);

    void exec(std::string file);

    void preprocess(std::string file);
//  friends

};