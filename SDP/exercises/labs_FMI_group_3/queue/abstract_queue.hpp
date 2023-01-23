#ifndef __ABSTRACT_QUEUE_HPP
#define __ABSTRACT_QUEUE_HPP

template<typename T>
class AbstactQueue
{
    public:
    virtual bool empty() const = 0;
    virtual void enqueue(T const&) = 0;
    virtual T dequeue() = 0;
    virtual T const& head() const = 0;
    virtual T& head() = 0;
    virtual ~AbstactQueue() {}
};

#endif