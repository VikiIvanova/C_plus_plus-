#ifndef __RSTACK_HPP
#define __RSTACK_HPP
#include <cstddef>
#include <cassert>
#include <iostream>
#include <exception>
#include "abstract_stack.hpp"

class ResizingStack : public AbstactStack<int>
{
    private:
    static const int EMPTY_STACK = -1;
    static const int INITSTACK = 10;

    //указател към масива на стека
    T* stack;

    //индекс на последния включен елемент
    int top;

    //капацитет
    size_t capacity;

    //проверка дали стек е запълнен на максимален капацитет
    bool full() const;

    //разширяване на стека
    void resize();

    //копиране на стека
    void copydData(ResizingStack const&);

    public:
    //създаване на празен стек
    ResizingStack();

    //конструктор за копиране
    ResizingStack(ResizingStack const&);

    //операция за присвояване
    ResizingStack operator=(ResizingStack const&);

    //деструктор 
    ~ResizingStack();

    //проверка за празнота
    bool empty() const;

    //включване на елемент
    void push(int const& x);

    //намиране на последния включен елемент
    T const& peek() const;

    //изключване на последния включен елемент
    T pop();
};

//създаване на празен стек
template<typename T>
ResizingStack<T>::ResizingStack() : capacity(INITSTACK), top(EMPTY_STACK)
{
    //заделяме първоначалния размер
    stack = new T[capacity];
}

template<typename T>
ResizingStack<T>::ResizingStack(ResizingStack const& other)
              : top(other.top), capacity(other.capacity)
{
    copyData(other);
}

template<typename T>
ResizingStack<T>::~ResizingStack()
{
    delete[] stack;
}

template<typename T>
void ResizingStack<T>::copyData(ResizingStack const& other)
{
    stack = new int[capacity];
    for(int i = 0; i <= top; ++i)
        stack[i] = other.stack[i];
}

ResizingStack<T>& ResizingStack::operator=(ResizingStack const& other)
{
    if(this != &other)
    {
        delete[] stack;
        top = other.top;
        capacity = other.capacity;
        copyData(other);
    }
    return *this;
}

//проверка за празнота
template<typename T>
bool ResizingStack<T>::empty() const
{
    return top == EMPTY_STACK;
}

//включване на елемент
template<typename T>
void ResizingStack<T>::push(int const& x)
{
    if(full())
       resize();
    stack[++top] = x;
}

//намиране на последен включен елемент
template<typename T>
T const& ResizingStack<T>::peek() const{
    assert(!empty());
    return stack[top];
}

//изключване на последния включен елемент
template<typename T>
T ResizingStack<T>::pop()
{
    if(empty())
       throw std::runtime_error("Опит за изключване на елемент в празен стек");
    return stack[top--];
}

template < typename T>
bool ResizingStack<T>::full() const
{
    return top == capacity - 1;
}

template<typename T>
void ResizingStack<T>::resize()
{
    //разчиатаме, че викаме resize само когато стекът е пълен
    size_t newcapacity = 2 * capacity;
    std::clog << "Разширяваме стека до " << newcapacity << std::endl;
    int* newstack = new int[newcapacity];
    for(int i = 0; i < capacity; ++i)
        newstack[i] = stack[i];
    capacity = newcapacity;
    delete[] stack;
    stack = newstack;
}

#endif