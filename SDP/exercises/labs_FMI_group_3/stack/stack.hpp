#ifndef __STACK_HPP
#define __STACK_HPP
#include "abstract_stack.hpp"

class Stack :public AbstractStack<int>
{
    private:
    static const int MAXSTACK = 100;
    static const int EMPTY_STACK = -1;

    //стекът
    int stack[MAXSTACK];
    //индекс на последния включен елемент
    int top;
    //проверка дали стек е запълнен на максимален капацитет
    bool full() const;

    public:
    //създаване на празен стек
    Stack();
    //проверка за празнота
    bool empty() const;
    //включване на елемент
    void push(int const& x);
    //намиране на последния включен елемент 
    int pop(); 

};

//създаване на празен стек
template<typename T>
Stack<T>::Stack()
{
    top = EMPTY_STACK;
}

//проверка за празнота
template<typename T>
bool Stack<T>::empty() const
{
    return (top == EMPTY_STACK);
}

//включване на елемент
template<typename T>
void Stack<T>::push(int const& x)
{
    if(full())
       throw std::runtime_error("Опит за включване на елемент в пълен стек!");
    stack[++top] = x;
}

//намиране на последния включен елемент
template <typename T>
int const& Stack<T>::peek() const
{
    if(empty())
        throw std::runtime_error("Опит за поглеждане на елемент в празен стек");
    assert(top >= 0 && top < MAXSTACK);
    return stack[top];
}

//изключване на последния включен елемент
template<typename T>
int Stack::pop()
{
    if(empty())
       throw std::runtime_error("Опит за изключване на елемент от празен стек");
    return stack[top--];
}

template<typename T>
bool Stack<T>::full() const
{
    return top == MAXSTACK - 1;
}

#endif