//Намерете двойка числа от даден масив, която се сумира до дадено
//число sum.

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

void findPair1(const std::vector<int>& arr, size_t n, int sum)
{
    for(size_t i = 0; i < n - 1; i++)
    {
        for(size_t j = i + 1; j < n; j++)
        {
            if(arr[i] + arr[j] == sum)
            {
                std::cout <<"Pair found at index " << i << " and " << j << std::endl;
                return;
            }
        }
    }
    std::cout << "Pair not found" << std::endl;
}

void findPair2(std::vector<int> arr, size_t n, int sum)
{
    std::sort(arr.begin(), arr.end());
    int low = 0;
    int high = n - 1;

    while(low < high)
    {
        if(arr[low] + arr[high] == sum)
        {
            std::cout << "Pair found: (" << arr[low] << " + " << arr[high] << " ) " << std::endl;
            return;
        }
    }
    std::cout << "Pair not found";
}

void findPair3(const std::vector<int>& arr, size_t n, int sum)
{
    std::unordered_set<int> set;
    for(size_t i = 0; i < n; i++)
    {
        std::unordered_set<int>::iterator it = set.find(sum - arr[i]);
        if(it != set.end())
        {
            std::cout << "Pair found " << *it << " + " << arr[i];
            return;
        }
        set.insert(arr[i]);
    }
    std::cout << "Pair not found";
}

int main()
{
    std::vector<int> arr = {8, 7, 2, 5, 9, 3, 1};
    int sum = 11;
    findPair1(arr, arr.size(), sum);
    findPair2(arr, arr.size(), sum);
    findPair3(arr, arr.size(), sum);

    return 0;
}


