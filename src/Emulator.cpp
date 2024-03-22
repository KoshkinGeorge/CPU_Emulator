#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <vector>
#include <map>

#include "Emulator.hpp"
#include "IO_dirs.hpp"
#include "Preprocessor.hpp"
#include "commands.hpp"
#include <memory>

using std::string;



Emulator::Emulator(size_t bytes_for_stack, size_t recursion_deepth):
outstream(std::string("../") + OUTPUT_DIR + "/out.txt"),
errstream(std::string("../") + OUTPUT_DIR + "/log.txt"),
preprocessor()
{
    command_vec =
    {
        // Pass commands - for alignment
        std::make_shared<Pass>(),

        std::make_shared<Begin>(),
        std::make_shared<End>(),
        std::make_shared<Push>(),
        std::make_shared<Pop>(),
        std::make_shared<PushR>(),
        std::make_shared<PopR>(),
        std::make_shared<Add>(),
        std::make_shared<Sub>(),
        std::make_shared<Mul>(),
        std::make_shared<Div>(),
        std::make_shared<Out>(),
        std::make_shared<In>(),
        
        std::make_shared<Label>(),

        std::make_shared<Jmp>(),
        std::make_shared<Jeq>(),
        std::make_shared<Jne>(),
        std::make_shared<Ja>(),
        std::make_shared<Jae>(),
        std::make_shared<Jb>(),
        std::make_shared<Jbe>(),
        std::make_shared<Call>(),
        std::make_shared<Ret>(),
    };

    state.stack = Stack<unsigned>(bytes_for_stack);
    state.call_stack = Stack<size_t>(sizeof(size_t) * recursion_deepth);

    state.registers[10000] = 0;
    state.registers[10001] = 0;
    state.registers[10002] = 0;
    state.registers[10003] = 0;
    state.registers[10004] = 0;
    state.registers[10005] = 0;
    state.registers[10006] = 0;
    state.registers[10007] = 0;
    state.registers[10008] = 0;
    state.registers[10009] = 0;
}

void Emulator::exec(std::string programm_name)
{       
    unsigned BeginIndex = 0, EndIndex = 0;
    try
    {
        std::string in_file = std::string("../") + std::string(PROCESSED_DIR) + "/" + programm_name + ".pcs";
        std::ifstream programm(in_file, std::ios::in | std::ios::binary);
        if (programm.fail())
        {
            throw FileNotFound(in_file);
        }

        uint32_t command, arg;
        std::vector<std::pair<uint32_t, uint32_t>> command_sequence;
        unsigned line_counter = 0;

        while (programm.read((char *)&command, 4) && programm.read((char *)&arg, 4))
        {   
            outstream << "Command:" << command << "\t\tArgument:" << arg << std::endl;
            command_sequence.push_back({command, arg});

            // running over the code and seeking avery function declaration
            if (command == 1)
            {
                BeginIndex = line_counter;
            }
            else if (command == 2)
            {
                EndIndex = line_counter;
            }
            else if (command == 23)
            {
                state.labels[arg] == line_counter;
            }
            line_counter++;
        }
        outstream << "\n\n\n\n";
        if (BeginIndex == 0 && EndIndex == 0)
        {
            throw NoMain("No BEGIN and END commands found");
        }

        for (state.cur_command = BeginIndex; state.cur_command != EndIndex; state.cur_command++)
        {
            outstream << "Command:" << command << "\t\tArgument:" << arg << std::endl;
            command = command_sequence[state.cur_command].first;
            arg = command_sequence[state.cur_command].second;
            command_vec[command]->exec(state, arg);
        }
    }
    catch(std::exception &e)
    {
        errstream << "Run-Time error\n" << e.what() << "\nStop execution...\n" << std::flush;
    }
    
}

int Emulator::preprocess(std::string programm_name)
{
    try
    {
        preprocessor.process_file(programm_name);
    }  
    catch (std::exception &e)
    {
        errstream << std::string("Preprocessor Error:\n") + std::string(e.what())
        << "\nPreprocessing determinated" << std::flush;
        return -1;
    }
    outstream << programm_name << " has been processed correctly!\n" << std::flush;
    return 0;
}

void Emulator::run(std::string programm_name)
{
    errstream << "\n\n\n\n\t\t\t\t------- " << programm_name << "---------\n\n" << std::endl;
    outstream << "\n\n\n\n\t\t\t\t------- " << programm_name << "---------\n\n" << std::endl;

    if (preprocess(programm_name) == 0)
    {
        exec(programm_name);
    }
} 