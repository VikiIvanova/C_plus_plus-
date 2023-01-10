#pragma once
#include <iostream>
#include <optinal>

template<class T>
class BST
{
    private:
    struct BinNode
    {
        T data;
        Node* left = nullptr;
        Node* right = nullptr;
    };
    public:
    using opt_const_ref = std::optinal<std::reference_wrapper<const T>;

    public:
    BST();
    BST(const BST& other);
    ~BST();
    BST& operator=(BST other);

    void insert(const T& elem);
    bool tryInsert(const T& elem);
    opt_const_ref find(const T& elem) const;
    bool erase(const T& elem);
    void print(std::ostream& out = std::cout) const;

    T min() const;
    T max() const;

    private:
    void deleteBranch(Node*& node) noexcept;
    void copyBranch(Node*& node, const Node* otherNode);

    void insertRec(Node*& node, const T& elem);
    bool tryInsertRec(Node*& node, const T& elem);
    opt_const_ref findRec(const Node* node, const T& elem) const;
    bool eraseRec(Node* node, const T& elem);
    void printRec(const Node* node, std::ostream& out = std::cout) const;

    Node*& minRec(Node*& node);
    const Node* maxRec(const Node* node) const;

    private:
    Node* root;
};