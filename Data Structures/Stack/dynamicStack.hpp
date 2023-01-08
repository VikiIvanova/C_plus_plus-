#ifndef __DYNAMICSTACK_HPP
#define __DYNAMICSTACK_HPP

class dynamicStack
{
    private:
    int* data;
    size_t size;
    size_t capacity;

    public:
    dynamicStack();
    dynamicStack(const dynamicStack& other);
    dynamicStack& operator=(dynamicStack other);
    ~dynamicStack();

    bool push(int element);
    bool pop();
    int& top();
    const int& top() const;
    bool empty() const;
    void swap(dynamicStack& other);

    private:
    bool resize();
};

dynamicStack::dynamicStack() : data(nullptr),
                               size(0),
                               capacity(0) {}

dynamicStack::dynamicStack(const dynamicStack& other) : dynamicStack()
{
    data = new int[other.capacity];
    capacity = other.capacity;
    for(size_t i = 0; i < other.size; ++i)
    {
        data[i] = other.data[i];
        ++size;
    }
}

dynamicStack::~dynamicStack()
{
    delete[] data;
    data = nullptr;
    size = 0;
    capacity = 0;
}

bool dynamicStack::push(int element)
{
    if(size >= capacity)
    {
        if(!resize())
        {
            return false;
        }
    }
    data[size] =  elem;
    ++size;

    return true;
}

bool dynamicStack::pop()
{
    if(size == 0)
    {
        return false;
    }
    --size;
    return true;
}

int& dynamicStack::top()
{
    return const_cast<int&>(std::as_const(*this).top());
}

const int& dynamicStack::top() const
{
    if(this->empty())
    {
        throw std::logic_error("Can't return top of an empty stack!");
    }
    return data[size - 1];
}

bool dynamicStack::empty() const
{
    return size == 0;
}

void dynamicStack::swap(dynamicStack& other)
{
    std::swap(data, other.data);
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
}

bool dynamicStack::resize()
{
    size_t newCapacity;
    if(capacity == 0)
    {
        newCapacity = 4;
    }
    else
    {
        newCapacity = 2 * capacity;
    }
    if(!(newCapacity > capacity))
    {
        return false;
    }

    int* newData = new(std::nothrow) int[newCapacity];
    if(!newData)
    {
        return false;
    }
    for(size_t i = 0; i < capacity; ++i)
    {
        std::swap(newData[i], data[i]);
    }

    delete[] data;
    data = newData;
    capacity = newCapacity;

    return true;
}