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
#include "codes.hpp"
#include <memory>

using std::string;



Emulator::Emulator(size_t bytes_for_stack, size_t recursion_deepth):
outstream(std::string("../") + OUTPUT_DIR + "/out.txt"),
errstream(std::string("../") + OUTPUT_DIR + "/log.txt"),
preprocessor()
{
    command_vec =
    {
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

        std::make_shared<Pass>(),

        std::make_shared<Jmp>(),
        std::make_shared<Jeq>(),
        std::make_shared<Jne>(),
        std::make_shared<Ja>(),
        std::make_shared<Jae>(),
        std::make_shared<Jb>(),
        std::make_shared<Jbe>(),
        std::make_shared<Call>(),
        std::make_shared<Ret>(),

        std::make_shared<Save>(),
    };

    state.stack = Stack<unsigned>(bytes_for_stack);
    state.call_stack = Stack<size_t>(sizeof(size_t) * recursion_deepth);

    state.registers[(int)Codes::ax] = 0;
    state.registers[(int)Codes::bx] = 0;
    state.registers[(int)Codes::cx] = 0;
    state.registers[(int)Codes::dx] = 0;
    state.registers[(int)Codes::sp] = 0;
    state.registers[(int)Codes::bp] = 0;
    state.registers[(int)Codes::si] = 0;
    state.registers[(int)Codes::di] = 0;
    state.registers[(int)Codes::ip] = 0;
    state.registers[(int)Codes::pc] = 0;
}

void Emulator::exec(std::string programm_name)
{
    try
    {
        std::string in_file = std::string("../") + std::string(PROCESSED_DIR) + "/" + programm_name + ".pcs";
        std::ifstream programm(in_file, std::ios::in | std::ios::binary);
        if (programm.fail())
        {
            throw FileNotFound(in_file);
        }

        int command, arg;
        std::vector<std::pair<int, int>> command_sequence;
        unsigned line_counter = 0;
        unsigned BEGIN_index = 0;

        while (programm.read((char *)&command, sizeof(int)) && programm.read((char *)&arg, sizeof(int)))
        {   
            if (command == (int)Codes::begin)
            {
                BEGIN_index = line_counter;
            }
            if (command == (int)Codes::label)
            {
                state.labels.insert(std::pair<int, unsigned>{arg, line_counter});
            }
            command_sequence.push_back({command, arg});
            line_counter++;
        }

        for (state.cur_command = BEGIN_index; state.cur_command < command_sequence.size(); state.cur_command++)
        {
            command = command_sequence[state.cur_command].first;
            arg = command_sequence[state.cur_command].second;
            command_vec[command]->exec(state, arg);
            outstream << "Command:" << command << "\t\tArgument:" << arg << std::endl;
        }
    }
    catch(std::exception &e)
    {
        errstream << "Run-Time error\n" << e.what() << "\nStop execution...\n" << std::flush;
    }
    clear();   
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

// cleaning everythong left from the previous programm
void Emulator::clear()
{
    unsigned index = 20000;
    while (state.labels.count(index) == 1)
    {
        state.labels.erase(index);
    }
    state.stack.clear();
} 



