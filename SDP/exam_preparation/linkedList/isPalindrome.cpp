#include <iostream>
#include <stack>

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x, ListNode* next = nullptr) : val(x), next(next) {}
};

bool isPalindrome(ListNode *head)
{
    ListNode *slow = head, *fast = head;
    std::stack<int> s;

    while (fast != nullptr && fast->next != nullptr)
    {
        s.push(slow->val);
        slow = slow->next;
        fast = fast->next->next;
    }

    // If the number of nodes is odd, skip the middle node
    if (fast != nullptr)
    {
        slow = slow->next;
    }

    while (slow != nullptr)
    {
        int top = s.top();
        s.pop();
        if (top != slow->val)
        {
            return false;
        }
        slow = slow->next;
    }

    return true;
}
int main()
{
    ListNode *ll = new ListNode(1, new ListNode(2, new ListNode(1)));

    std::cout << std::boolalpha <<  isPalindrome(ll) << std::endl;
}