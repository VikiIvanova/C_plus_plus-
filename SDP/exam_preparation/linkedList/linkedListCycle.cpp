#include <iostream>
//Да се напише функция, която проверява дали в едносвързан списък има цикъл.

struct LinkedListNode
{
    int data;
    LinkedListNode *next;
    LinkedListNode(int x, LinkedListNode *next = nullptr) : data(x), next(next) {}
};

bool hasCycle(LinkedListNode* head)
{
    LinkedListNode* fast = head;
    LinkedListNode* slow = head;

    while(fast && fast->next && slow)
    {
        fast = (fast->next)->next;;
        slow = slow->next;

        if(fast == slow)
           return true;
    }

    return false;
}

int main()
{
    LinkedListNode* last = new LinkedListNode(6);
    LinkedListNode* list = new LinkedListNode(1, new LinkedListNode(2, new LinkedListNode(3, new LinkedListNode(4, new LinkedListNode(5, last)))));

    last->next = list->next->next;

    std::cout << std::boolalpha << hasCycle(list) << std::endl;

    return 0;
}