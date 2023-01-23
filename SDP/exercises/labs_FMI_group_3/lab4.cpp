#include "queuebystack.hpp"
#include <iostream>


int main()
{
    QueueByStacks<int> q;
    q.push(2);
    q.push(3);
    q.push(4);
    std::cout << q.pop() << std::endl;
    q.push(5);
    q.push(6);
    std::cout << "Pop: " << q.pop() << std::endl;
    std::cout << "Pop: " << q.pop() << std::endl;
    std::cout << "Pop: " << q.pop() << std::endl;
    std::cout << "Peek: " << q.peek() << std::endl;
    std::cout << "Pop: " << q.pop() << std::endl;
    try
    {
        std::cout << q.pop() << std::endl;
    }
    catch(const std::runtime_error error)
    {
        std::cerr << "Expected error: " << error.what() << std::endl;
    }
     
    return 0;
}