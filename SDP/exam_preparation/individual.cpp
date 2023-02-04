/*Да се дефинира подходящ шаблон на структура Node<T>,
описваща елемент от едносвързан списък с елементи от тип T.
Да се реализира функция reverseFib, която по указател към началото на списък L
с елементи от тип T, проверява дали за списъка е изпълнено условието на Фибоначи,
т.е. за всеки три последователни елемента на списъка е вярно,
че сборът на първите два елемента е равен на третия елемент
(допускаме, че за типа T са дефинирани операции за събиране и проверка за равенство).
Ако това условие е изпълнено, функцията reverseFib да връща като резултат указател
към първия елемент на нов списък, създаден в динамичната памет, който съдържа елементите на L,
но в обратен ред. Ако условието не е изпълнено, функцията reverseFib да връща празен списък.
Да се реализира примерна програма, която демонстрира работата на функцията reverseFib
като инициализира списък с поне 10 елемента и я прилага над него.
Да се дефинират подходящи помощни функции за построяването на примерния списък.
За тази задача не се изисква освобождаване на заделената от примерната програма динамична памет.*/

#include <iostream>

template <typename T>
struct Node
{
    T data;
    Node<T> *next;
    Node(): data(T()), next(nullptr){};
};

template <typename T>
bool checkIsFibSeq(Node<T> *&list)
{
    Node<T> *prev = list;
    Node<T> *current = list->next;
    while (current->next)
    {
        if (prev->data + current->data == current->next->data)
        {
            prev = prev->next;
            current = current->next;
        }
        else
        {
            return false;
        }
    }
    return true;
}

template <typename T>
Node<T>* reverseFib(Node<T> *&list)
{
    if (checkIsFibSeq(list))
    {
        Node<T> *next = nullptr;
        Node<T> *prev = nullptr;
        Node<T> *current = list;
        while(current != nullptr)
        {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        list = prev;
        return list;
    }
    return nullptr;
}

template<typename T>
void printList(Node<T>* list)
{
    while(list)
    {
        std::cout << list->data << ' ';
        list = list->next;
    }
    std::cout << std::endl;
}

template<typename T>
void append(Node<T>* &list, T element)  
{  
    
    Node<T>* newNode = new Node<T>(); 
    Node<T> *last = list; 
    
    newNode->data = element;  
    newNode->next = nullptr;  
    if (list == nullptr)  
    {  
        list = newNode;  
        return;  
    }  
    while (last->next != nullptr)
    {
        last = last->next;  
    }
    
    last->next = newNode;  
}  

int main()
{
    Node<int>* reverseList = nullptr;
    append(reverseList, 1);
    append(reverseList, 2);
    append(reverseList, 3);
    append(reverseList, 5);

    printList(reverseList);

    if(reverseFib(reverseList))
    {
        printList(reverseList);
    }
    else
    {
       std::cout << "The Fibonacci rule is not satisfied" << std::endl;
    }

    return 0;
}
 