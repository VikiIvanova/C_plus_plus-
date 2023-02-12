template <typename T>
struct node
{
    T data;
    node<T> *next;
    node() : data(T()), next(nullptr){};
};
/*Задача 1. Да се дефинира функция fillgaps, която приема като
  единствен параметър указател към линеен едносвързан списък от цели
  числа, наредени в нарастващ ред. Функцията да вмъква между всеки два
  съседни елемента a и b, такива че b – a > 1, числата a + 1, a + 2,
  ..., b, така че елементите на списъка да образуват редицата от
  поредните цели числа в интервала между първия и последния елемент на
  списъка.*/

void fillgaps(node<int> *l)
{
    if (l == nullptr)
    {
        return;
    }
    while (l->next != nullptr)
    {
        while (l->next->data - l->data > 1)
        {
            l->next = new node<int>(l->data + 1, l->next);
            l = l->next;
        }
        l = l->next;
    }
}
/*
 Да се дефинира функция removeIdx, която приема като
  единствен параметър указател към линеен едносвързан списък от цели
  числа. Функцията да премахва от списъка всички елементи, които са
  равни на разликата между индекса на последния елемент и индекса на
  самия елемент.*/
void removeIdx(node<int> *&l)
{

    if (l == nullptr)
        return;

    int length = 0;
    node<int> *crr = l;
    while (crr != nullptr)
    {
        ++length;
        crr = crr->next;
    }
    node<int> *save;
    int i;
    for (crr = l, i = length - 2; i >= 0; --i)
    {
        if (crr->next->data == i)
        {
            save = crr->next->next;
            delete crr->next;
            crr->next = save;
        }
        else
        {
            crr = crr->next;
        }
    }

    if (l->data == length - 1)
    {
        save = l->next;
        delete l;
        l = save;
    }
}
/* 3 задача:
  Да се дефинира шаблон на булева функция dupsub, която
  приема два параметъра: указател към линеен едносвързан списък и
  неотрицателно число k. Функцията да връща истина, ако в списъка има
  поне два различни подсписъка с дължина k, които са са еднакви
  елементи. Примери за такива списъци са 1, 2, 3, 4, 1, 2, 5 и 1, 2,
  3, 3, 3, 4 за k = 2.*/

template <typename T>
bool commonprefix(node<T> *l1, node<T> *l2, unsigned k)
{
    while (l1 != nullptr && l2 != nullptr && l1->data == l2->data && k > 0)
    {
        l1 = l1->next;
        l2 = l2->next;
        k--;
    }
    return k == 0;
}

template <typename T>
bool dupsub(node<T> *l, unsigned k)
{

    node<T> *second = l;

    while (l != nullptr)
    {
        second = l->next;
        while (second != nullptr)
        {
            if (commonprefix(l, second, k))
            {
                return true;
            }
            second = second->next;
        }
        l = l->next;
    }
    return false;
}

/*Задача 4. Да се дефинира шаблон на функция mirror, която приема като
  единствен параметър указател към линеен едносвързан списък. Към края
  на списъка да се долепят оригиналните му елементи в обратен
  ред. Например, списъкът с елементи 1, 2, 3 да се преобразува до
  списъка 1, 2, 3, 3, 2, 1.*/

template <typename T>
void mirror(node<T> *l)
{
    if (l == nullptr)
        return;

    node<T> *last = l;

    while (last->next != nullptr)
    {
        last = last->next;
    }

    while (l != last->next)
    {
        last->next = new node<T>(l->data, last->next);
        l = l->next;
    }
}

/*Задача 5. Да се дефинира функция removedups, която приема като
  единствен параметър указател към линеен едносвързан списък от цели
  числа, наредени в ненамаляващ ред. Функцията да изтрива всички
  повторения на елементи в списъка, така че всеки от оригиналните му
  елементи да се среща само веднъж, така че елементите на списъка да
  образуват строго растяща редица. Задачата да се реши без използване
  на помощна структура от данни (с константна сложност по памет).*/

void removedups(node<int> *l)
{
    node<int> *save;

    while (l != nullptr && l->next != nullptr)
    {
        while (l->next != nullptr && l->data == l->next->data)
        {
            save = l->next->next;
            delete l->next;
            l->next = save;
        }
        l = l->next;
    }
}

/*Задача 6. Да се дефинира шаблон на функция removesub, която приема
  два параметъра first и second — указатели към линейни едносвързани
  списъци. Функцията да изтрива от списъка с начало first
  последователно всички срещания на подсписъци, които съвпадат със
  списъка с начало second. Например, при списък first с елементи 1, 2,
  3, 3, 3, 4, 5, 3, 3, 6 и second с елементи 3, 3, first да се
  преобразува до списъка 1, 2, 3, 4, 5, 6.*/
template <typename T>
bool issublist(node<T> *sub, node<T> *list)
{
    while (sub != nullptr && list != nullptr && sub->data == list->data)
    {
        sub = sub->next;
        list = list->next;
    }

    return sub == nullptr;
}

template <typename T>
bool deleteprefix(node<T> *sub, node<T> *&list)
// sub MUST be a prefix of list
{
    node<T> *save;
    while (sub != nullptr)
    {
        sub = sub->next;
        save = list->next;
        delete list;
        list = save;
    }

    return sub == nullptr;
}

template <typename T>
void removesub(node<T> *&first, node<T> *second)
{

    if (first == nullptr || second == nullptr)
    {
        return;
    }

    node<T> *crr = first;

    if (issublist(second, first))
    {
        deleteprefix(second, first);
    }

    while (crr->next != nullptr)
    {
        if (issublist(second, crr->next))
        {
            deleteprefix(second, crr->next);
        }
        else
        {
            crr = crr->next;
        }
    }
}

/*Задача 1. Даден е символен низ, състоящ се от кръглите скоби '(',
  ')', запетайки ',' и малки латински букви. Да се реализира функция
  bool valid(const std::string &s, unsigned& error), която проверява
  дали низът, записан в s, е правилно записан функционален израз
  съгласно следните правила:

    <променлива> ::= a | b | … | z
    <израз> ::= <променлива> | <променлива>(<израз>{,<израз>})

  Ако низът s не е коректен, в параметъра error да се запише индексът
  на първия некоректен символ. В реализацията на valid не е позволено
  използването на рекурсия.

  Пример: Например, "f(g(x,y),h(k(u)),v)" е правилно записан израз, но
  "f(g(,x)" и "(f(x),g(y))" не са, като стойността на error е
  съответно 4 и 0.

  Упътване:
    * В стек записваме отварящи скоби, букви и специален символ
    (например '?'), означаващ “резултат от извикването на
    функция”.
    * Какво трябва да има на върха на стека при прочитане на ','?
    * Какво трябва да се случи със стека при прочитане на ','?
    * Какво трябва да има на върха на стека при прочитане на ')'?
    * Какво трябва да се случи със стека при прочитане на ')'?
    * Освен случаите на ',' и ')', какви още проверки за коректност са
    нужни?
    * Какво съдържание трябва да има стекът след приключване на
    програмата?*/

#include <string>
#include <stack>

bool isLetter(char c)
{
    return 'a' <= c && c <= 'z';
}
bool isLetterQ(char c)
{
    return isLetter(c) || c == '?';
}

bool valid(const std::string &s, unsigned &error)
{
    unsigned &i = error;
    std::stack<char> stack;
    for (i = 0; i < s.size(); ++i)
        if (s[i] == '(')
        {
            if (stack.empty() || !isLetter(stack.top()))
                return false;
            stack.push(s[i]);
        }
        else if (isLetter(s[i]))
        {
            if (!stack.empty() && stack.top() != '(')
                return false;
            stack.push(s[i]);
        }
        else if (s[i] == ',')
        {
            if (stack.empty() || !isLetterQ(stack.top()))
                return false;
            stack.pop();
            if (stack.empty() || stack.top() != '(')
                return false;
        }
        else if (s[i] == ')')
        {
            if (stack.empty() || !isLetterQ(stack.top()))
                return false;
            stack.pop();
            if (stack.empty() || stack.top() != '(')
                return false;
            stack.pop();
            if (stack.empty() || !isLetter(stack.top()))
                return false;
            stack.pop();
            stack.push('?');
        }
        else
            return false;
    if (stack.empty() || !isLetterQ(stack.top()))
        return false;
    stack.pop();
    return stack.empty();
}

/*Задача 2. Даден е вектор v от цели числа.Казваме, че двоичното
дърво с положителни числа по върховете t представя v при следните условия :
    *v е празният вектор и t е празното дърво;
или
*ако v = v[0],…, v[k - 1], a m = ⌊k / 2⌋(долна цяла част), то коренът на t съдържа числото v[m],
лявото поддърво на t представя вектора v[0],…, v[m - 1],
а дясното поддърво на t представя вектора v[m + 1],…, v[k - 1].
Забележка : ако k = 2, то десния подвектор считаме за празен.
           а) Да се реализира функция, която построява дърво, представящо
           вектора v, и връща указател към корена му.

           Упътване: Ако v е вектор, то с помощта на следния конструктор
           std::vector<unsigned> L(v.begin(), v.begin() + count) ще получите
           първите count елемента от v,
           а с std::vector<unsigned> R (v.begin() + start, v.end()), ще
           получите суфикса на v, започващ от елемента с индекс start.

           Пример:
           std::vector<unsigned> v{1, 2, 3, 4, 5, 6},
                                 L(v.begin(), v.begin() + 3),
                                 R(v.begin() + 4, v.end());

           Тогава L е векторът 1, 2, 3, а R е векторът 5, 6.*/
#include <vector>

node<unsigned> *buildTree(const std::vector<unsigned> &v)
{
    if (v.empty())
        return nullptr;

    unsigned mid = v.size() / 2;
    std::vector<unsigned> L(v.begin(), v.begin() + mid), R(v.begin() + mid + 1, v.end());
    return new node<unsigned>(v[mid], buildTree(L), buildTree(R));
}

/***********************************************************************
 б) Да се реализира функция, която връща вектор, съставен от възлите
 по път в дървото от корен до листо, в който сумата на елементите е
 максимална.
************************************************************************/

void findMaxSum(node<unsigned> *t, unsigned sum, std::vector<unsigned> &v, unsigned &max, std::vector<unsigned> &maxPath)
{
    if (t == nullptr)
    {
        if (sum > max)
        {
            max = sum;
            maxPath = v;
        }
    }
    else
    {
        v.push_back(t->data);
        findMaxSum(t->left, sum + t->data, v, max, maxPath);
        findMaxSum(t->right, sum + t->data, v, max, maxPath);
        v.pop_back();
    }
}

std::vector<unsigned> sumMax(node<unsigned> *t)
{
    std::vector<unsigned> empty, result;
    unsigned max = 0;
    findMaxSum(t, 0, empty, max, result);
    return result;
}
