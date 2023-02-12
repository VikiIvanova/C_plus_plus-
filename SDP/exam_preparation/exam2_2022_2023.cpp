// task 1

#include <cstring>
#include <exception>
#include <cassert>

template <typename T>
struct Node
{
    T data;
    Node<T> *left, *right;
};

bool read(const Node<char> *tree, const char *word, int len)
{
    if (len-- == 0)
        return true;

    if (tree && tree->data == *word++)
        return read(tree->left, word, len) || read(tree->right, word, len);

    return false;
}

bool readWord(const Node<char> *tree, const char *word)
{
    int size = strlen(word);
    if (size < 4)
    {
        throw std::exception();
    }

    Node<char> *left = tree->left, *right = tree->right;
    for (size_t i = 2; i < size - 1; i++)
    {
        if(word[i] == right->data)
        {
            return read(tree->left, word, i) && read(tree->right, word + 1, size - i);
        }
    }
    return false;
}

int main()
{
    Node<char> c{'c'};
    Node<char> e{'e'};
    Node<char> h{'h'};
    Node<char> a{'a'};
    Node<char> d{'d', &c, &e};
    Node<char> i{'i', &h};
    Node<char> b{'b', &a, &d};
    Node<char> g{'g', &i};
    Node<char> f{'f', &b, &g};
    assert(readWord(&f, "bdcgi") == true);
    assert(readWord(&f, "bdgi") == true);
    assert(readWord(&f, "bcdgi") == false);
    assert(readWord(&f, "bdgh") == false);
}

//task 2
#include <queue>
#include <iostream>
#include <climits>

size_t maxLevel(const Node<char>* tree)
{
    std::queue<const Node<char>*> q;
    q.push(tree);
    size_t level = 1, max = 0, min = ULONG_MAX;
    while(!q.empty())
    {
        int size = q.size();
        bool descending = true, ascending = true;
        char prev = CHAR_MAX;
        for(size_t i = 0; i < size; i++)
        {
            const Node<char> *node =q.front();
            q.pop();
            if(node->data > prev)
            {
                descending = false;
            }
            if(node->data < prev)
            {
                ascending = false;
            }
            prev = node->data;
            if(node->left)
            {
               q.push(node->left);
            }
            if(node->right)
            {
                q.push(node->right);
            }
        }
        if(descending)
        {
            max = std::max(max, level);
        }
        if(ascending && level != 1)
        {
            min = std::min(min, level);
        }
        level++;
    }
    if(max == 0)
    {
        throw std::logic_error("There is no descending level. ");
    }
    return max;
}

int main()
{
     Node<char> d{'d'};
    Node<char> c{'c'};
    Node<char> b{'b'};
    Node<char> a{'a'};
    Node<char> e{'e', &b, &a};
    Node<char> f{'f', &d, &c};
    Node<char> h{'h', &f, &e};
    assert(maxLevel(&h) == 3);
}