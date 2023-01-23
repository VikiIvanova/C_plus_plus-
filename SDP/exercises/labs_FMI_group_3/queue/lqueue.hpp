#ifndef __LQUEUE_HPP
#define __LQUEUE_HPP
#include <stdexcept>

#include "abstract_queue.hpp"

template <typename T>
struct QueueElement
{
    T data;
    QueueElement<T> *next;
    QueueElement(T const &_data, QueueElement<T> *_next = nullptr) : data(_data), next(_next) {}
};

template <typename T>
class LinkedQueue : public AbstractQueue<T>
{
private:
    QueueElement<T> *front, *back;

    void copy(LinkedQueue<T> const &);
    void erase();

public:
    LinkedQueue() : front(nullptr), back(nullptr) {}
    LinkedQueue(LinkedQueue<T> const &);
    LinkedQueue &operator=(LinkedQueue<T> const &);
    ~LinkedQueue();

    virtual bool empty() const { return front == nullptr; }
    virtual void enqueue(T const &) = 0;
    virtual T dequeue() = 0;
    virtual T const &head() const = 0;
    virtual T &head = 0;
};

template <typename T>
T const &LinkedQueue<T>::head() const
{
    if (empty())
        throw std::runtime_error("Опит за поглеждане в празна опашка");
    return front->data;
}

template <typename T>
T& LinkedQueue<T>::head()
{
    if(empty())
       throw std::runtime_error("Опит за поглеждане в празна опашка");
    return front->data;
}

template<typename T>
void LinkedQueue<T>::enqueue(T const& x)
{
    QueueElement<T>* newElement = new QueueElement<T>{x};
    if(empty())
       front = newElement;
    else
       back->next = newElement;
    back = newElement;
}

template<typename T>
T LinkedQueue<T>::dequeue()
{
    if(empty())
       throw std::runtime_error("Опит за изваждане от празна опашка");
    if(front == back)
       back = nullptr;
    QueueElement<T>* oldElement = front;
    front = front->next;
    T result = oldElement ->data;
    delete oldElement;
    return result;
}

template <typename T>
LinkedQueue<T>::LinkedQueue(LinkedQueue<T> const& other)
{
    copy(other);
}

template <typename T>
LinkedQueue<T>& LinkedQueue<T>::operator=(LinkedQueue<T> const& other)
{
    if(this != &other)
    {
        erase();
        copy(other);
    }
    return *this;
}

template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
    erase();
}

template<typename T>
void LinkedQueue<T>::copy(LinkedQueue<T> const& other)
{
    if(other.front != nullptr)
    {
      back = front = new QueueElement<T>{other.front->data, nullptr};
      QueueElement<T>* nextToCopy = other.front->next;
      while (nextToCopy)
      {
        back = back->next = new QueueElement<T>{nextToCopy->data, nullptr};
        nextToCopy = nextToCopy->next;
      }
    }
    else
    {
        front = back = nullptr;
    }
}

template<typename T>
void LinkedQueue<T>::erase()
{
    while(!empty())
      dequeue();
}

#pragma endif