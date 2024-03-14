#ifndef CPU_EM_HPP

#define CPU_EM_HPP

#include <iostream>
#include <fstream>
#include "Stack.hpp"

class CPU_Em
{
//  private type fields
private:
    inline void file_not_found_error(std::string file_name)
    {
        std::string message = std::string("Trying to open an unexisting file") + file_name +    std::string(" in file ") + __FILE__ + "\nfunction: " + __func__ + "\nLine: " + std::to_string(__LINE__);
        throw new std::out_of_range(message);
    }
//  private fields
private:
    std::ifstream programm; //  in.txt file
    std::ofstream out;
    std::ofstream err;

//  private methods
private:

//  public fields
public:
    

//  public methods
public:
    CPU_Em(std::string out_file,
    std::string err_file);

    void print(std::string mes);

    void exec(std::string in_file);
//  friends

};

#endif