#ifndef __STATICSEQSTACK_HPP
#define __STATICSEQSTACK_HPP

#include<iostream>

#define MAX_SIZE 100

class staticStack
{
    private:
    int data[MAX_SIZE];
    int top;

    public:
    staticStack() {top = -1; }
    void push(int value);
    int pop();
    int peek();
    bool isEmpty() {return top == -1; }

};

void staticStack::push(int value)
{
    if(top == MAX_SIZE - 1)
    {
        std::cout << "Error: stack overflow" << std::endl;
        return;
    }
    data[++top] = value;
}

int staticStack::pop()
{
    if(top == -1)
    {
        std::cout << "Error: stack underflow" << std::endl;
        return -1;
    }
    return data[top--];
}

int staticStack::peek()
{
    if(top == -1)
    {
        std::cout << "Error: stack is empty" << std::endl;
        return -1;
    }
    return data[top];
}



#endif
