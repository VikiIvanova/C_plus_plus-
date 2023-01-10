#pragma once
#include "binarySearchTree.h"

template <class T>
BST<T>::BST() : root(nullptr) {}

template <class T>
BST<T>::BST(const BST &other)
{
    this->copyBranch(root, other.root);
}

template <class T>
BST<T> &BST<T>::operator=(BST other) noexcept
{
    std::swap(root, other.root);
    return *this;
}

template <class T>
BST<T>::~BST()
{
    this->deleteBranch(root);
}

template <class T>
void BST<T>::insert(const T &elem)
{
    this->insertRec(root, elem);
}

template <class T>
bool BST<T>::tryInsert(const T &elem)
{
    return this->tryInsertRec(root, elem);
}

template <class T>
typename BST<T>::opt_const_ref BST<T>::find(const T &elem) const
{
    return this->findRec(root, elem);
}

template <class T>
bool BST<T>::erase(const T &elem)
{
    return this->eraseRec(root, elem);
}

template <class T>
void BST<T>::print(std::ostream &out) const
{
    this->printRec(root, out);
}

template <class T>
T BST<T>::min() const
{
    if (root == nullptr)
        throw std::logic_error("BST: min() of an empty BST!");

    BST<T>::Node *curr = root;
    while (curr->left)
        curr = curr->left;

    return curr->data;
}

template <class T>
BST<T>::maxRec(const Node *node) const
{
    if (node == nullptr)
        throw std::logic_error("BST:max() of an empty BST!");
    if (node->right)
        return this->maxRec(node->right);

    return node;
}

template <class T>
void BST<T>::deleteBranch(Node *&node) noexcept
{
    if (!node)
        return;

    deleteBranch(node->left);
    deleteBranch(node->right);
    delete node;
    node = nullptr;
}

template <class T>
void BST<T>::copyBranch(Node *&node, const Node *otherNode)
{
    if (!otherNode)
        return;
    node = new Node{otherNode->data};
    this->copyBranch(node->left, node);
    this->copyBranch(node->right, otherNode->right);
}

template <class T>
void BST<T>::insertRec(Node *&node, const T &elem)
{
    if (!this->tryInsertRec(node, elem))
        throw std::logic_error("BST: Cannot store duplicate elements!");
}

template <class T>
bool BST<T>::tryInsertRec(Node *&node, const T &elem)
{
    if (node == nullptr)
    {
        node = new Node{elem};
        return true;
    }
    if (elem < node->data)
    {
        return this->tryInsertRec(node->left, elem);
    }
    if (elem > node->data)
    {
        return this->tryInsertRec(node->right, elem);
    }
    return false;
}

template <class T>
typename BST<T>::opt_const_ref
BST<T>::findRec(const Node *node, const T &elem) const
{
    if (!node)
    {
        return std::nullptr;
    }
    if (elem == node->data)
    {
        return node->data;
    }
    if (elem < node->data)
    {
        return this->findRec(node->left, elem);
    }
    return this->findRec(node->right, elem);
}

template <class T>
bool BST<T>::eraseRec(Node *&node, const T &elem)
{
    if (!node)
        return false;
    if (node->data == elem)
    {

        if (node->data == elem && !node->right)
        {
            delete node;
            node = nullptr;
        }
        else if ((node->left && !node->right) || (!node->left && node->right))
        {
            Node *onlyChild = node->left ? node->left : node->right;
            Node *toRemove = node;
            node = onlyChild;
            delete toRemove;
        }
        else
        {
            Node *&min = this->minRec(node->right);
            std::swap(node->data, min->data);
            this->eraseRec(min, elem);
        }
        return true;
    }
    else if (elem < node->data)
    {
        return this->eraseRec(node->left, elem);
    }
    return this->eraseRec(node->right, elem);
}

template<class T>
void BST<T>::printRec(const Node* node, std::ostream& out) const
{
    if(!node)
       return;
    this->printRec(node->left);
    out << node->data << " ";
    this->printRec(node->right);
}

template<class T>
typename BST<T>::Node*&
BST<T>::minRec(Node*& node)
{
    if(node->left)
       return this->minRec(node->left);

    return node;
}
