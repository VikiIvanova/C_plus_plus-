/*
Обрънете реда на оказана част от 0-индексиран свързан списък по дадени индекси.
*/
struct Node
{
    int data;
    Node* next;
};

void reverse(Node*& head, int m, int n)
{
    if(m > n)
       return;
    
    Node* prev = nullptr;
    Node* curr = head;

    for(int i = 1; curr != nullptr && i < m; i++)
    {
        prev = curr;
        curr = curr->next;
    }

    Node* start = curr;
    Node* end = nullptr;

    for(int i = 1; curr != nullptr && i <= n - m + 1; i++)
    {
        Node* next = curr->next;

        curr->next = end;
        end = curr;

        curr = next;
    }

    if(start)
    {
        start->next = curr;
        if(prev != nullptr)
        {
            prev->next = end;
        }
        else
        {
            head = end;
        }
    }
}