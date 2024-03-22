#include "Preprocessor.hpp"
#include <iostream>
#include <map>
#include <fstream>
#include "IO_dirs.hpp"
#include "codes.hpp"


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

        command_data("SAVE",  1),
    };

    using code = std::pair<std::string, Codes>;
    codes = 
    {
        code("NONE",  Codes::none),
        code("BEGIN", Codes::begin),
        code("END",   Codes::end),
        code("PUSH",  Codes::push),
        code("POP",   Codes::pop),
        code("PUSHR", Codes::pushr),
        code("POPR",  Codes::popr),
        code("ADD",   Codes::add),
        code("SUB",   Codes::sub),
        code("MUL",   Codes::mul),
        code("DIV",   Codes::div),
        code("OUT",   Codes::out),
        code("IN",    Codes::in),

        code("LABEL", Codes::label),

        code("JMP",   Codes::jmp),
        code("JEQ",   Codes::jeq),
        code("JNE",   Codes::jne),
        code("JA",    Codes::ja),
        code("JAE",   Codes::jae),
        code("JB",    Codes::jb),
        code("JBE",   Codes::jbe),
        code("CALL",  Codes::call),
        code("RET",   Codes::ret),

        code("SAVE",  Codes::save),

        code("AX", Codes::ax),
        code("BX", Codes::bx),
        code("CX", Codes::cx),
        code("DX", Codes::dx),
        code("SP", Codes::sp),
        code("BP", Codes::bp),
        code("SI", Codes::si),
        code("DI", Codes::di),
        code("IP", Codes::ip),
        code("PC", Codes::pc),
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

    string command, arg;

    while(programm >> command)
    {
        if (command == "LABEL")
        {
            programm >> arg;
            if (codes.count(arg) == 1)
            { // If this lexeme is already in use    
                codes[arg] = Codes(index++);
            }
            else
            {
                codes.insert(std::pair<std::string, Codes>{arg, Codes(index++)}); // adding new entity to the registry
            }
        }
    }
    programm.close();
    programm = std::ifstream(programm_path);
    

    processed = std::ofstream(string("../") + PROCESSED_DIR + "/" + file_name + ".pcs",
                              std::ios::out | std::ios::binary);


    
    bool is_running = false;
    while(programm >> command)
    {
        if (is_running || command == "BEGIN" || command == "LABEL")
        {
            if (command == "BEGIN" || command == "LABEL")
            {
                is_running = true;
            }
            if (all_commands.count(command) != 1) // if this command does not exist
            {
                throw UnknownLexeme(command);
            }
            else
            {
                processed.write((char *)&codes[command], sizeof(int));
                if (all_commands[command] == 1)
                {
                    if (!(programm >> arg))
                    {
                        throw NoArgumentGiven(command);
                    }

                    if (command == "PUSH")
                    {
                        int num = std::stoul(arg);
                        processed.write((char *)&num, sizeof(int));
                    }
                    else if (codes.count(arg) == 1)
                    {  
                        processed.write((char *)&codes[arg], sizeof(int));
                    }
                    else
                    {
                        throw UnknownLexeme(arg);
                    }
                }
                else
                {
                    processed.write((char *)&codes["NONE"], sizeof(int));
                }
            }
        }
    }
    programm.close();
    processed.close();
}
