/*Да се напише функция, която намира сумата на всички елементи на двоично наредено дърво от цели числа, 
които имат нечетен брой наследници в интервала [x, y] 
(т.е. сумата на броя елементи в лявото поддърво и броя елементи в дясното поддърво в интервала [x, y] е нечетно число). 
Нека x и y са параметри на функцията.*/

// #include "tree-utils.h"

// std::pair<int, int> findSumHelper(const Tree<int>* t, int x, int y)
// {
//     if(t == nullptr)
//        return std::make_pair(0, 0);
    
//     std::pair<int, int> l = std::make_pair(0, 0);
//     std::pair<int, int> r = std::make_pair(0, 0);

//     if(t->data >= x)
//        l = findSumHelper(t->left, x, y);
//     if(t->data <= y)
//        r = findSumHelper(t->right, x, y);
    
//     bool oddChildren = ((l.second + r.second) % 2);

//     int sum = l.first + r.first;
//     int count = l.second + r.second + (t->data >= x && t->data <= y);

//     if(oddChildren)
//        sum += t->data;
    
//     return std::make_pair(sum, count);
// }

// int findSum(const Tree<int>* t, int x, int y)
// {
//     return findSumHelper(t, x, y).first;
// }

#include <iostream>

struct Node
{
    int data;
    Node *left, *right;
    Node(int x) : data(x), left(nullptr), right(nullptr) {}
};

int sumOddDescendants(Node *root, int x, int y)
{
    if (!root)
        return 0;

    int sum = 0;
    if (root->data >= x && root->data <= y) {
        int left_count = 0, right_count = 0;
        if (root->left)
            left_count = sumOddDescendants(root->left, x, y);
        if (root->right)
            right_count = sumOddDescendants(root->right, x, y);
        if ((left_count + right_count) % 2 != 0)
            sum = root->data;
    }

    sum += sumOddDescendants(root->left, x, y);
    sum += sumOddDescendants(root->right, x, y);

    return sum;
}


int main()
{
    
}