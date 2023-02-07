/*Да се напише функция, която намира сумата на всички елементи на двоично наредено дърво от цели числа, 
които имат нечетен брой наследници в интервала [x, y] 
(т.е. сумата на броя елементи в лявото поддърво и броя елементи в дясното поддърво в интервала [x, y] е нечетно число). 
Нека x и y са параметри на функцията.*/

#include "tree-utils.h"

std::pair<int, int> findSumHelper(const Tree<int>* t, int x, int y)
{
    if(t == nullptr)
       return std::make_pair(0, 0);
    
    std::pair<int, int> l = std::make_pair(0, 0);
    std::pair<int, int> r = std::make_pair(0, 0);

    if(t->data >= x)
       l = findSumHelper(t->left, x, y);
    if(t->data <= y)
       r = findSumHelper(t->right, x, y);
    
    bool oddChildren = ((l.second + r.second) % 2);

    int sum = l.first + r.first;
    int count = l.second + r.second + (t->data >= x && t->data <= y);

    if(oddChildren)
       sum += t->data;
    
    return std::make_pair(sum, count);
}

int findSum(const Tree<int>* t, int x, int y)
{
    return findSumHelper(t, x, y).first;
}

int main()
{
    
}