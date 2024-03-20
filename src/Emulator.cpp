#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include "Emulator.hpp"
#include "IO_dirs.hpp"
#include "Preprocessor.hpp"

using std::string;



Emulator::Emulator(size_t bytes_for_stack):
outstream(std::string("../") + OUTPUT_DIR + "/out.txt"),
errstream(std::string("../") + OUTPUT_DIR + "/log.txt"),
preprocessor()
{
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
    static unsigned counter = 1;
    std::string in_file = std::string("../") + std::string(INPUT_DIR) + "/" + programm_name + ".txt";
    // distinguishing marks
    errstream << "\n\n\n\n\t\t\t\t------- " << programm_name << "---------\n\n" << std::endl;
    outstream << "\n\n\n\n\t\t\t\t------- " << programm_name << "---------\n\n" << std::endl;
    
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