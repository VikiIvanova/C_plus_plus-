/*По подадено число 𝑘 ∈ [ 1; 𝑛 ] връща итератор (указател) към
k-тия по големина елемент от масива.*/

#include <iostream>
#include <algorithm>
#include <vector>

template <class T>
typename std::vector<T>::const_iterator
kthElement(const std::vector<T> &vec, size_t kth)
{
    using iter = typename std::vector<T>::iterator;
    if (kth > vec.size() || kth == 0)
    {
        throw std::logic_error("Invalid kth element range!");
    }

    std::vector<T> helper = vec;
    for(size_t i = 0; i < kth; i++)
    {
        iter curr = helper.begin() + i;
        iter minIt = std::min_element(curr, helper.end());
        std::iter_swap(curr, minIt);
    }

    return std::find(vec.begin(), vec.end(), helper[kth - 1]);
}

void print(const std::vector<int>& vec)
{
    for(int elem : vec)
       std::cout << elem << "\t";

    std::cout << "\n";
}

int main()
{
    std::vector<int> vec = {5, 10, 12, 43, -123, -4, 3, 1};
    print(vec);
    std::cout << "2-nd smallest element:\t" << *kthElement(vec, 2) << std::endl;
    std::cout << "4-th smallest element:\t" << *kthElement(vec, 4) << std::endl;

    return 0;
}