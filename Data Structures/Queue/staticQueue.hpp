#ifndef __STATICQUEUE_HPP
#define __STATICQUEUE_HPP

#define CAPACITY 4

class staticQueue
{
private:
    int data[CAPACITY];
    size_t headIndex;
    size_t tailIndex;
    size_t size;

public:
    staticQueue();
    void enqueue(const int &element);
    int dequeue();
    void push(const int &elem);
    void pop();
    int &front();
    const int &front() const;
    size_t size() const;
    bool empty() const;
};

inline staticQueue::staticQueue() : headIndex(0),
                                    tailIndex(0),
                                    size(0) {}

inline void staticQueue::enqueue(const int& element)
{
    if(size == CAPACITY)
       throw std::logic_error("staticQueue: enqueue to a full queue!");

    data[tailIndex++] = element;

    if(tailIndex >= CAPACITY)
       tailIndex = 0;
    
    ++size;
}

inline int staticQueue::dequeue()
{
    if(this->empty())
       throw std::logic_error("StaticQueue: dequeue from an empty queue!");
    
    int  res = data[headIndex++];

    if(headIndex >= CAPACITY)
       headIndex = 0;

    --size;
    return res;
}

inline void staticQueue::push(const int& element)
{
    this->enqueue(element);
}

inline void staticQueue::pop()
{
    this->dequeue();
}

inline int& staticQueue::front()
{
    return const_cast<T&>(*this).front());
}

inline const int& staticQueue::front() const
{
    if(this->empty())
       throw std::logic_error("StaticQueue: front of an empty queue!");

    return data[headIndex];
}

inline size_t staticQueue::size() const
{
    return size;
}

inline bool staticQueue::empty() const
{
    return this->size() == 0;
}
