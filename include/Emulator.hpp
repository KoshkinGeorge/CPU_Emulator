#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <memory>
#include <vector>

#include "Stack.hpp"
#include "commands.hpp"
#include "Preprocessor.hpp"
#include "my_funcs.hpp"
#include "State.hpp"



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
            return to_c_str(std::string("File ") + file_name + " is not found");
        }
    };

//  private fields
private:
    State state;
    Preprocessor preprocessor;

    std::ifstream programm; //  in.txt file
    std::ofstream outstream;
    std::ofstream errstream;

    // commands 
    std::vector<std::shared_ptr<Command>> command_vec;
//  private methods
private:

private:
    void clear();
//  public fields
public:
    

//  public methods
public:
    Emulator(size_t bytes_for_stack = 1024, size_t recursion_deepth = 200);

    void exec(std::string file);

    int preprocess(std::string file);

    void run(std::string file);
//  friends

};