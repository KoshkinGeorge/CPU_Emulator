#pragma once

#include <iostream>
#include <map>
#include <vector>
#include "IO_dirs.hpp"
#include <fstream>
#include "my_funcs.hpp"

class Preprocessor
{
private:
    std::map<std::string, unsigned> all_commands; // all the commands and amount of their arguments
    std::map<std::string, uint32_t> codes;
    uint32_t index = 0;
    std::ofstream processed;

private:
    int compile_function(std::ifstream &programm, std::ofstream &compiled,
        const std::string &start, const std::string &end);

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
            return to_c_str(std::string("Expected an argument for ") + lxm);
        }
    };

    class UnknownLexeme : public std::exception
    {
    private:
        std::string lxm{};

    public:
        UnknownLexeme(std::string lexeme)
            : lxm(lexeme) {}
        
        const char* what() const noexcept override 
        {
            return to_c_str(lxm + " is not defined");
        }
    };


    class LexemeReserved : public std::exception
    {
    private:
        std::string lxm{};
    public:
        LexemeReserved(std::string lexeme)
            : lxm(lexeme) {}
        
        const char* what() const noexcept override 
        {
            return to_c_str(std::string("Lexeme \"") + lxm + "\" is already in use");
        }
    };

    class CoredFunction : public std::exception
    {
    private:
        std::string mes{};
    public:
        CoredFunction(std::string _mes)
            : mes(_mes) {}
        
        const char* what() const noexcept override 
        {
            return to_c_str(mes);
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
            return to_c_str(std::string("File ") + file_name + " is not found");
        }
    };

    Preprocessor();

public:
    void process_file(std::string file_name);
};
