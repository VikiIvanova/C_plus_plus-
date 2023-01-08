#ifndef __LINKEDSTACK_HPP
#define __LINKEDSTACK_HPP
#include<algorithm>

class linkedStack
{
public:
    linkedStack();
    linkedStack(const linkedStack &other);
    linkedStack &operator=(linkedStack other);
    ~linkedStack();

    bool push(int element);
    bool pop();
    int &top();
    const int &top() const;
    bool empty() const;

    void swap(linkedStack &other);

private:
    struct Node
    {
        Node(int data = 0, Node *next = nullptr)
            : next(next), data(data) {}

        Node *next;
        int data;
    };

private:
    Node *top;
};

linkedStack::linkedStack() : top(nullptr) {}

linkedStack::linkedStack(const linkedStack &other) : linkedStack()
{
    if (!other.empty())
    {
        top = new Node(other.top->data);
        Node *nextOther = other.top->next;
        Node *currThis = top;

        while (nextOther)
        {
            currThis->next = new Node(nextOther->data);

            currThis = currThis->next;
            nextOther = nextOther->next;
        }
    }
}

linkedStack &linkedStack::operator=(linkedStack other)
{
    this->swap(other);
    return *this;
}

linkedStack::~linkedStack()
{
    Node *next;
    while (!this->empty())
    {
        next = top->next;
        delete top;
        top = next;
    }
}

bool linkedStack::push(int element)
{
    Node *newNode = new Node(element, top);
    if (!newNode)
    {
        return false;
    }
    top = newNode;

    return true;
}

bool linkedStack::pop()
{
    if (this->empty())
    {
        return false;
    }

    Node *next = top->next;
    delete top;
    top = next;

    return true;
}

int &linkedStack::top()
{
    return const_cast<int &>(std::as_const(*this).top());
}

const int& linkedStack::top() const
{
    if(this->empty())
    {
        throw std::logic_error("LinkedStack: Can't return top of an empty stack!");
    }
    return top->data;
}

bool linkedStack::empty() const
{
    return top == nullptr;
}

void linkedStack::swap(linkedStack& other)
{
    std::swap(top, other.top);
}



#endif