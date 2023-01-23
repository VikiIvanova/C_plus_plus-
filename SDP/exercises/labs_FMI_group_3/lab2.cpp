#include <iostream>
#include <vector>
#include <stdexcept>

bool hasValidSize(size_t sizeA, size_t sizeB)
{
   return sizeA == sizeB;
}

std::vector<std::vector<int>> sumMatrix(
    const std::vector<std::vector<int>> &a,
    const std::vector<std::vector<int>> &b)
{
    size_t sizeA = a.size();
    size_t sizeB = b.size();
    if (!hasValidSize(sizeA, sizeB))
    {
        throw std::invalid_argument("Некоректни данни!");
    }

    std::vector<int>::iterator itA;
    std::vector<int>::iterator itB;
    std::vector<std::vector<int>> result;

    /*for (std::vector<std::vector<int>>::const_iterator itA = a.cbegin(), itB = b.cbegin();
         itA != a.cend(); itA++, itB++)
    {
        std::vector<int> row;
        for (std::vector<int>::const_iterator jA = (*itA).cbegin(), jB = (*itB).cbegin();
             jA != (*itA).cend(); jA++, jb++)
        {
            row.push_back(*jA + *jB);
        }
        result.push_back(row);
    }*/
    for (int i = 0; i < sizeA; ++i)
    {
        std::vector<int> row;
        for (int j = 0; j < a[i].size(); ++j)
        {
            row.push_back(a[i][j] + b[i][j]);
        }
        result.push_back(row);
    }
    return result;
}

int main()
{
    std::vector<std::vector<int>> a
    {
        {1, 2},
        {4, 5}
    };
    std::vector<std::vector<int>> b
    {
        {3, 4},
        {7, 8}
    };
    std::vector<std::vector<int>> result = sumMatrix(a, b);
    for(int i = 0; i < result.size(); ++i)
    {
        for(int j = 0; j < result[i].size(); ++j)
        {
            std::cout << result[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}