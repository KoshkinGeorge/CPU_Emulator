#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <map>

#include "Emulator.hpp"
#include "IO_dirs.hpp"
#include "Preprocessor.hpp"
#include "commands.hpp"
#include <memory>

using std::string;



Emulator::Emulator(size_t bytes_for_stack):
outstream(std::string("../") + OUTPUT_DIR + "/out.txt"),
errstream(std::string("../") + OUTPUT_DIR + "/log.txt"),
preprocessor()
{
    command_map["BEGIN"] = std::make_shared<Command>()

    stack = Stack<unsigned>(bytes_for_stack);

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
}

void Emulator::exec(std::string programm_name)
{   
    errstream << "\n\n\n\n\t\t\t\t------- " << programm_name << "---------\n\n" << std::endl;
    outstream << "\n\n\n\n\t\t\t\t------- " << programm_name << "---------\n\n" << std::endl;
    
    try
    {
        std::string in_file = std::string("../") + std::string(INPUT_DIR) + "/" + programm_name + ".pcs";
        std::ifstream programm(in_file);
        if (programm.fail())
        {
            throw FileNotFound(in_file);
        }
        std::string command, arg;
        Command::State state(stack, registers, running, arg);
        state.registers = registers;
        state.stack = stack;
        state.running = running;
        while (programm >> command)
        {   
            while (programm >> state.next_lexeme && state.next_lexeme != "&") {}
            commands[command]->exec(state);
        }
    }
    catch(std::exception &e)
    {
        errstream << "Run-Time error\n" << e.what() << "\nStop execution...\n";
    }
    
}

void Emulator::preprocess(std::string programm_name)
{
    try
    {
        preprocessor.process_file(programm_name);
    }  
    catch (std::exception &e)
    {
        errstream << std::string("Preprocessor Error:\n") + std::string(e.what())  << "\nPreprocessing determinated";
        return;
    }
    outstream << programm_name << " has been processed correctly!\n";
}