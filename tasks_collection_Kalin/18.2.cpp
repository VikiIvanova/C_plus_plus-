/*Даден е израз, който може да съдържа отварящи и затварящи скоби. Да
се напише функция, която проверява дали скобите на израза са правилно
балансирани. Например, изразът (x+(y+(1+2))) считаме за правилно
балансиран, но не и израза (x+y)*3)+(x+(1+2).*/

//не работи

#include <iostream>
#include <stack>

const int MAXEXPR = 100;
/*
void showStack(std::stack<int> s)
{
    while(!s.empty())
    {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << std::endl;
}
bool isDigit(char c)
{
    return c >= 0 && c <= 9;
}

bool isop(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}
*/
bool isOpeningParenthesis(char c)
{
    return c == '(' || c == '[' || c == '{';
}

bool isClosingParenthesis(char c)
{
    return c == ')' || c == ']' || c == '}';
}

bool matchParentheses(char open, char close)
{
    return (open == '(' && close == ')') || 
           (open == '[' && close == ']') || 
           (open == '{' && close == '}');
}

bool checkParentheses(const char* expr)
{
    std::stack<int> s;
    while (*expr != '\0')
    {
        if(isOpeningParenthesis(*expr))
        {
            s.push(*expr);
            
        } 
        else if (isClosingParenthesis(*expr))
        {
            if(s.empty() || !matchParentheses(s.top(), *expr))
               return false;
            else
            //ако е мачнало и стека не ми е празен трябва да премахнем елемента от стека, защото иначе ще върне false
                s.pop();
        }
        expr++;
    }
    return s.empty();
}
int main()
{
    char expr[MAXEXPR];
    std::cin.getline(expr, MAXEXPR);
    
    std::cout << std::boolalpha << checkParentheses(expr) << std::endl;
    
    return 0;
}