#pragma once 

#include <iostream>
#include <vector>
#include <assert.h>
#include "../../../include/my_funcs.hpp"

template <class T>
class Stack
{
//  private type fields
private:
    struct node
    {
        node *next;
        T value;
    };

//  public type fields
public:
    class EmptyStackError : public std::exception
    {
    private:
        std::string msg{};
    public:
        EmptyStackError(std::string message)
            : msg(message) {}
        
        const char* what() const noexcept override 
        {
            return to_c_str(std::string("Trying to get an element from the empty Stack...\n") + msg);
        }
    };

    class FullStackError : public std::exception
    {
    private:
        std::string msg{};
    public:
        FullStackError(std::string message)
            : msg(message) {}
        
        const char* what() const noexcept override 
        {
            return to_c_str(std::string("Memory for stack has exeeded...\n") + msg);
        }
    };

    //  private fields
private:
    node *top = nullptr;
    size_t size = 0;
    size_t max_size = 0;

    //  private methods
private:

    //  public fields
public:
    //  public methods
public:
    //  default constractor
    Stack() = default;

    Stack(size_t bytes_given) : max_size((bytes_given - 3 * sizeof(size_t)) / sizeof(node)) {}
    // самому стеку надо 3 * sizeof(size_t) байт памяти + каждому
    // элементу стека надо по sizeof(nod)

    // copying constractor
    Stack(const Stack &ins)
    {
        *this = ins;
    }

    //  moving constructor
    Stack(Stack &&ins);

    // destructor
    ~Stack();

    //  some methods are defined right here - so it can be inlined in future
    Stack &operator=(const Stack &ins);

    Stack &operator=(Stack &&ins);

    inline bool empty() const
    {
        return (size == 0);
    }

    inline size_t get_size() const
    {
        return size;
    }

    inline void push(T &new_value)
    {
        if (size + 1 > max_size)
        {
            throw FullStackError("In push method");
        }
        node *new_nod{new node{top, new_value}};
        top = new_nod;
        ++size;
    }

    inline void push(T &&new_value)
    {
        if (size + 1 > max_size)
        {
            throw FullStackError("In push method");
        }
        node *new_nod = new node;
        new_nod->next = top;
        new_nod->value = new_value;
        top = new_nod;
        ++size;
    }

    T &get_top();

    void pop();

    void clear();

    inline void set_max_size(size_t new_max_size)
    {
        if (size > new_max_size)
        {
            throw FullStackError("In set_max_size method");
        }
        else
        {
            max_size = new_max_size;
        }
    }

    std::ostream &print(std::ostream &out);

    //  friends
};


template <typename T>
Stack<T>::Stack(Stack<T> &&ins)
{
    top = ins.top;
    size = ins.size;
    max_size = ins.max_size;
    ins.top = nullptr;
}

template <typename T>
Stack<T>::~Stack()
{
    clear();
}
template <typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &ins)
{
    size = ins.size;
    max_size = ins.max_size;
    if (size == 0)
    {
        top = nullptr;
    }
    else
    {
        top = new node({ins.top->value, nullptr});
        node *temp = top;
        for (const node *cur = ins.top->next; cur != nullptr; cur = cur->next)
        {
            temp->next = new node({cur->value, nullptr});
            temp = temp->next;
        }
    }
    return *this;
}

template <typename T>
Stack<T> &Stack<T>::operator=(Stack<T> &&ins)
{
    top = ins.top;
    size = ins.size;
    max_size = ins.max_size;
    ins.top = nullptr;
    return *this;
}

// ToDo: T
template <typename T>
T &Stack<T>::get_top()
{
    if (size <= 0)
    {
        throw EmptyStackError("In get_top method");
    }
    return top->value;
}

template <typename T>
void Stack<T>::pop()
{
    if (size <= 0)
    {
        throw EmptyStackError("In pop method");
    }
    node *temp = top->next;
    delete top;
    top = temp;
    --size;
}

template <typename T>
void Stack<T>::clear()
{
    while (top)
    {
        pop();
    }
}

template <typename T>
std::ostream &Stack<T>::print(std::ostream &out)
{
    for (Stack<T>::node *cur = top; cur != nullptr; cur = cur->next)
    {
        out << "\n\t\t\t\t|\t" << cur->value << "\t|\n"
            << std::endl;
    }
    return out;
}
