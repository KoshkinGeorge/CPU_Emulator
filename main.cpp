#include <iostream>
#include <string>
#include "Stack.hpp"

int main()
{
    Stack<int> test(1024);
    Stack<std::string> s(1024); // выделяем под стек 1024 байта
    for (std::string el : {"ba",  "ra", "ba", "sh", "ka"})
    {
        s.push(el);
    }
    size_t length = s.get_size();
    for (int i = 0; i < length; i++)
    {
        std::cout << s.get_top() << '\n';
        s.pop();
    }
    

    for (std::string el : {"ab",  "ra", "ka", "da", "bra"})
    {
        s.push(el);
    }
    Stack<std::string> s2 = std::move(s);
    std::cout << "First Stack:\n";
    s.print(std::cout);
    std::cout << "Second Stack:\n";
    s2.print(std::cout);
    return 0;
}