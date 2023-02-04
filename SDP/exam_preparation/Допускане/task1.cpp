#include <iostream>

struct node
{
    int data;
    node *next;
};

node *toList(const int *arr, size_t size)
{
    node *list = new node{arr[0], nullptr};
    for (int i = 1; i < size; ++i)
    {
        node *last = list;
        while (last->next != nullptr)
        {
            last = last->next;
        }
        last->next = new node{arr[i], nullptr};
    }
    return list;
}

void deleteList(node *&list)
{
    while (list)
    {
        node *toDelete = list;
        list = list->next;
        delete toDelete;
    }
}

void printList(node *list)
{
    while (list != nullptr)
    {
        std::cout << list->data << ' ';
        list = list->next;
    }
    std::cout << std::endl;
}

void removeConsecutiveDuplicates(node *list)
{
    if (list == nullptr)
        return;

    node *current = list;
    while (current && current->next)
    {
        if (current->data == current->next->data)
        {
            node *toDelete = current->next;
            current->next = current->next->next;
            delete toDelete;
        }
        else
        {
            current = current->next;
        }
    }
}

int main()
{
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    node *list = toList(array, 10);
    printList(list);
    deleteList(list);

    int arrayWithDuplicate[14] = {1, 1, 2, 2, 1, 1, 2, 2, 2, 2, 1, 2, 1, 2};
    node *listWithDuplicates = toList(arrayWithDuplicate, 14);
    printList(listWithDuplicates);
    removeConsecutiveDuplicates(listWithDuplicates);
    printList(listWithDuplicates);
    deleteList(listWithDuplicates);

    return 0;
}