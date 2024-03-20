#pragma once

#include <iostream>
#include <map>
#include "IO_dirs.hpp"
#include <fstream>

class Preprocessor
{
private:
    static std::map<std::string, unsigned> all_commands; // all the commands and amount of their arguments
    std::ofstream processed;
public:

    class NoArgumentGiven : public std::exception
    {
    private:
        std::string lxm{};
    public:
        NoArgumentGiven(std::string lexeme)
            : lxm(lexeme) {}
        
        const char* what() const noexcept override 
        {
            return (std::string("Expected an argument for ") + lxm).c_str();
        }
    };

    class UnknownCommand : public std::exception
    {
    private:
        std::string lxm{};
    public:
        UnknownCommand(std::string lexeme)
            : lxm(lexeme) {}
        
        const char* what() const noexcept override 
        {
            return (std::string("Unknown command: ") + lxm).c_str();
        }
    };

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

public:
    void process_file(std::string file_name);
};
