#include <iostream>
/* Задача първа:
Даден е списък l с n елемента.
Да се дефинира функция shuffle(), която получава адреса на първия елемент на списъка.
Функцията да пренарежда възлите на списъка така, че елементите от втората половина на
списъка да се преместят в началото на списъка, но в обратен ред
(при списъци с нечетен брой елементи считаме средния елемент за принадлежащ към първата половина на списъка).
Пример:
Вход: L1 → L2 → L3 → L4 → L5
Изход: L5 → L4 → L1 → L2 → L3*/

struct LinkedListNode
{
    int data;
    LinkedListNode *next;
    LinkedListNode(int x, LinkedListNode *next = nullptr) : data(x), next(next) {}
};

void printList(LinkedListNode *list)
{
    LinkedListNode *temp = list;
    while (temp)
    {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

void pushFront(LinkedListNode *&result, int num)
{
    if (result == nullptr)
    {
        result = new LinkedListNode{num, nullptr};
    }
    else
    {
        LinkedListNode* newNode = new LinkedListNode{num, result};
        result = newNode;
    }
}

void insertAfter(LinkedListNode*& currEndResult, int num)
{
    if(currEndResult == nullptr)
    {
        currEndResult = new LinkedListNode{num, nullptr};
    }
    else
    {
        LinkedListNode* newNode = new LinkedListNode{num, currEndResult->next};
        currEndResult->next = newNode;
        currEndResult = newNode;
    }
}

void reverseList(LinkedListNode *&list)
{
    LinkedListNode *previous = nullptr;
    LinkedListNode *current = nullptr;
    LinkedListNode *temp = list;

    while (temp->next)
    {
        current = temp->next;
        temp->next = previous;
        previous = temp;
        temp = current;
    }
    list = previous;
}

LinkedListNode *shuffle(LinkedListNode *list)
{
    LinkedListNode *result = nullptr;
    LinkedListNode* current = list;
    size_t sizeList = 0;
    LinkedListNode* currEndResult = nullptr;
    while(list)
    {
       sizeList++;
       list = list->next;
    }

    insertAfter(currEndResult, current->data);
    current = current->next;
    result = currEndResult;
    size_t counter = 1;
    if(sizeList % 2 == 0)
    {
        while(counter < sizeList / 2)
        {
            insertAfter(currEndResult, current->data);
            current = current->next;
            counter++;
        }
    }
    else
    {
        while(counter < sizeList / 2 + 1)
        {
            insertAfter(currEndResult, current->data);
            current = current->next;
            counter++;
        }
    }
    while(current)
    {
        pushFront(result, current->data);
        current = current->next;
    }
    list = result;

    return list;
}

/* Задача втора:
Даден е списък l с елементи стекове.
Да се дефинира функция equalize(l), която размества елементите на стековете така,
че да няма два стека в l с разлика в броя на елементите, по-голяма от 1.
Вход                          Изход
5 -> 4 -> 3 -> 2 -> 1         5 -> 4 -> 3
|                             |
v                             v
7 -> 6                        7 -> 6 -> 1
|                             |
v                             v
11 -> 10 -> 9 -> 8            11 -> 10 -> 9
|                             |
v                             v
12                            12 -> 2 -> 8
*/
#include <stack>
#include <queue>

template<typename T>
struct listWithStackNode
{
    T data;
    listWithStackNode<T>* next = nullptr;
};

size_t allElementInList(listWithStackNode<std::stack<int>>* list)
{
    size_t count = 0;
    while(list)
    {
        count += list->data.size();
        list = list->next;
    }
    return count;
}

size_t countNodeinList(listWithStackNode<std::stack<int>>* list)
{
    size_t count = 0;
    while(list)
    {
        count++;
        list = list->next;
    }
    return count;
}

listWithStackNode<std::stack<int>>* equalize(listWithStackNode<std::stack<int>>* list)
{
    listWithStackNode<std::stack<int>>* current = list;
    size_t countAllElementInList = allElementInList(list);
    size_t countNode = countNodeinList(list);
    size_t maxElementInStack = countAllElementInList / countNode;

    std::queue<int> temp;

    while(current)
    {
        while(current->data.size() != maxElementInStack)
        {
            while(current->data.size() > maxElementInStack)
            {
                temp.push(current->data.top());
                current->data.pop();
            }
            while (!temp.empty() && current->data.size() < maxElementInStack)
            {
                current->data.push(temp.front());
                temp.pop();
            }
            
        }
        current = current->next;
    }
    return list;
}


void printList(listWithStackNode<std::stack<int>>* list)
{
    listWithStackNode<std::stack<int>>* temp = list;
    while(temp)
    {
        std::stack<int> current;
        while(!temp->data.empty())
        {
          current.push(temp->data.top());
          temp->data.pop();
        }
        while(!current.empty())
        {
            std::cout << current.top() << " ";
            current.pop();
        }
        temp = temp->next;
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

/* Задача трета - Linked List Partition
Да се създаде функция
LinkedListNode<int>* partition(LinkedListNode<int>* head, int x);
която пренарежда списъка така, че всички възли със стойност по-малка от х са преди
всички възли със стойност по-голяма или равна от х.
Пример:
Вход: head -> 1 -> 4 -> 3 -> 2 -> 5 -> 2, x = 3
Изход: 1 -> 2 -> 2 -> 4 -> 3 -> 5

Вход: head -> 2 -> 1, x = 2
Изход: 1 -> 2
HINT:
Можете да си направите два указателя, чрез които да строите някакви полезни помощни списъци.
После, след като построите тези полезни помощни списъци,
можете да пренасочите правилните указатели и да получите коректен отговор.*/

void print(LinkedListNode* list)
{
    LinkedListNode* temp = list;
    while(temp)
    {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

LinkedListNode *partition(LinkedListNode *head, int x) {
  LinkedListNode *beforeStart = nullptr;
  LinkedListNode *beforeEnd = nullptr;
  LinkedListNode *afterStart = nullptr;
  LinkedListNode *afterEnd = nullptr;

  // Partition list
  while (head != nullptr) {
    LinkedListNode *next = head->next;
    head->next = nullptr;
    if (head->data < x) {
      if (beforeStart == nullptr) {
        beforeStart = head;
        beforeEnd = beforeStart;
      } else {
        beforeEnd->next = head;
        beforeEnd = head;
      }
    } else {
      if (afterStart == nullptr) {
        afterStart = head;
        afterEnd = afterStart;
      } else {
        afterEnd->next = head;
        afterEnd = head;
      }
    }
    head = next;
  }

  if (beforeStart == nullptr) {
    return afterStart;
  }

  beforeEnd->next = afterStart;
  return beforeStart;
}



int main()
{
    std::stack<int> s1;
    s1.push(5);
    s1.push(4);
    s1.push(3);
    s1.push(2);
    s1.push(1);

    std::stack<int> s2;
    s2.push(7);
    s2.push(6);

    std::stack<int> s3;
    s3.push(11);
    s3.push(10);
    s3.push(9);
    s3.push(8);
  
    std::stack<int> s4;
    s4.push(12);

    listWithStackNode<std::stack<int>>* list = new listWithStackNode<std::stack<int>>{s1,
                        new listWithStackNode<std::stack<int>>{s2, 
                         new listWithStackNode<std::stack<int>>{s3, 
                         new listWithStackNode<std::stack<int>>{s4, nullptr 
                         }}}};
                         
    printList(equalize(list));

    LinkedListNode* l1 = new LinkedListNode(1, new LinkedListNode(4, new LinkedListNode(3, new LinkedListNode(2, new LinkedListNode(5, new LinkedListNode(2))))));
    LinkedListNode* result = partition(l1, 3);
    print(result);


    return 0;
}
