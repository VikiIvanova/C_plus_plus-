#include <iostream>
#include <vector>
#include <algorithm>

void countingSort(std::vector<int>& vec)
{
    int diff = *std::max_element(vec.begin(), vec.end()) - *std::min_element(vec.begin(), vec.end()) + 1;
    std::vector<int> countArr(diff, 0);

    for(size_t i = 0; i < vec.size(); ++i)
        ++countArr[vec[i]];

    int resIndex = 0;
    for(size_t i = 0; i < countArr.size(); ++i)
    {
        while(countArr[i] > 0)
        {
            vec[resIndex] = i;
            --countArr[i];
            ++resIndex;
        }
    }
}

int main()
{
    std::vector<int> arr = {50, 2, 3, 6, 1, 0, 4};
    countingSort(arr);
    std::cout << "Counting sorted: ";
    for(int elem : arr)
       std::cout << elem << " ";
    
    std::cout << std::endl;

    return 0;
}