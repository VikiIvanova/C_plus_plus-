#include "binTree.h"
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>
#include <exception>

BinTree::BinTree() : root(nullptr) {}

bool BinTree::empty() const
{
    return !root;
}

bool BinTree::memberHelper(const int &data, const BinTree::BinNode *_root) const
{
    if (!_root)
        return false;

    if (data < root->data)
        return memberHelper(data, _root->left);

    else if (data > root->data)
        return memberHelper(data, _root->right);

    return true;
}

bool BinTree::member(const int &data) const
{
    return memberHelper(data, root);
}

void BinTree::addHelper(const int &data, BinTree::BinNode *&_root)
{
    if (!_root)
    {
        _root = new BinTree::BinNode{data};
        return;
    }
    if (data < _root->data)
    {
        addHelper(data, _root->left);
    }
    else if (data > _root->data)
    {
        addHelper(data, _root->right);
    }
}

void BinTree::add(const int &data)
{
    addHelper(data, root);
}

void BinTree::printHelper(BinTree::BinNode *_root) const
{
    if (!_root)
    {
        return;
    }
    printHelper(_root->left);
    std::cout << _root->data << " ";
    printHelper(_root->right);
}

void BinTree::printDotHelper(std::ostream &out, BinTree::BinNode *_root) const
{
    if (!_root)
    {
        return;
    }
    printDotHelper(out, _root->left);
    out << (long)_root << "[label=\"" << _root->data << "\"];\n";
    if (_root->left)
    {
        out << (long)_root << "->" << (long)_root->left << "[color=blue];\n";
    }
    if (_root->right)
    {
        out << (long)_root << "->" << (long)_root->right << "[color=red];\n";
    }
    printDotHelper(out, _root->right);
}

void BinTree::print() const
{
    printHelper(root);
}

void BinTree::printDot(std::ostream &out) const
{
    out << "digraph G{\n";

    printDotHelper(out, root);
    out << "}";
}

void BinTree::eraseHelper(const int &data, BinTree::BinNode *&_root)
{
    if (!_root)
    {
        return;
    }
    if (data < _root->data)
    {
        eraseHelper(data, _root->left);
    }
    else if (data > _root->data)
    {
        eraseHelper(data, _root->right);
    }
    else
    {
        if (!_root->left && !root->right)
        {
            BinTree::BinNode *save = _root;
            _root = nullptr;
            delete save;
        }
        else if (!_root->left && _root->right)
        {
            BinTree::BinNode *save = _root;
            _root = root->right;
            delete save;
        }
        else if (_root->left && !_root->right)
        {
            BinTree::BinNode *save = _root;
            _root = _root->left;
            delete save;
        }
        else
        {
            BinTree::BinNode *maxLeftSubTree = findMaxInLeftSubtree(_root->left);
            std::swap(_root->data, maxLeftSubTree->data);
            eraseHelper(data, _root->left);
        }
    }
}

BinTree::BinNode *BinTree::findMaxInLeftSubtree(BinTree::BinNode *_root)
{
    while (_root->right)
    {
        _root = _root->right;
    }
    return _root;
}

void BinTree::erase(const int &data)
{
    eraseHelper(data, root);
}

int BinTree::count() const
{
    return countHelper(root);
}

int BinTree::countHelper(BinTree::BinNode *_root) const
{
    if (!_root)
    {
        return 0;
    }
    return 1 + countHelper(_root->left) + countHelper(_root->right);
}

int BinTree::countFHelper(BinTree::BinNode *_root, bool (*f)(int)) const
{
    if (!_root)
    {
        return 0;
    }
    if (f(_root->data))
    {
        return 1 + countFHelper(_root->left, f) + countFHelper(_root->right, f);
    }
    return countFHelper(_root->left, f) + countFHelper(_root->right, f);
}

int BinTree::countEvens() const
{
    return countFHelper(root, [](int el) -> bool
                        { return el % 2 == 0; });
}

int BinTree::heightHelper(BinTree::BinNode *_root) const
{
    if (!_root)
    {
        return -1;
    }
    return 1 + std::max(heightHelper(_root->left), heightHelper(_root->right));
}

int BinTree::height() const
{
    return heightHelper(root);
}

int BinTree::countHelperLeaves(BinTree::BinNode *_root) const
{
    if (!_root)
    {
        return 0;
    }
    if (!_root->left && !_root->right && _root)
    {
        return 1;
    }
    return countHelperLeaves(_root->left) + countHelperLeaves(_root->right);
}

int BinTree::countLeaves() const
{
    return countHelperLeaves(root);
}

int BinTree::maxHelperLeave(BinTree::BinNode *_root) const
{
    if (!_root->left && !_root->right && _root)
    {
        return _root->data;
    }
    else if (!_root->right && root && _root->left)
    {
        return maxHelperLeave(_root->left);
    }
    else
    {
        return maxHelperLeave(_root->right);
    }
}

int BinTree::maxLeave() const
{
    if (empty())
    {
        throw std::out_of_range("Empty Balanced Tree");
        return INT_MIN;
    }
    return maxHelperLeave(root);
}

int &BinTree::theLeftestLeaf(BinTree::BinNode *current) const
{
    while (current->left || current->right)
    {
        if (!current->left && current->right)
        {
            current = current->right;
        }
        else
        {
            current = current->left;
        }
        if (!current->left && !current->right)
        {
            return current->data;
        }
    }
    return current->data;
}

int BinTree::maxLeaveNewHelper(BinTree::BinNode *current, int data)
{
    if (!current)
    {
        return data;
    }
    if (current && !current->left && !current->right)
    {
        data = std::max(data, current->data);
    }
    return std::max(maxLeaveNewHelper(current->left, data), maxLeaveNewHelper(current->right, data));
}

int BinTree::maxLeaveNew()
{
    int data = theLeftestLeaf(root);
    return maxLeaveNewHelper(root, data);
}

BinTree::BinNode *BinTree::locate(const char *s) const
{
    if (empty())
    {
        throw std::out_of_range("Empty tree at the locate method ->289 line");
    }
    if (s[0] == 0)
    {
        return root;
    }
    BinTree::BinNode *current = root;
    while (current && s[0] != 0)
    {
        if (s[0] != 'L' && s[0] != 'R')
        {
            throw "Error symbol at the locate method -> 300 line";
        }
        if (s[0] == 'L')
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
        ++s;
    }
    if (!current)
    {
        throw std::out_of_range("Error road in locate on 314 line");
    }
    return current;
}

int BinTree::operator[](const char *s) const
{
    return locate(s)->data;
}
/*void BinTree::set(int element, const char *s) const
{
    locate(s)->data = element;
}*/

void BinTree::clearHelper(BinTree::BinNode *&current)
{
    if (!current)
    {
        return;
    }
    if(current && !current->left && !current->right)
    {
        BinTree::BinNode *save = current;
        current = nullptr;
        delete save;
        return;
    }
    clearHelper(current->left);
    clearHelper(current->right);

}

void BinTree::clear()
{
    clearHelper(root);
}

BinTree::~BinTree()
{
    clear();
}

void BinTree::DFS(BinTree::BinNode* t) const
{
    std::stack<BinTree::BinNode*> stack;
    stack.push(t);

    while(!stack.empty())
    {
        BinTree::BinNode* curr = stack.top();
        stack.pop();

        std::cout << curr->data << "->";

        if(!curr->left && !curr->right)
        {
            continue;
        }
        stack.push(curr->left);
        stack.push(curr->right);
    }
}

void BinTree::BFS(BinTree::BinNode *root) const
{
    std::queue<BinTree::BinNode *> q;
    q.push(root);
    while (!q.empty())
    {
        BinTree::BinNode *cur = q.front();
        q.pop();
        std::cout << cur->data << " -> ";
        if (!cur->left && !cur->right)
        {
            continue;
        }

        q.push(cur->left);
        q.push(cur->right);
    }
}

