#include "queue/abstract_queue.hpp"
#include <iostream>
#include <vector>
#include "stack/lstack.hpp" 

template<typename T>
StaticQueue<T> readN(int n)
{
    StaticQueue<T> q;
    for(int i = 0; i < n; ++i)
    {
        std::cout << "Input value: ";
        T element;
        std::cin >> element;
        q.enqueue(element); //push
    }
    return q;
}

template<typename T>
void print(StaticQueue<T> q)
{
    while(!q.empty())
    {
        std::cout << q.dequeue() << std::endl;
    }
}

//print a vector
template<typename T>
void print(std::vector<T> v)
{
    for(T x : v)
    {
        std::cout << x << std::endl;
    }
}


template<typename T>
StaticQueue<T> reverse(StaticQueue<T> q)
{
    lstack<T> s;
    while(q.empty())
    {
      s.push(s.dequeue());
    }
    while(!s.empty())
    {
        q.enqueue(s.pop());
    }
    return q;
}

template <typename T>
void reverseRecursiveHelper(StaticQueue<T> &q, StaticQueue<T> &result)
{
    if(q.empty())
    {
        return;
    }
    T element = q.dequeue();
    reverseRecursiveHelper(q, result);
    result.enqueue(element);
}

template<typename T>
StaticQueue<T> reverseRecursive(StaticQueue<T> q)
{
    StaticQueue<T> result;
    reverseRecursiveHelper(q, result);
    return result;
}

int findMax(StaticQueue<int> q)
{
    int maxValue = q.dequeue();
    while(!q.empty())
    {
        if(maxValue < q.head())
        {
            maxValue = q.head();
        }
        q.dequeue();
    }
    return maxValue;
}

std::vector<int> findSlidingWindowMaxValue(std::vector<int> const &number, int windowSize)
{
    StaticQueue<int> window;
    for(int i = 0; i < windowSize; ++i)
    {
        window.enqueue(number[i]);
    }
    std::vector<int> maxValues;
    maxValues.push_back(findMax(window));
    for(int i = windowSize; i < number.size(); ++i)
    {
        window.dequeue();
        window.enqueue(numbers[i]);
        maxValue.push_back(findMax(window));
    }
    return maxValues;
}
std::vector<int> findSlidingWindowMaxValue(std::vector<int> const& number, int windowSize)
{
    StaticQueue<int> window;
    int windowMaxValue = number[0];
    int sizeVector = number.size();
    for(int i = 0; i < sizeVector; ++i)
    {
        window.enqueue(numbers[i]);
        if(windowMaxValue < numbers[i])
        {
            windowMaxValue = numbers[i];
        }
    }
    std::vector<int> maxValues;
    maxValues.push_back(windowMaxValue);
    for(int i = windowSize; i < sizeVector; ++i)
    {
        if(windowMaxValue < numbers[i])
        {
            windowMaxValue = numbers[i];
        }
        window.enqueue(numbers[i]);
        if(windowMaxValue == window.dequeue())
        {
            windowMaxValue = findMax(window);
        }
        maxValues.push_back(windowMaxValue);
    }
    return maxValues;
}

int main()
{
    StaticQueue<int> q = readN<int>(4);
    print(q);
    std::cout << "now print reversed" << std::endl;
    print(reverse(q));
    std::cout << "now print recursively reversed" << std::endl;
    print(reverseRecursive(q));

    std::vector<int> values = {-1, 5, 10, 4, 123, -9, 0, -1};
    std::vector<int> maxValuesV1 = findSlidingWindowMaxValues(values, 3);
    std::vector<int> maxValuesV2 = findSlidingWindowMaxValuesV2(values, 3);

    std::cout << "----------------------"<< std::endl;
    print(maxValuesV1);
    std::cout << "---------------------" << std::endl;
    print(maxValuesV2);
    std::cout << "---------------------" << std::endl;

    return 0;
}