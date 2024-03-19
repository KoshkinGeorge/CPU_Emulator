#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include "Emulator.hpp"
#include "IO_dirs.hpp"

using std::string;



Emulator::Emulator(string out_file, string err_file, size_t bytes_for_stack):
outstream(std::string("../") + OUTPUT_DIR + "/" + out_file),
errstream(std::string("../") + OUTPUT_DIR + "/" + err_file)
{
    stack = Stack<unsigned>(bytes_for_stack);

    commands_0["BEGIN"] = begin;
    commands_0["END"] = end;
    commands_0["POP"] = pop;
    commands_0["ADD"] = add;
    commands_0["SUB"] = sub;
    commands_0["MUL"] = mul;
    commands_0["DIV"] = div;
    commands_0["OUT"] = out;
    commands_0["IN"] = in;

    commands_1["PUSH"] = push;
    commands_1["PUSHR"] = pushr;
    commands_1["POPR"] = popr;

    registers["AX"] = 0;
    registers["BX"] = 0;
    registers["CX"] = 0;
    registers["DX"] = 0;
    registers["SP"] = 0;
    registers["BP"] = 0;
    registers["SI"] = 0;
    registers["DI"] = 0;
    registers["IP"] = 0;
    registers["PC"] = 0;

    if (!outstream || !errstream) // if failed to open one of the files
    {
        throw FileNotFound(!outstream? out_file : err_file);
    }
}

void Emulator::exec(std::string programm_name)
{   
    static unsigned counter = 1;
    std::string in_file = std::string("../") + std::string(INPUT_DIR) + "/" + programm_name + ".txt";
    // distinguishing marks
    errstream << "\n\n\n\n\t\t\t\t-------Programm " << counter << "---------\n\n" << std::endl;
    outstream << "\n\n\n\n\t\t\t\t-------Programm " << counter++ << "---------\n\n" << std::endl;
    programm = std::ifstream(in_file);
    if (!programm)
    {
        throw FileNotFound(std::string("File ") + in_file + " not found!");
    }
    string lexeme;

    while(programm >> lexeme)
    {
        if (running || lexeme == "BEGIN")
        {
            try
            {
                if (commands_0.count(lexeme) == 1) // if this command takes no arguments
                {
                    auto func = commands_0[lexeme];
                    (this->*func)();
                }
                else if (commands_1.count(lexeme) == 1)
                {
                    auto func = commands_1[lexeme];
                    std::string arg;
                    if (!(programm >> arg)) 
                    {
                        throw InvalidSyntaxError(std::string("Expected an argument for ") + lexeme + " function");
                    }
                    (this->*func)(arg);
                }
                else if (lexeme == "REPEAT")
                {
                    unsigned count;
                    if (!(programm >> count)) 
                    {
                        throw InvalidSyntaxError(std::string("Expected an argument for ") + lexeme + " function");
                    }
                    std::string cycle_body;
                    programm >> cycle_body;
                    
                    if (commands_0.count(cycle_body) == 1) // if this command takes no arguments
                    {
                        auto func = commands_0[cycle_body];
                        repeat(count, func);
                    }
                    else if (commands_1.count(cycle_body) == 1)
                    {
                        auto func = commands_1[cycle_body];
                        std::string arg;
                        if (!(programm >> arg)) 
                        {
                            throw InvalidSyntaxError(std::string("Expected an argument for ") + lexeme + " function");
                        }
                        repeat(count, func, arg);
                    }

                }
            }
            catch(int exception_code)
            {
                errstream << "Error with code " << exception_code << " occured - aborting the programm..." << std::endl;
                break;
            }
        }
    }
}