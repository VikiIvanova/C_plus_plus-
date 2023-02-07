#include <iostream>
#include <deque>

template <class T>
struct LinkedListNode
{
    T data;
    LinkedListNode<T> *next;

    LinkedListNode(const T &elem, LinkedListNode<T> *n = nullptr) : data{elem}, next{n} {}
};

template <typename T>
void printLinkedList(const LinkedListNode<T> *l1)
{
    const LinkedListNode<T> *iterate = l1;

    while (iterate)
    {
        std::cout << iterate->data << " ";
        iterate = iterate->next;
    }
    std::cout << std::endl;
}

template <typename T>
void freeList(LinkedListNode<T> *l1)
{
    while (l1)
    {
        LinkedListNode<T> *toDelete = l1;
        l1 = l1->next;
        delete toDelete;
    }
}

/*Да се напише функция, която добавя елемент в началото на едносвързан списък*/
template <class T>
void insertAtBegin(LinkedListNode<T> *&l1, const T &elem)
{
    LinkedListNode<T> *toInsert = new LinkedListNode<T>{elem, l1};
    l1 = toInsert;
}

// Да се напише функция, която обръща едносвързан списък.
template <class T>
void reverseLinkedList(LinkedListNode<T> *&l1)
{
    LinkedListNode<T> *previous = nullptr;
    LinkedListNode<T> *next = nullptr;
    LinkedListNode<T> *iterate = l1;

    while (iterate)
    {
        next = iterate->next;
        iterate->next = previous;
        previous = iterate;
        iterate = next;
    }
    l1 = previous;
}

// Да се напише функция, която открива средата на свързан списък.
template <typename T>
LinkedListNode<T> *findMiddle(LinkedListNode<T> *l1)
{
    LinkedListNode<T> *fast = l1;
    LinkedListNode<T> *slow = l1;

    while (fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}
/* да се напише функция която пренарежда свързания списък по следния начин:
LL = 1 -> 2 -> 3 -> 4 -> 5
reorder(LL);
LL = 1 -> 5 -> 2 -> 4 -> 3 */
void reorderWithDeque(LinkedListNode<int> *head)
{
    if (!head || !head->next)
        return;

    std::deque<LinkedListNode<int> *> dq;

    LinkedListNode<int> *it = head;

    while (it)
    {
        dq.push_back(it);
        it = it->next;
    }

    // Винаги пазим края на вече готовия списък
    LinkedListNode<int> *backOfNewList = nullptr;

    while (!dq.empty())
    {
        // Ако размерът е 1 то имаме нечетен брой елементи и просто добавяме последния в края
        if (dq.size() == 1)
        {
            backOfNewList->next = dq.front();
            backOfNewList = backOfNewList->next;
            break;
        }

        // Първият елемент останал в дека започва да сочи към последния
        // Генерираме коректна двойка
        dq.front()->next = dq.back();

        // Ако края на списъка не е nullptr следващите два елемнта
        // в списъка са dq.front()->dq.front()->next (което dq.back())
        if (backOfNewList)
            backOfNewList->next = dq.front(); // Сложи следващите два елемента накрая.

        backOfNewList = dq.front()->next; // Вече края на списъка е друг. Преместваме се там

        dq.pop_back();
        dq.pop_front();
    }

    // next на последния елемент от списъка е nullptr
    backOfNewList->next = nullptr;
}

void reorderWithTwoPointers(LinkedListNode<int> *l1)
{
    if (!l1 || !l1->next)
        return;
    LinkedListNode<int> *mid = findMiddle(l1);
    reverseLinkedList(mid);

    LinkedListNode<int> *firstHalf = l1;
    LinkedListNode<int> *currentPair = nullptr;
    LinkedListNode<int> *backOfList = nullptr;

    while (mid)
    {
        currentPair = firstHalf;
        firstHalf = firstHalf->next;

        // Случая в който имаме нечетен брой елементи
        if (!firstHalf)
        {
            backOfList->next = currentPair;
            backOfList = backOfList->next;
            break;
        }

        currentPair->next = mid;
        mid = mid->next;
        if (backOfList)
            backOfList->next = currentPair; // Пренасочи края към конкретната двойка. Ако е nullptr нямаме какво да пренасочвме.

        backOfList = currentPair->next; // И един бърз ъпдейт на края - вече края на конкретния лист е стария лист + новата двойка
    }
    backOfList->next = nullptr;
}

int main()
{
    LinkedListNode<int> *ll = new LinkedListNode<int>(1, new LinkedListNode<int>(2, new LinkedListNode<int>(3)));
    printLinkedList(ll);
    insertAtBegin(ll, 0);
    printLinkedList(ll);
    reverseLinkedList(ll);
    printLinkedList(ll);
    freeList(ll);

    LinkedListNode<int> *ll2 = new LinkedListNode<int>(1, new LinkedListNode<int>(2, new LinkedListNode<int>(3, new LinkedListNode<int>(4))));
    LinkedListNode<int> *lls = new LinkedListNode<int>(1, new LinkedListNode<int>(2, new LinkedListNode<int>(3, new LinkedListNode<int>(4, new LinkedListNode<int>(5)))));
    LinkedListNode<int> *firstMiddle = findMiddle(ll2);
    LinkedListNode<int> *secondMiddle = findMiddle(lls);
    std::cout << firstMiddle->data << " " << secondMiddle->data;
    freeList(ll2);
    freeList(lls);

    std::cout << std::endl;
    LinkedListNode<int> *l3 = new LinkedListNode<int>(1, new LinkedListNode<int>(2, new LinkedListNode<int>(3, new LinkedListNode<int>(4, new LinkedListNode<int>(5)))));

    reorderWithTwoPointers(l3);
    printLinkedList(l3);
    freeList(l3);

    return 0;
}
