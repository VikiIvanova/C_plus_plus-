//Намерете всички симетрични двойки в масив от двойки числа

#include <iostream>
#include <unordered_set>
#include <string>

struct Pair
{
    int x, y;
};

std::string constructStringPair(int x, int y)
{
   return "{" + std::to_string(x) + ", " + std::to_string(y) + "}";
}

void findPairs(const std::vector<Pair>& pairs)
{
    //create an empty set of string
    std::unordered_set<std::string> set;
    
    //do for each pair
    for(const Pair& p_iter : pairs)
    {
        //construct a pair(x, y) from pairs[i]
        std::string p = constructStringPair(p_iter.x, p_iter.y);

        //insert current pair into the set
        set.insert(p);

        //construct mirror pair(y, x) of pairs[i]
        std::string reverse_pair = constructStringPair(p_iter.y, p_iter.x);

        //if mirror pair if seen before, print the pairs
        if(set.find(reverse_pair) != set.end())
        {
            std::cout << p << " | " << reverse_pair << '\n';
        }
    }
}

int main()
{
    std::vector<Pair> pairs = {{3, 4}, {1, 2}, {5, 2}, {7, 10}, {4, 3}, {2, 5}};
    findPairs(pairs);

    return 0;
}