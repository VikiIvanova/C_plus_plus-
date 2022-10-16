/*18.1. Нека е даден масив с n елемента. За всеки от елементите на масива да
се изведе следващия в масива по-голям елемент. Т.е. за всеки елемент
a[i] да се отпечата a[j] такъв, че n > j > i и ∀k ∈ (i, j) : a[k] ≤ a[i].
Ако такъв елемент няма, да се изведе числото −1. Пример, за масива
{4, 5, 2, 25}, да се изведат двойките (4,5), (5,25), (2,25), (25,-1).
Алгоритъмът да работи с линейна сложност спрямо n. Упътване: Задачата е известна под името “Next Greater Element(NGE)”.
*/

#include <iostream>
#include<stack>
static const int MAXARRAY = 100;

void nextGreaterElement(int array[], size_t n)
{
    std::stack<int> s;
    int result[MAXARRAY];
    s.push(array[0]);
    for(int i = 1; i < n; ++i)
    {
        if(s.empty())
        {
            s.push(array[i]);
            continue;
        }
        while(!s.empty() && s.top() < array[i])
        {
            std::cout << s.top() << " -> " << array[i] << std::endl;
            s.pop();
        }
        s.push(array[i]);
    }
    while(!s.empty())
    {
        std::cout << s.top() << " -> " << -1 << std::endl;
        s.pop();
    }
}
int main()
{
    size_t n;
    std::cout << "Enter n: ";
    std::cin >> n;
    int array[MAXARRAY];
    for(int i = 0; i < n; ++i)
    {
        std::cin >> array[i];
    }
    nextGreaterElement(array, n);

    return 0;
}