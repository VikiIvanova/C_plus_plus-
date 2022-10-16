#include <iostream>
#include <cassert>
#include "stack.h"
#include "rstack.h"
#include "lstack.h"
#include "abstract_stack.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "test/lstack_test.h"

//using Stack = ResizingStack;
//using Stack = LinkedStack<int>;

void convertBase()
{
    unsigned n;
    std::cout << "n = ";
    std::cin >> n;

    unsigned base;
    do 
    {
        std::cout << "base = ";
        std::cin >> base;
    } while(base < 2 || base > 10);

    Stack s;
    unsigned k = n;
    while (k > 0)
    {
        s.push(k % base);
        k /= base;
    }

    std::cout << n << "(10) = ";
    while (!s.empty())
       std::cout << s.pop();
    std::cout << "(" << base << ")" << std::endl;
}

bool isDigit(char c)
{
    return '0' <= c && c <= '9';
}

bool isop(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int calculate(int left, char op, int right)
{
    switch(op)
    {
        case '+' : return left + right;
        case '-' : return left - right;
        case '*' : return left * right;
        case '/' : return right == 0 ? 0 : left / right;
        default : assert(isop(op)); return 0;
    }
}

int calculateExpression(char const* expr)
{
    LinkedStack<int> result;
    LinkedStack<char> ops;
    while(*expr)
    {
        if(isDigit(*expr))
           result.push(*expr - '0');
        else if (isop(*expr))
           ops.push(*expr);
        else if (*expr == ')')
        {
            int right = results.pop();
            int left = results.pop();
            char op = ops.pop();
            result.push(calculate(left, op, right));
        }
        expr++;
    }
    return results.pop();
}

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
    return open == '(' && close == ')' || 
           open == '[' && close == ']' || 
           open == '{' && close == '}';
}

void testExpression()
{
    const int MAXEXPR = 100;
    char expr[MAXEXPR];
    std::cin.getline(expr, MAXEXPR);
    std::cout << " = " <<calculateExpression(expr) << std::endl;
}

bool checkParentheses(const char* expr)
{
    Stack s;
    while (*expr != '\0')
    {
        if(isOpeningParenthesis(*expr))
           s.push(*expr);
        else if (isClosingParenthesis(*expr))
        {   if(s.empty() || !matchParentheses(s.pop(), *expr))
              //грешка тип 2: затваряща скоба без отваряща
              // грешка тип 3: несъвпадащи по вид скоби
              return false;
        }
    expr++;
    }
    //грешка тип 1: повече отварящи скоби
    return s.empty();
}
void autoTestParentheses() {
    assert(true  == checkParentheses("((2+3)*(5-7))"));
    assert(true  == checkParentheses("[(2+3)*{5-7}]"));
    // тест за грешка тип 1
    assert(false == checkParentheses("((2+3)+(5-7)"));
    // тест за грешка тип 2
    assert(false == checkParentheses("((2+3)))*((5-7)"));
    // тест за грешка тип 3
    assert(false == checkParentheses("[(2+3)*{5-7)]"));
    // тест за голям израз (100 скоби)
    assert(true == checkParentheses("((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((2))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))"));
    // тест за голям израз (101 скоби)
    assert(true == checkParentheses("(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((2)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))"));
    std::cout << "OK" << std::endl;
}

void testCopyStack()
{
    Stack s1;
    for(int i = 1; i <= 10; ++i)
        s1.push(i);
    Stack s2;
    s2 = s1;
    s2 = s2;
    std::cout << s2.pop() << std::endl;
    s2.push(20);
    std::cout << s1.peek() << std::endl;
    std::cout << s2.pop() << std::endl;
    std::cout << s1.pop() << std::endl;
    std::cout << s1.pop() << std::endl;
}
/*
void testDestroyStack()
{
    for(int i = 0; i < 1E8; ++i)
    {
        //ResizingStack s;
        LinkedStack<int> s;
        for(int j = 1; j <= 10; ++j)
           s.push(j);
    }
    std::cout << "Готово!\n";
    char x;
    std::cin >> x;
}*/

void testAbstractStack()
{
    AbstractStack<int>* stack[] = {
        new Stack,
        new ResizingStack,
        new LinkedStack<int>
    };
    size_t count = sizeof(stacks) / sizeof(stacks[0]);
    for(int i = 0; i < count; ++i)
       for(int x = 1; x <= 10; ++x)
           stacks[i] -> push(x);
    for(int i = 0; i < count; ++i)
        while(!stacks[i] -> empty())
            std::cout << stacks[i] ->pop() << std::endl;
    for(int i = 0; i < count; ++i)
        delete stacks[i];
}

int main(int, char**)
{
    convertBase();
    testExpression();
    autoTestParentheses();
    testCopyStack();
    testDestroyStack();
    testAbstractStack();
}