/*Вход: Низ състоящ се от отварящи и затварящи скоби.
Изход: Дали скобите в този низ са балансирани
Примери:
((())) -> true
))() -> false
)( -> false
()()(()) -> true*/

#include <iostream>
#include <stack>
#include <string>

bool isStringBalanced(const std::string& str)
{
    std::stack<char> s;
    for(size_t i = 0; i < str.size(); ++i)
    {
        if(str[i] == ')')
        {
            if(s.empty())
               return false;
            s.pop();
        }
        else
        {
            s.push(str[i]);
        }
    }
    return s.empty();
}