#include <iostream>
#include "Stack.hpp"
#include "commands.hpp"
#include <map>
#include <sstream>

//  commands_0 - without args

void Begin::exec(State &state) const
{
    state.running = true;
}
const std::string Begin::name = "BEGIN";



void End::exec(State &state) const
{
    state.running = false;
}
const std::string End::name = "END";




void Pop::exec(State &state) const
{
    //  all errors are being catched at the top level
    state.stack.pop(); 
}
const std::string Pop::name = "POP";



void Add::exec(State &state) const
{
    state.running = true;
    unsigned num1 = state.stack.get_top();
    state.stack.pop();
    unsigned num2 = state.stack.get_top();
    state.stack.push(num1);
    state.stack.push(num1 + num2);
}
const std::string Add::name = "ADD";



void Sub::exec(State &state) const
{
    unsigned num1 = state.stack.get_top();
    state.stack.pop();
    unsigned num2 = state.stack.get_top();
    state.stack.push(num1);
    state.stack.push(num1 - num2);
}
const std::string Sub::name = "SUB";




void Mul::exec(State &state) const
{
    unsigned num1 = state.stack.get_top();
    state.stack.pop();
    unsigned num2 = state.stack.get_top();
    state.stack.push(num1);
    state.stack.push(num1 * num2);
}
const std::string Mul::name = "MUL";



void Div::exec(State &state) const
{
    unsigned num1 = state.stack.get_top();
    state.stack.pop();
    unsigned num2 = state.stack.get_top();
    state.stack.push(num1);
    state.stack.push(num1 + num2);
    if (num2 == 0)
    {
        std::ostringstream oss;
        oss << num1;
        throw DivisionByZero(oss.str().c_str());
    }
    state.stack.push(num1 / num2);
}
const std::string Div::name = "DIV";



void Out::exec(State &state) const
{
    unsigned num = state.stack.get_top();
    state.stack.pop();
    std::cout << "You got the number from the top: " << num << std::endl;
}
const std::string Out::name = "OUT";



void In::exec(State &state) const
{
    unsigned num;
    if (!(std::cin >> num))
    {
        throw ExpectedAnArgument("Num for IN command");
    }
    state.stack.push(num);
}
const std::string In::name = "IN";



void Push::exec(State &state) const
{
    state.stack.push(std::move(std::stoul(state.next_lexeme)));
}
const std::string Push::name = "PUSH";



void PushR::exec(State &state) const
{
    // if user tries to get a value from random register - he would be given a value left there from previous programms
    unsigned value = state.registers[state.next_lexeme]; 
    state.stack.push(value);
}
const std::string PushR::name = "PUSHR";



void PopR::exec(State &state) const
{
    unsigned value = state.stack.get_top();
    state.stack.pop();
    state.registers[state.next_lexeme] = value;
}
const std::string PopR::name = "POPR";