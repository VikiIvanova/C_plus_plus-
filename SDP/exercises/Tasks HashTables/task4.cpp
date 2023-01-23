/*
: Проверете дали два стринга са изоморфни. Два стринга се наричат изоморфни,
ако всички срещания на един символ от единия стринг можем да ги заменим с друг символ
от втория стринг и така за всички символи, докато не се получи изцяло същия като втория
стринг.
*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

//Find if string X and Y are Isomorphic or not
bool isIsomorphic(std::string X, std::string Y)
{
    //if X and Y have different lengths, they cannot be Isomorphic
    if(X.length() != Y.length())
       return false;
    
    //use set to store mapping from characters of string X to string T
    std::unordered_map<char, char> map;

    //use set to store pool of an alredy mapped characters
    std::unordered_set<char> set;

    for(int i = 0; i < X.length(); ++i)
    {
        char x = X[i], y = Y[i];

        //if x is seen before
        if(map.find(x) != map.end())
        {
            //return false if first occurence of x is mapped to
            //different character
            if(map[x] != y)
               return false;
        }

        //if x is seen for the first time(i.e. it is not mapped yet)
        else
        {
            //return false if y is already mapped to some other char in X
            if(set.find(y) != set.end())
               return false;

            //map y to x and mark it mapped
            map[x] = y;
            set.insert(y);
        }
    }
    return true;
}

int main()
{
    std::string X = "ACAB";
    std::string Y = "XCXY";

    if(isIsomorphic(X, Y))
       std::cout << X << " and " << Y << " are Isomorphic";
    else
       std::cout << X << " and " << Y << " are not Isomorphic";

    return 0;
}