//Връща копие на масива, но с елементите му в обратен ред.

#include <iostream>
#include <vector>

//Reverse a vector using indecies
std::vector<int> reversed_ind(const std::vector<int>& vec)
{
    std::vector<int> res;
    res.reserve(vec.size());
    
    for(int i = vec.size() - 1; i >= 0; i--)
        res.push_back(vec[i]);
    
    return res;
}

//Generic function to reverse a vector with iterators
template<class T>
std::vector<T> reversed(const std::vector<T>& vec)
{
    std::vector<T> res;
    res.reserve(vec.size());

    using criterator_t = typename std::vector<T>::const_reverse_iterator;
    criterator_t it = vec.crbegin();

    for(; it != vec.crend(); it++)
    {
        res.push_back(*it);
    }
    return res;
}

int main()
{
    std::vector<int> vec = {5, 10, 12, 43, -123, -4, 3, 1};
    std::vector<int> revVec = reversed(vec);

    for(int elem : revVec)
     std::cout << elem << " ";

    std::cout << std::endl;

    for(int elem : reversed_ind(vec))
    {
        std::cout << elem << " ";
    }

    return 0;
}