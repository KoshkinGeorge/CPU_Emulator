#include <iostream>
#include <string>
#include <fstream>
#include "CPU_Em.hpp"

using std::string;


CPU_Em::CPU_Em(string out_file,
string err_file):
out(out_file), err(err_file) {
    if (!out || !err) // if failed to open one of the files
    {
        file_not_found_error(!out? out_file : err_file);
    }
}

void CPU_Em::exec(std::string in_file)
{
    programm = std::ifstream(in_file);
    if (!programm)
    {
        file_not_found_error(in_file);
    }
}

void CPU_Em::print(std::string mes)
{
    out << mes;
}