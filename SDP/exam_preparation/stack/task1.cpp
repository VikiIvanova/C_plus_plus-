/* Задача 1:
Имаме низ състоящ се от английски букви и символа *. Всеки път когато видим * трябва да премахнем символът отляво както и самата звезда. 
Пример:
aa* -> "a"
erase***** -> ""
thi*s i*s exampl*e -> "ths s exampe"
Задачата да се реализира за линейно време с линейна памет.*/

#include <string>
#include <stack>
#include <iostream>

std::string removeStars(const std::string& s)
{
    std::stack<char> st;
    for(int i = 0; i < s.size(); i++)
    {
        if(s[i] == '*')
        {
            if(st.empty())
               throw "invalid expr";
            else
               st.pop();
        }
        else
           st.push(s[i]);
    }
    std::string res(st.size(), '\0');
    size_t idx = st.size() - 1;
    while(!st.empty())
    {
        res[idx--] = st.top();
        st.pop();
    }
    return res;
}
