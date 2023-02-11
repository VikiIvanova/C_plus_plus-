/*Напишете програма, която работи с текстов файл, представящ дърво с произволна разклоненост и символи в
елементите. Форматът на файла е следния.
(корен <(поддърво 1) .. (поддърво n)>)
Например дървото
се представя така:
(a <(b <(d) (f)>) (c) (a <(c) (m) (n)>)>)
Напишете:
 Функция, която създава дърво от подадения файл.
 Функция, която по подадено такова дърво и число връща символният низ, получен от прочитането отлявонадясно на символите от нивото с номер подаденото число. Например за нарисуваното дърво и числото 2
трябва да върне символния низ „dfcmn”.
Демонстрирайте използването на тези функции в програма, която получава името на такъв текстов файл като
аргумент от командния ред и след това въвежда от потребителя многократно номера на нивата от които да
състави символни низове.*/

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

struct TreeNode {
    char val;
    vector<TreeNode*> children;
    TreeNode(char x) : val(x) {}
};

// Function to create a tree from the input file
TreeNode* createTree(ifstream &file) {
    char c;
    file >> c;
    TreeNode *node = new TreeNode(c);

    while (file >> c && c != '>') {
        if (c == '<') {
            node->children.push_back(createTree(file));
        }
    }
    return node;
}

// Function to get the character sequence at a given level of the tree
string levelOrder(TreeNode *root, int level) {
    string result;
    if (root == NULL) {
        return result;
    }
    if (level == 1) {
        result += root->val;
        return result;
    }

    for (int i = 0; i < root->children.size(); i++) {
        result += levelOrder(root->children[i], level - 1);
    }

    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <file name>" << endl;
        return 0;
    }

    ifstream file(argv[1]);
    if (!file) {
        cout << "File " << argv[1] << " not found" << endl;
        return 0;
    }

    TreeNode *root = createTree(file);
    file.close();

    int level;
    cout << "Enter level: ";
    while (cin >> level) {
        cout << "Result: " << levelOrder(root, level) << endl;
        cout << "Enter level: ";
    }

    return 0;
}

/*Напишете функция, която получава като аргументи два списъка от цели числа. Проверете, че всеки от тях е получен
от сортиран възходящо списък, който е разделен на две части в някаква точка и места на тези части са разменени.
Ако списъците отговарят на тези условия ги слейте в сортиран възходящо списък, който ще е резултат от функцията.
Ако някой от списъците не отговаря на тези условия – изведете подходящо съобщение на екрана и върнете празен
списък.
Демонстрирайте функцията в кратка програма.
Пример:
Входни списъци: Резултат:
L1: 1->2->5->7->10 1->2->2->4->5->6->7->7->9->10->11
L2: 9->11->2->4->6->7
Входни списъци: Резултат:
L1: 10->1->2->5->7 The second argument is wrong!
L2: 8->11->2->4->6->7->9
*/
#include <iostream>
struct ListNode
{
    int data;
    ListNode *next;
    ListNode(int data, ListNode *next = nullptr) : data(data), next(next){};
};

bool isSorted(ListNode *list)
{
    while (list && list->next)
    {
        if (list->data > list->next->data)
            return false;

        list = list->next;
    }
    return true;
}

ListNode *isSplitCorrect(ListNode *list)
{
    ListNode *current = list;
    ListNode *firstPartOfList = nullptr;
    ListNode *secondPartOfList = nullptr;
    ListNode *secondPartHead = nullptr;
    while (current->next != nullptr && current->data <= current->next->data)
    {
        current = current->next;
    }
    firstPartOfList = list;
    secondPartOfList = current->next;
    current->next = nullptr;
    if (secondPartOfList != nullptr)
    {
        secondPartHead = secondPartOfList;
        current = secondPartOfList;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = firstPartOfList;
    }
    return secondPartHead != nullptr ? secondPartHead : firstPartOfList;
}

ListNode* mergeLists( ListNode* head1, ListNode* head2 )
{
	ListNode* resultList = nullptr;
	ListNode* forward = head2;
	ListNode* current = head2;
	while ( forward->data < head1->data )
	{
		current = forward;
		forward = forward->next;
	}
	if ( forward != head2 )
	{
		resultList = head2;
		current->next = head1;
		head2 = forward;
	}
	else
	{
		resultList = head1;
	}
	
	while ( head2 )
	{
		if ( head1 && head1->data <= head2->data && head1->next && head2->data <= head1->next->data )
		{
			ListNode* ahead = head1->next;
			head1->next = head2;
			head1 = head1->next;
			ListNode* currentNode = head2->next;
			head2->next = ahead;
			head2 =  currentNode;
		}
		else if ( head1 && head1->next )
		{
			head1 = head1->next;
		}
		else if ( head1 && !head1->next )
		{
			head1->next = head2;
			break;
		}
	}

	return resultList;
}


int main()
{
    ListNode *list1_1 = new ListNode((1), new ListNode((2), new ListNode((5), new ListNode((7), new ListNode(10)))));
    ListNode *list1_2 = new ListNode((9), new ListNode((11), new ListNode((2), new ListNode((4), new ListNode((6), new ListNode(7))))));
    ListNode *list2_1 = new ListNode((10), new ListNode((1), new ListNode((2), new ListNode((5), new ListNode(7)))));
    ListNode *list2_2 = new ListNode((8), new ListNode((11), new ListNode((2), new ListNode((4), new ListNode((6), new ListNode((7), new ListNode(9)))))));

    ListNode *temp1 = isSplitCorrect(list1_1);
    ListNode *temp2 = isSplitCorrect(list1_2);
    if (isSorted(temp1) && isSorted(temp2))
    {
        ListNode *result1 = mergeLists(temp1, temp2);
        while (result1)
        {
            std::cout << result1->data << " ";
            result1 = result1->next;
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Error" << std::endl;
    }
    ListNode *current1 = isSplitCorrect(list2_1);
    ListNode *current2 = isSplitCorrect(list2_2);
    if (isSorted(current1) && isSorted(current2))
    {
        ListNode *result2 = mergeLists(current1, current2);
        while (result2)
        {
            std::cout << result2->data << " ";
            result2 = result2->next;
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Error" << std::endl;
    }
}