#ifndef STACK_HPP

#define STACK_HPP
#include <iostream>
#include <vector>
#include <assert.h>

template <class T>
class Stack
{
    //  public type fields

public:
    struct node
    {
        node *next;
        T value;
    };

    //  private fields

private:
    node *top = nullptr;
    size_t size = 0;
    size_t max_size = 0;

    //  private methods
private:
    void raise_empty_stack_error();

    void raise_full_stack_error();

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
#ifndef NDEBUG
        std::cout << "Copying constructor\n";
#endif
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
            raise_full_stack_error();
        }
        node *new_nod{new node{top, new_value}};
        top = new_nod;
        ++size;
    }

    inline void push(T &&new_value)
    {
        if (size + 1 > max_size)
        {
            raise_full_stack_error();
        }
        node *new_nod = new node;
        new_nod->next = top;
        new_nod->value = new_value;
        top = new_nod;
        ++size;
    }

    Stack<T>::node *get_top();

    void pop();

    void clear();

    inline void set_max_size(size_t new_max_size)
    {
        if (size > new_max_size)
        {
            raise_full_stack_error();
        }
        else
        {
            max_size = new_max_size;
        }
    }

#ifndef NDEBUG

    std::ostream &print(std::ostream &out);

#endif
    //  friends
};

template <typename T>
inline void Stack<T>::raise_empty_stack_error()
{
    std::string message = std::string("Attempt to get the element from the empty stack in file ") +
                          __FILE__ + "\nfunction: " + __func__ + "\nLine: " + std::to_string(__LINE__);
    throw new std::out_of_range(message);
}

template <typename T>
inline void Stack<T>::raise_full_stack_error()
{
    std::string message = std::string("Run out of stack memory in file ") +
                          __FILE__ + "\nfunction: " + __func__ + "\nLine: " + std::to_string(__LINE__);
    throw new std::overflow_error(message);
}

template <typename T>
Stack<T>::Stack(Stack<T> &&ins)
{
    top = ins.top;
    size = ins.size;
    max_size = ins.max_size;
    ins.top = nullptr;
#ifndef NDEBUG
    std::cout << "Moving constructor\n";
#endif
}

template <typename T>
Stack<T>::~Stack()
{
    clear();
#ifndef NDEBUG
    std::cout << "Stack cleared!\n";
#endif
}
template <typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &ins)
{
    size = ins.size;
    max_size = max_size;
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
#ifndef NDEBUG
    std::cout << "Moving constructor\n";
#endif
    return *this;
}

// ToDo: T
template <typename T>
typename Stack<T>::node *Stack<T>::get_top()
{
    if (size <= 0)
    {
        raise_empty_stack_error();
    }
    return top;
}

template <typename T>
void Stack<T>::pop()
{
    if (size <= 0)
    {
        raise_empty_stack_error();
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

#ifndef NDEBUG

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

#endif

#endif