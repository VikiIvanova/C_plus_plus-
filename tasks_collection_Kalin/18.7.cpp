/*(*)Да се дефинира функция за намиране на стойността на полинома на
Ермит Hn(x) (x е реална променлива, а n неотрицателна цяла променлива), дефиниран по следния начин:
H0(x) = 1
H1(x) = 2x
Hn(x) = 2xHn−1(x) + 2(n − 1)Hn−2(x), n > 1,
за дадени n и x с използване на стек.*/

#include <iostream>
#include <stack>

double calculateStack(std::stack<double> s)
{
    double result = 0;
    while(!s.empty())
    {
       result += s.top();
       s.pop();
    }   
    return result;
}

double polynomialErmit(int x, unsigned n)
{
    std::stack<double> result;
    if(n == 0)
       result.push(1);
    else if(n == 1)
       result.push(2*x);
    else 
    {
        result.push(2*x*polynomialErmit(x, n-1)+
                         2*(n-1)*polynomialErmit(x, n-2));
    }
    return calculateStack(result);
}

int main()
{
    int x;
    unsigned n;
    std::cout << "Enter x: ";
    std::cin >> x;
    std::cout << "Enter n: ";
    std::cin >> n;

    std::cout << polynomialErmit(x, n) << std::endl;
    
    return 0;
}