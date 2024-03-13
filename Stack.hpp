#ifndef STACK_HPP

#define STACK_HPP
#include <iostream>
#include <vector>
#include <assert.h>


template <class T> 
class Stack
{
//  private type fields

private:
    struct nod 
    {
        T value;
        nod* next;
    };

//  private fields

private:
    nod *top=nullptr;
    size_t size=0;

//  private methods
private:
    void raiseEmptyStackError();

//  public fields
public:


//  public methods
public:
    //  default constractor
    Stack() = default;
    
    //copying constractor
    Stack(const Stack &ins)
    {
        *this = ins;
        std::cout << "Copying constructor";
    }
    
    //  moving constructor
    Stack(Stack&& ins);

    // destructor
    ~Stack();

    //  some methods are defined right here - so it can be inlined in future
    Stack& operator=(const Stack& ins);

    Stack& operator=(Stack&& ins);

    inline bool empty() const
    {
        return (size == 0);
    }

    inline size_t get_size() const
    {
        return size;
    }

    inline void push(T new_value)
    {
        nod *new_nod{new nod{new_value, top}};
        top = new_nod;
        ++size;
    }

    inline void push(T&& new_value)
    {
        nod *new_nod{new nod{new_value, top}};
        top = new_nod;
        ++size;
    }

    T get_top();

    void pop();

    void clear();

    #ifndef NDEBUG

    std::ostream& print(std::ostream & out);

    #endif
//  friends

};


template<typename T>
void Stack<T>::raiseEmptyStackError()
{
    std::string message = std::string("Attempt to get the element from the empty stack in file ") +
    __FILE__ + "\nfunction: " + __func__ + "\nLine: " + std::to_string(__LINE__);
    throw new std::out_of_range(message);
}

template<typename T>
Stack<T>::Stack(Stack<T>&& ins)
{
    top = ins.top;
    size = ins.size;
    ins.top = nullptr;
    std::cout << "Moving constructor\n";
}

template<typename T>
Stack<T>::~Stack()
{
    clear();
    std::cout << "Stack cleared!\n";
}
template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& ins)
{
    size = ins.size;
    if (size == 0)
    {
        top = nullptr;
    }
    else
    {
        top = new nod({ins.top->value, nullptr});
        nod* temp = top;
        for (const nod* cur = ins.top->next; cur != nullptr; cur = cur->next)
        {
            temp->next = new nod({cur->value, nullptr});
            temp = temp->next;
        }
    }
    return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& ins)
{
    top = ins.top;
    size = ins.size;
    ins.top = nullptr;
    std::cout << "Moving constructor";
    return *this;
}

template<typename T>
T Stack<T>::get_top()
{
    if (size <= 0)
    {
        raiseEmptyStackError();
    }
    return top->value;
}

template<typename T>
void Stack<T>::pop()
{
    if (size <= 0)
    {
        raiseEmptyStackError();
    }
    nod *temp = top->next;
    delete top;
    top = temp;
    --size;
}

template<typename T>
void Stack<T>::clear()
{
    while (top)
    {
        pop();
    }
}

#ifndef NDEBUG

template <typename T>
std::ostream& Stack<T>::print(std::ostream & out)
{
    for (Stack<T>::nod* cur = top; cur != nullptr; cur=cur->next)
    {
        out << "\n\t\t\t\t|\t" << cur->value << "\t|\n";
    }
    return out;
}

#endif

#endif