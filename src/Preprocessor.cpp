#include "Preprocessor.hpp"
#include <iostream>
#include <map>
#include <fstream>
#include "IO_dirs.hpp"


using std::string;
using command_data = std::pair<string, unsigned>;
std::map<string, unsigned> Preprocessor::all_commands = 
{
    command_data("BEGIN", 0),
    command_data("END", 0),
    command_data("PUSH", 1),
    command_data("POP", 0),
    command_data("PUSHR", 1),
    command_data("POPR", 1),
    command_data("ADD", 0),
    command_data("SUB", 0),
    command_data("MUL", 0),
    command_data("DIV", 0),
    command_data("OUT", 0),
    command_data("IN", 0)
};

void Preprocessor::process_file(string file_name)
{
    string programm_path = string("../") + INPUT_DIR + "/" + file_name + ".txt";
    std::ifstream programm(programm_path);
    if (programm.fail())
    {
        throw FileNotFound(programm_path);
    }

    processed = std::ofstream(string("../") + INPUT_DIR + "/" + file_name + ".pcs");

    string lexeme;
    
    bool is_running = false;
    while(programm >> lexeme)
    {
        if (is_running || lexeme == "BEGIN")
        {
            if (lexeme == "BEGIN")
            {
                is_running = true;
                continue;
            }
            else if (lexeme == "END")
            {
                break;
            }
            if (all_commands.count(lexeme) != 1) // if this command takes no arguments
            {
                throw UnknownCommand(lexeme);
            }
            else
            {
                processed << lexeme;
                for (unsigned i = 0; i < all_commands[lexeme]; i++)
                {
                    if (!(programm >> lexeme))
                    {
                        throw NoArgumentGiven(lexeme);
                    }
                    processed << " " << lexeme;
                }
                processed << "\n";
            }
        }
    }
    processed << "\0";
}