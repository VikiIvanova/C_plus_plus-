#include <unordered_map>
#include <map>
#include <unordered_set>
#include <set>
#include <iostream>

int main()
{
    std::map<int, char> myMap = {{2, 'B'}, {6, 'F'}, {3, 'C'}, {1, 'A'}, {5, 'E'}, {4, 'D'}};
    std::set<int> mySet = {2, 6, 3, 1, 5, 4};
    std::unordered_map<int, char> myUnorderedMap = {{2, 'B'}, {6, 'F'}, {3, 'C'}, {1, 'A'}, {5, 'E'}, {4, 'D'}};
    std::unordered_set<int> myUnorderedSet = {2, 6, 3, 1, 5, 4, 2, 1, 8, 4};
 
    for(std::pair<const int, char> it : myMap)
    {
        std::cout << '(' << it.first << ", " << it.second << "), ";
    }
    std::cout << std::endl;
    for(int it : mySet)
    {
        std::cout << it << ' ';
    }
    std::cout << std::endl;
    for(std::pair<const int, char> it : myUnorderedMap)
    {
        std::cout << '(' << it.first << " , " << it.second << "), ";
    }
    std::cout << std::endl;
    for(int it : myUnorderedSet)
    {
        std::cout << it << ' ';
    }
    std::cout << std::endl;
    std::unordered_map<const int, char>::iterator it = myUnorderedMap.find(6);
    if(it != myUnorderedMap.end())
    {
        it->second = 'Y';
    }
    for(std::pair<const int, char> it : myUnorderedMap)
    {
        std::cout << '(' << it.first << ", " << it.second << "), ";
    }
    std::cout << std::endl;

    myUnorderedMap[7];
    myUnorderedMap[7] = 'M';
    for(std::pair<const int, char> it : myUnorderedMap)
    {
        std::cout << '(' << it.first << ", " << it.second << "), ";
    }
    std::cout<<std::endl;

    std::pair<const int, char> p = {8, 'N'};
    myUnorderedMap.insert(p);
    myUnorderedMap.insert( std::make_pair<const int, char>( 9, 'Z' ) );
    for ( std::pair<const int, char> it : myUnorderedMap )
    {
        std::cout << '(' << it.first << ", " << it.second << "), ";
    }
    std::cout << std::endl;

    myUnorderedMap.insert(std::make_pair<const int, char>(9, 'P'));
    for(std::pair<const int, char> it : myUnorderedMap)
    {
        std::cout << '(' << it.first << ", " << it.second << "), ";
    }
    std::cout << std::endl;

    return 0;
}