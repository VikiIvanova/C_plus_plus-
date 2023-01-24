/*Връща нов масив съдържащ само неповтарящите се елементи
на оригиналния.*/

#include <iostream>
#include <algorithm>
#include <vector>

template<class T>
std::vector<T> unique(const std::vector<T>& vec)
{
    std::vector<T> res;
    std::vector<T> sorted = vec;
    std::sort(sorted.begin(), sorted.end());

    res.push_back(sorted.front());
    for(size_t i = 1; i < sorted.size() - 1; ++i)
    {
        if(sorted[i] != sorted[i - 1])
        {
            res.push_back(sorted[i]);
        }
    }
    return res;
}

void print(const std::vector<int>& vec)
{
    for(int elem : vec)
       std::cout << elem << "\t";

    std::cout << std::endl;
}

int main()
{
    std::vector<int> vec = {5, 10, -4, 12, 10, 43, -123, 5, 10, -4, 1, 5};

    print(vec);
    print(unique(vec));

    return 0;
}