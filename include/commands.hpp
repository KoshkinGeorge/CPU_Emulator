#pragma once
#include <iostream>
#include <Stack.hpp>
#include <map>
#include <vector>

#include "State.hpp"
#include "my_funcs.hpp"


class DivisionByZero : public std::exception
{
private:
    std::string num1;

public:
    DivisionByZero(const char *num): num1(num) {}

    const char* what() const noexcept override
    {
        return to_c_str(("Trying to devide ") + num1 + "by zero");
    }
};


class ExpectedAnArgument : public std::exception
{
private:
    std::string arg_name;

public:
    ExpectedAnArgument(const char *_arg_name):   arg_name(_arg_name) {}

    const char* what() const noexcept override
    {
        return to_c_str(("Expected: ") + arg_name + "\nGot: Nothing");
    }
};


class Command
{
public:
    virtual void exec(State& state, int arg) const
    {

    }
};


class Pass: public Command
{
public:
    void exec(State& state, int arg) const override;
};


class Begin: public Command
{
public:
    void exec(State& state, int arg) const override;
};




class End: public Command
{
public:
    void exec(State& state, int arg) const override;
};



class Pop: public Command
{
public:
    void exec(State& state, int arg) const override;
};



class Add: public Command
{
public:
    void exec(State& state, int arg) const override;
};



class Sub: public Command
{
public:
    void exec(State& state, int arg) const override;
};



class Mul: public Command
{
public:
    void exec(State& state, int arg) const override;
};



class Div: public Command
{
public:
    void exec(State& state, int arg) const override;
};



class Out: public Command
{
public:
    void exec(State& state, int arg) const override;
};



class In: public Command
{
public:
    void exec(State& state, int arg) const override;
};



class Push: public Command
{
public:
    void exec(State& state, int arg) const override;
};



class PushR: public Command
{
public:
    void exec(State& state, int arg) const override;
};



class PopR: public Command
{
public:
    void exec(State& state, int arg) const override;
};


class Jmp: public Command
{
public:
    void exec(State& state, int arg) const override;
};


class Jeq: public Command
{
public:
    void exec(State& state, int arg) const override;
};


class Jne: public Command
{
public:
    void exec(State& state, int arg) const override;
};


class Ja: public Command
{
public:
    void exec(State& state, int arg) const override;
};


class Jae: public Command
{
public:
    void exec(State& state, int arg) const override;
};


class Jb: public Command
{
public:
    void exec(State& state, int arg) const override;
};


class Jbe: public Command
{
public:
    void exec(State& state, int arg) const override;
};


class Call: public Command
{
public:
    void exec(State& state, int arg) const override;
};


class Ret: public Command
{
public:
    void exec(State& state, int arg) const override;
};


class Save: public Command
{
public:
    void exec(State& state, int arg) const override;
};