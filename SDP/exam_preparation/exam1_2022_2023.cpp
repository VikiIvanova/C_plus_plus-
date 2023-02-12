/*Задача 1.
Нека е даден едносвързан списък. Всеки затворен интервал от валидни 0-базирани индекси [i, j] 
представя еднозначно негов подсписък, състоящ се от последователните елементи с индекси k ∈ [i, j]. 
Да се реализира шаблон на функция reverseSublists(<тип> list, <тип> intervals), 
която приема указател към първи елемент на едносвързан списък list с елементи от тип Т 
и указател към първи елемент на едносвързан списък intervals с елементи от подходящ тип, 
представящ затворен интервал от 0-базирани индекси, и модифицира списъка list като последователно обръща 
огледално реда на елементите във всеки от подсписъците, представени чрез интервалите в intervals. 
Ако някой интервал съдържа невалидни индекси в list, да се хвърли подходящо изключение (exception).

Пример:

intervals                   [1, 3] → [2, 5] → [5, 6] 
list                        11 → 4 → 3 → 7 → 13 → 4 → 5 
след обръщане на [1, 3]     11 → 7 → 3 → 4 → 13 → 4 → 5 
след обръщане на [2, 5]     11 → 7 → 4 → 13 → 4 → 3 → 5 
след обръщане на [5, 6]     11 → 7 → 4 → 13 → 4 → 5 → 3 */

#include <vector>
#include <iostream>
#include <exception>

template <typename T>
struct Node
{
    T value;
    Node<T> *next;
    Node(T value, Node *next = nullptr) : value(value), next(next){};
};

//моите не работещи глупости
// template <typename T>
// void reverseList(Node<T> *&list, size_t size)
// {
//     Node<T> *current = list;
//     Node<T> *temp = nullptr;
//     Node<T> *prev = nullptr;
//     while (current && size > 0)
//     {
//         temp = current->next;
//         current->next = prev;
//         prev = current;
//         current = temp;
//         --size;
//     }
//     list = prev;
    
// }

// template <typename T>
// void reverseSublists(Node<T> *&list, Node<T> *intervals)
// {
//     Node<T> *tempIntervals = intervals;
//     size_t sizeInterval = tempIntervals->value;
//     while (tempIntervals->next)
//     {
//         tempIntervals = tempIntervals->next;
//     }
//     sizeInterval = tempIntervals->value - sizeInterval + 1;

//     Node<T> *startTransform = list;
//     int counter = intervals->value;
//     while (startTransform && counter > 0)
//     {
//         startTransform = startTransform->next;
//         counter--;
//     }
//     reverseList(startTransform, sizeInterval);
//     Node<T> *newList = list;
//     int counterNewList = intervals->value - 1;
//     while (newList && counterNewList > 0)
//     {
//         newList = newList->next;
//     }
//     newList->next = startTransform;

//     printList(list);
// }
template<typename T>
int getLen(Node<T>* list)
{
    int result = 0;
    while(list)
    {
        result++;
        list = list->next;
    }
    return result;
}

template<typename T>
Node<T>* reverse(Node<T>* head, int from, int to)
{
    Node<T> dummyHead(0, head), *prev = &dummyHead, *curr = head, *start, *startPrev, *next;
    for(size_t i = 0; i < from; i++)
    {
        prev = curr;
        curr = curr->next;
    }
    start = curr;
    startPrev = prev;
    for(size_t i = 0; i < to - from + 1; i++)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    start->next = curr;
    startPrev->next = prev;
    return dummyHead.next;
}

template<typename T>
Node<T>* reverseSublists(Node<T>* head, Node<std::pair<int, int>>* intervals)
{
    int len = getLen(head);
    Node<std::pair<int, int>>* intervalsIter = intervals;
    while(intervalsIter)
    {
        auto &&[i, j] = intervalsIter->value;
        if(i > j || i >= len || i < 0 || j < 0)
        {
            throw std::length_error("Index out of bounds.");
        }
        intervalsIter = intervalsIter->next;
    }
    while(intervals)
    {
        auto &&[i, j] = intervals->value;
        head = reverse(head, i, j);
        intervals = intervals->next;
    }
    return head;
}
template <typename T>
void printList(Node<T> *list)
{
    while (list)
    {
        std::cout << list->value << " ";
        list = list->next;
    }
    std::cout << std::endl;
}

template<typename T>
void deleteList(Node<T>* head)
{
    while(head)
    {
        Node<T>* del = head;
        head = head->next;
        delete del;
    }
}

// int main()
// {
//     Node<int> *list = new Node<int>(11, new Node<int>(4, new Node<int>(3, new Node<int>(7, new Node<int>(13, new Node<int>(4, new Node<int>(5)))))));
//     Node<std::pair<int, int>>* intervals = new Node<std::pair<int, int>>({1, 3}, new Node<std::pair<int, int>>({2, 5}, new Node<std::pair<int, int>>({5, 6})));
//     printList(list);

//     list = reverseSublists(list, intervals);
//     printList(list);

//     deleteList(list);
//     deleteList(intervals);
// }

/*Списък от цели числа се нарича изцяло балансиран, ако се състои от поне 3 елемента и 
всички елементи без първия и последния са равни на сбора от съседните си два елемента и изцяло небалансиран, 
ако в него няма нито един такъв елемент. Да се реализира функция makeTotal, която приема като параметър указател 
към първия елемент на едносвързан списък от цели числа и връща true, ако списъкът е изцяло балансиран. 
Ако списъкът не е изцяло балансиран, функцията да връща false след като изтрие последователно от списъка от началото 
към края елементи, които изпълняват свойството за балансираност, докато списъкът стане изцяло небалансиран.
За реализацията НЕ се допуска използването на допълнителни помощни структури от данни 
(т.е. външната (auxiliary) сложност по памет е O(1)). 
Примери:
1) 1 → -4 → -5 → -1 → 4      true 
2) 10 → 5 → -5 → -15 → 2     false // -> delete 5
10 → -5 → -15 → 2                  // -> delete -5 
10 → -15 → 2 
(списъкът вече е изцяло небалансиран)*/

// използваме наготово някои функции от предишната задача

template<typename T>
void balance(Node<T>* head)
{
    Node<T>* prev = head, *curr = head->next;
    if(!head || !head->next || !head->next->next)
       return;
    
    while(curr->next)
    {
        if(prev->value + curr->next->value == curr->value)
        {
            Node<T>* del = curr;
            curr = curr->next;
            prev->next = curr;
            delete del;
            continue;
        }
        prev = curr;
        curr = curr->next;
    }
}

template<typename T>
bool makeTotal(Node<T>* head)
{
    Node<T>* prev = head, *curr = head->next;
    while(curr->next)
    {
        if(prev->value + curr->next->value != curr->value)
        {
            balance(head);
            return false;
        }
        prev = curr;
        curr = curr->next;
    }
    return true;
}

// int main()
// {
//     Node<int> *head = new Node<int>(1, new Node<int>(-4, new Node<int>(-5, new Node<int>(-1, new Node<int>(4)))));
//     printList(head);
//     std::cout << std::boolalpha << makeTotal(head) << '\n';
//     printList(head);

//     Node<int> *head1 = new Node<int>(10, new Node<int>(5, new Node<int>(-5, new Node<int>(-15, new Node<int>(2)))));
//     printList(head1);
//     std::cout << std::boolalpha << makeTotal(head1) << '\n';
//     printList(head1);

//     deleteList(head);
//     deleteList(head1);
// }

/*Казваме, че дадена дума може да се прочете в стек от символи, ако можем да я получим 
при последователно изваждане на символи от стека като избирателно пропуснем някои от тях. 
Да се реализира функция readAndDelete, която по подаден стек от символи, 
представен чрез std::stack и дума (word) от тип std::string, връща като резултат дали 
думата може да се прочете в стека. Функцията да модифицира стека като изключи от него всички 
открити символи от word и да запазва останалите символи в същия ред.*/

#include <stack>
#include <string>
#include <cassert>

bool readAndDelete(std::stack<char>& stack, const std::string& str)
{
    int i = 0; 
    std::stack<char> store;
    while(!stack.empty())
    {
        if(str[i] == stack.top())
        {
            i++;
        }
        else
        {
            store.push(stack.top());
        }
        stack.pop();
    }
    while(!store.empty())
    {
        stack.push(store.top());
        store.pop();
    }
    return i == str.length();
}

template<typename T>
void print(std::stack<T> s)
{
    while(!s.empty())
    {
        std::cout << s.top();
        s.pop();
    }
    std::cout << "\n";
}

void test1()
{
    std::stack<char> stack;
    stack.push('m');
    stack.push('o');
    stack.push('o');
    stack.push('f');
    stack.push('m');
    std::string string = "mom";
    assert(readAndDelete(stack, string));
    print(stack);
}

void test2()
{
    std::stack<char> stack;
    stack.push('y');
    stack.push('a');
    stack.push('d');
    stack.push('c');
    stack.push('c');
    std::string string = "car";
    assert(!readAndDelete(stack, string));
    print(stack);
}

int main()
{
    test1();
    test2();
}