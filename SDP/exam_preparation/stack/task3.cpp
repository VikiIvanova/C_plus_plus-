/*Обратен полски запис наричаме запис, в който операторите "следват" (са след) числата. 
Примерно изразът 3 + 4 в обратна полска нотация е 3 4 +. Или изразът 1−2+3 би изглеждал 1 2 −3+. 
Обикновено първо са дадени числата а след това операциите които извършваме върху тях.
А как би изглеждал израза 1−(2+3). Тук първо трябва да извършим събирането и след това изваждането. 
Тоест израза се записва като 123+−. Предимството от тази нотация е, че нямаме нужда от скоби, 
което ускорява сметките. Нашата задача е да напишем функция, 
която приема валиден стринг в обратна полска нотация и връща пресметнатия резултат.*/

#include <iostream>
#include <stack>
#include <string>
#include <cassert>

bool isOperation(char c)
{
    return (c == '+') || (c == '-') || (c == '*') || (c == '/');
}

bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}

int eval(int fst, int snd, char op)
{
    assert(isOperation(op));

    switch (op)
    {
    case '+':
        return fst + snd;
    case '-':
        return fst - snd;
    case '*':
        return fst * snd;
    case '/':
        return fst / snd;
    }
}

int RPN(const std::string& str)
{
    std::stack<int> numbers;
    for(size_t i = 0; i < str.size(); ++i)
    {
        if(isOperation(str[i]))
        {
            int snd = numbers.top();
            numbers.pop();

            int fst = numbers.top();
            numbers.pop();

            numbers.push(eval(fst, snd, str[i]));
        }
        else if(str[i] != ' ')
        {
            int number = 0;
            while(i < str.size() && isDigit(str[i]))
            {
                number *= 10;
                number += str[i] - '0';
                i++;
            }
            i--;
            numbers.push(number);
        }
    }
    return numbers.top();
}