#ifndef __LINKEDQUEUE_HPP
#define __LINKEDQUEUE_HPP

template<typename T>
struct QueueElement
{
    T data;
    QueueElement<T>* next;
};

template <typename T>
class LinkedQueue
{
    private:
    QueueElement<T> *front, *back;

    void copyQueue(LinkedQueue<T> const&);
    void erase();

    public:
    LinkedQueue();
    LinkedQueue(LinkedQueue<T> const&);
    LinkedQueue& operator=(LinkedQueue<T> const&);
    ~LinkedQueue();

    bool empty() const;
    void push(T const& x);
    void pop();
    T& head();
    T const& head() const;

};

template<typename T>
void LinkedQueue<T>::copyQueue(LinkedQueue<T> const& other)
{
    if(other.empty())
    {
        front=back = nullptr;
    }

    QueueElement<T>* elemPtr = other.front;
    while(elemPtr)
    {
        push(elemPtr->data)
        elemPtr = elemPtr->next;
    }
}

template<typename T>
void LinkedQueue<T>::erase()
{
    while(!empty())
    {
        pop();
    }
}

template<typename T>
LinkedQueue<T>::LinkedQueue() : front(nullptr), back(nullptr) {}

template<typename T>
LinkedQueue<T>::LinkedQueue(LinkedQueue<T> const& other)
{
    copyQueue(other);
}

template<typename T>
LinkedQueue<T>& LinkedQueue<T>::operator=(LinkedQueue<T> const& other)
{
    if(this != &other)
    {
        erase();
        copyQueue(other);
    }
    return *this;
}

template<typename T>
LinkedQueue<T>::~LinkedQueue()
{
    erase();
}

template<typename T>
bool LinkedQueue<T>::empty() const
{
    return (front == nullptr && back == nullptr);
}

template<typename T>
void LinkedQueue<T>::push(T const& newElemData)
{
    QueueElement<T>* newElemPtr = new QueueElement<T>{newElemData, nullptr};

    if(!empty())
    {
        back->next = newElemPtr;
    }
    else
    {
        front = newElemPtr;
    }

    back = newElemPtr;
}

template<typename T>
void LinkedQueue<T>::pop()
{
    if(empty())
    {
        std::runtime_error("Can not delete element from an empty queue");
    }

    QueueElement<Т>* delElemPtr = front;

    front = front->next;

    if(front = nullptr)
       back = nullptr;

    delete delElemPtr;
}

template<typename T>
T& LinkedQueue<T>::head()
{
    if(empty())
    {
        throw std::runtime_error("The queue is empty!");
    }
    return front->data;
}

template<typename T>
T const& LinkedQueue<T>::head() const
{
    if(empty())
    {
        throw std::runtime_error("The queue is empty!");
    }
    return front->data;
}

#endif