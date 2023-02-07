/*Да се напише функция, която генерира всички двоични числа от 1 до n, използвайки опашка.*/
#include <iostream>
#include <queue>
#include <string>

void printAllBinaryNumber(size_t n)
{
    std::queue<std::string> q;

    q.push("1");

    while(n)
    {
        std::string currentNumber = q.front();
        q.pop();

        std::cout << currentNumber << " ";

        q.push(currentNumber + "0");
        q.push(currentNumber + "1");

        n--;
    }
}