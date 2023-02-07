#include <iostream>
struct LinkedListNode
{
    int data;
    LinkedListNode *next;
    LinkedListNode(int x, LinkedListNode *next = nullptr) : data(x), next(next) {}
};

bool isLinkedListPalRec(const LinkedListNode* begin, const LinkedListNode* end)
{
    if(end == nullptr)
       return;
    
    bool res = isLinkedListPalRec(begin, end->next) && (begin->data == end->data);
    begin = begin->next;

    return res;
}

bool isLinkedListPal(const LinkedListNode* l1)
{
    if(l1 == nullptr)
      return true;
    
    const LinkedListNode* begin = l1;
    const LinkedListNode* end = l1;

    return isLinkedListPalRec(begin, end);
}

int main()
{
    LinkedListNode* ll = new LinkedListNode(0, new LinkedListNode(1, new LinkedListNode(1)));

    std::cout << isLinkedListPal(ll);
}