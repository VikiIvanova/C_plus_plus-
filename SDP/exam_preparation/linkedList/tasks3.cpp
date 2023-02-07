struct LinkedListNode
{
    int data;
    LinkedListNode *next;
    LinkedListNode(int x, LinkedListNode *next = nullptr) : data(x), next(next) {}
};

// Да се напише функция, която приема сортиран свързан списък и добавя elem на правилното място.
void insertSorted(LinkedListNode *&l1, const int &elem)
{
    LinkedListNode *toInsert = new LinkedListNode(elem);

    if (l1 == nullptr)
        l1 = toInsert;

    else if (l1->data > elem)
    {
        toInsert->next = l1;
        l1 = toInsert;
    }
    else if (l1->next == nullptr)
    {
        l1->next = toInsert;
    }
    else
    {
        LinkedListNode *it = l1;
        while (it->next != nullptr)
        {
            if (it->next->data > elem)
            {
                LinkedListNode *nNext = it->next;
                it->next = toInsert;
                toInsert->next = nNext;
                return;
            }
            it = it->next;
        }
        it->next = toInsert;
    }
}
/*Задача втора
Нека имаме двусвързан списък от опашки и символи.
Във всяка опашка от началото към края е записан валиден израз в обратна полска нотация.
Операторите са [+, -, *, /] а операндите за улеснение са едноцифрени числа.
Да се напише функция, която приема такъв списък, изчислява стойността на всички опашки,
и връща дали списъка от резултатите е симетричен спрямо средата.
Пример:

      *           *     +
      |           |     |
      7           *     3
      |           |     |
+     +           7     *
|     |           |     |
5     6           7     3
|     |           |     |
4     1     8     1     2
|     |     |     |     |
* <-> * <-> * <-> * <-> *
Изход: 1
Примера ще се оцени до 9 <-> 49 <-> 8 <-> 49 <-> 9, който е симетричен списък.*/

#include <list>
#include <iostream>
#include <queue>
#include <stack>

bool isSymetric(const std::list<int> &l1)
{
    auto start = l1.begin();
    auto end = --(l1.end());
    while (start != end)
    {
        if (*start != *end)
            return false;

        ++start;
        if (start == end)
            break;
        --end;
    }
    return true;
}

int evaluateExpr(char op, int fst, int snd)
{
    switch (op)
    {
    case '+':
        return (fst + snd);
        break;
    case '-':
        return (fst - snd);
        break;
    case '*':
        return (fst * snd);
        break;
    case '/':
        return (snd / fst);
        break;
    }
    return 0;
}

size_t evaluateQueue(std::queue<char> q)
{
    std::stack<int> nums;
    while (!q.empty())
    {
        if (isdigit(q.front()))
        {
            int cDigit = q.front() - '0';
            q.pop();
            nums.push(cDigit);
        }
        else
        {
            int fst = nums.top();
            nums.pop();
            int snd = nums.top();
            nums.pop();
            char op = q.front();
            q.pop();

            nums.push(evaluateExpr(op, fst, snd));
        }
    }
    return nums.top();
}

bool solution(const std::list<std::queue<char>> &l1)
{
    std::list<int> l;
    for (auto elem : l1)
        l.push_back(evaluateQueue(elem));

    return isSymetric(l);
}

int main()
{
    std::list<std::queue<char>> test(5);

    auto it = test.begin();
    (*it).push('4');
    (*it).push('5');
    (*it).push('+');

    ++it;

    (*it).push('1');
    (*it).push('6');
    (*it).push('+');
    (*it).push('7');
    (*it).push('*');
    ++it;

    (*it).push('8');
    ++it;

    (*it).push('1');
    (*it).push('7');
    (*it).push('7');
    (*it).push('*');
    (*it).push('*');

    ++it;

    (*it).push('2');
    (*it).push('3');
    (*it).push('*');
    (*it).push('3');
    (*it).push('+');

    std::cout << std::boolalpha << solution(test) << std::endl;

    return 0;
}