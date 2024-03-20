#pragma once
#include <iostream>
#include <Stack.hpp>
#include <map>

class Command
{
public:
    class DivisionByZero : public std::exception
    {
    private:
        std::string num1{};
    
    public:
        DivisionByZero(const char *num): num1(num) {}
    
        const char* what() const noexcept override
        {
            return (("Trying to devide ") + num1 + "by zero").c_str();
        }
    };


    class ExpectedAnArgument : public std::exception
    {
    private:
        std::string arg_name{};
    
    public:
        ExpectedAnArgument(const char *_arg_name):   arg_name(_arg_name) {}
    
        const char* what() const noexcept override
        {
            return (("Expected: ") + arg_name + "\nGot: Nothing").c_str();
        }
    };

    

protected:
    struct State
    {
    private:
        using reg_map = std::map<std::string, unsigned>;

    public:
        Stack<unsigned> &stack;
        reg_map &registers;
        bool &running;
        std::string next_lexeme;
        
        State(Stack<unsigned> &s, reg_map &r, bool &run, const std::string &next_lexeme): stack(s), registers(r), running(run) {}
    };

    static const std::string name;

public:
    virtual void exec(State& state) const;
};




class Begin: public Command
{
protected:
    static const std::string name;

public:
    void exec(State& state) const override;
};




class End: public Command
{
protected:
    static const std::string name;

public:
    void exec(State& state) const override;
};



class Pop: public Command
{
protected:
    static const std::string name;

public:
    void exec(State& state) const override;
};



class Add: public Command
{
protected:
    static const std::string name;

public:
    void exec(State& state) const override;
};



class Sub: public Command
{
protected:
    static const std::string name;

public:
    void exec(State& state) const override;
};



class Mul: public Command
{
protected:
    static const std::string name;

public:
    void exec(State& state) const override;
};



class Div: public Command
{
protected:
    static const std::string name;

public:
    void exec(State& state) const override;
};



class Out: public Command
{
protected:
    static const std::string name;

public:
    void exec(State& state) const override;
};



class In: public Command
{
protected:
    static const std::string name;

public:
    void exec(State& state) const override;
};



class Push: public Command
{
protected:
    static const std::string name;

public:
    void exec(State& state) const override;
};



class PushR: public Command
{
protected:
    static const std::string name;

public:
    void exec(State& state) const override;
};



class PopR: public Command
{
protected:
    static const std::string name;

public:
    void exec(State& state) const override;
};



/*class Begin: public Command
{
private:
    std::string name;

public:
    void exec(State& state) const override;
};



class Begin: public Command
{
private:
    std::string name;

public:
    void exec(State& state) const override;
};


class Begin: public Command
{
private:
    std::string name;

public:
    void exec(State& state) const override;
};



class Begin: public Command
{
private:
    std::string name;

public:
    void exec(State& state) const override;
};



class Begin: public Command
{
private:
    std::string name;

public:
    void exec(State& state) const override;
};



class Begin: public Command
{
private:
    std::string name;

public:
    void exec(State& state) const override;
};



class Begin: public Command
{
private:
    std::string name;

public:
    void exec(State& state) const override;
};



class Begin: public Command
{
private:
    std::string name;

public:
    void exec(State& state) const override;
};*/