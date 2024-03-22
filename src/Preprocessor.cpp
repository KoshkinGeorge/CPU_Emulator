#include "Preprocessor.hpp"
#include <iostream>
#include <map>
#include <fstream>
#include "IO_dirs.hpp"


using std::string;

Preprocessor::Preprocessor()
{   
    using command_data = std::pair<string, unsigned>;
    all_commands = 
    {
        command_data("PASS", 0),

        command_data("BEGIN", 0),
        command_data("END",   0),
        command_data("PUSH",  1),
        command_data("POP",   0),
        command_data("PUSHR", 1),
        command_data("POPR",  1),
        command_data("ADD",   0),
        command_data("SUB",   0),
        command_data("MUL",   0),
        command_data("DIV",   0),
        command_data("OUT",   0),
        command_data("IN",    0),

        command_data("LABEL", 1),

        command_data("JMP",   1),
        command_data("JEQ",   1),
        command_data("JNE",   1),
        command_data("JA",    1),
        command_data("JAE",   1),
        command_data("JB",    1),
        command_data("JBE",   1),
        command_data("CALL",  1),
        command_data("RET",   0),
    };

    using code = std::pair<std::string, uint32_t>;
    codes = 
    {
        code("NONE",  0),
        code("BEGIN", 1),
        code("END",   2),
        code("PUSH",  3),
        code("POP",   4),
        code("PUSHR", 5),
        code("POPR",  6),
        code("ADD",   7),
        code("SUB",   8),
        code("MUL",   9),
        code("DIV",   10),
        code("OUT",   11),
        code("IN",    12),

        code("LABEL", 13),

        code("JMP",   14),
        code("JEQ",   15),
        code("JNE",   16),
        code("JA",    17),
        code("JAE",   18),
        code("JB",    19),
        code("JBE",   20),
        code("CALL",  21),
        code("RET",   22),

        code("AX", 10000),
        code("BX", 10001),
        code("CX", 10002),
        code("DX", 10003),
        code("SP", 10004),
        code("BP", 10005),
        code("SI", 10006),
        code("DI", 10007),
        code("IP", 10008),
        code("PC", 10009),
    };
    index = 20000; // from which indexes labels accounting starts
}

void Preprocessor::process_file(string file_name)
{
    string programm_path = string("../") + INPUT_DIR + "/" + file_name + ".txt";
    std::ifstream programm(programm_path);
    if (!programm.is_open())
    {
        throw FileNotFound(programm_path);
    }

    processed = std::ofstream(string("../") + PROCESSED_DIR + "/" + file_name + ".pcs",
                              std::ios::out | std::ios::binary);

    string command, arg;
    
    bool is_running = false;
    while(programm >> command)
    {
        if (is_running || command == "BEGIN")
        {
            if (command == "BEGIN")
            {
                is_running = true;
            }
            if (all_commands.count(command) != 1) // if this command does not exist
            {
                throw UnknownLexeme(command);
            }
            else
            {
                processed.write((char *)&codes[command], 4);
                if (all_commands[command] == 1)
                {
                    if (!(programm >> arg))
                    {
                        throw NoArgumentGiven(command);
                    }

                    if (command == "LABEL")
                    {
                        if (codes.count(arg) == 1)
                        { // If this lexeme is already in use    
                            throw LexemeReserved(arg);
                        }
                        codes.insert(std::pair<std::string, uint32_t>{arg, index++}); // adding new entity to the registry
                    }

                    if (command == "PUSH")
                    {
                        uint32_t num = std::stoul(arg);
                        processed.write((char *)&num, 4);
                    }
                    else if (codes.count(arg) == 1)
                    {  
                        processed.write((char *)&codes[arg], 4);
                    }
                    else
                    {
                        throw UnknownLexeme(arg);
                    }
                }
                else
                {
                    processed.write((char *)&codes["NONE"], 4);
                }
            }
        }
    }
    programm.close();
    processed.close();
}