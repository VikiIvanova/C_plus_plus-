// https://www.geeksforgeeks.org/quicksort-on-singly-linked-list/
// quick sort
#include <iostream>

struct node
{
    int data;
    node *next;
};

void push(node **head, int newData)
{
    node *newNode = new node;
    newNode->data = newData;
    newNode->next = *head;

    *head = newNode;
}

void printList(node *node)
{
    while (node != nullptr)
    {
        std::cout << node->data << ' ';
        node = node->next;
    }
    std::cout << std::endl;
}

node *getTail(node *current)
{
    while (current != nullptr && current->next != nullptr)
        current = current->next;

    return current;
}

node *partition(node *head, node *end, node **newHead, node **newEnd)
{
    node *pivot = end;
    node *prev = nullptr, *current = head, *tail = pivot;

    while (current != pivot)
    {
        if (current->data < pivot->data)
        {
            if (*newHead == nullptr)
                *newHead = current;

            prev = current;
            current = current->next;
        }
        else
        {
            if (prev)
                prev->next = current->next;

            node *temp = current->next;
            current->next = nullptr;
            tail->next = current;
            tail = current;
            current = temp;
        }
    }
    if (*newHead == nullptr)
        *newHead = pivot;

    *newEnd = tail;

    return pivot;
}

node *quickSortRecur(node *head, node *end)
{
    if (!head || head == end)
        return head;

    node *newHead = nullptr, *newEnd = nullptr;
    node *pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot)
    {
        node *temp = newHead;
        while (temp->next != pivot)
            temp = temp->next;
        temp->next = nullptr;

        newHead = quickSortRecur(newHead, temp);

        temp = getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);

    return newHead;
}

void quickSort(node **head)
{
    *head = quickSortRecur(*head, getTail(*head));
    return;
}

int main()
{
    node *a = nullptr;
    push(&a, 5);
    push(&a, 20);
    push(&a, 4);
    push(&a, 3);
    push(&a, 30);

    std::cout << "Linked list before sorting\n";
    printList(a);

    quickSort(&a);

    std::cout << "Linked list after sorting \n";
    printList(a);

    return 0;
}