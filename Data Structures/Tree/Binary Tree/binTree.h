#ifndef _BINTREE_HPP
#define _BINTREE_HPP
#include<iostream>

class BinTree
{
    private:
    struct BinNode
    {
        int data;
        BinNode* left;
        BinNode* right;

        BinNode(const int& _data, BinNode* _left = nullptr, BinNode* _right = nullptr) :
        data(_data), left(_left), right(_right) {}
    };
    BinNode* root;
    void addHelper(const int&, BinNode*&);
    bool memberHelper(const int &, const BinNode *) const;
    void printHelper(BinNode*) const;
 void printDotHelper(std::ostream &, BinNode *) const;
    void eraseHelper(const int &, BinNode *&);
    BinNode *findMaxInLeftSubtree(BinNode *);
    int countHelper(BinNode *) const;
    int countFHelper(BinNode *, bool (*f)(int)) const;
    int heightHelper(BinNode *) const;
    int countHelperLeaves(BinNode *) const;
    int maxHelperLeave(BinNode *) const;
    int maxLeaveNewHelper(BinNode *, int);
    int &theLeftestLeaf(BinNode *) const;
    BinNode *locate(const char *) const;
    void clear();
    void clearHelper(BinNode *&);

public:
    BinTree();
    void add(const int &data);
    bool member(const int &) const;
    bool empty() const;
    void print() const;
    void printDot(std::ostream &) const;
    void erase(const int &);
    int count() const;
    int countEvens() const;
    int height() const;
    int countLeaves() const;
    int maxLeave() const;
    int maxLeaveNew();
    int operator[](const char *) const;
    void set(int, const char *);
    void DFS(BinNode *) const;
    void BFS(BinNode *) const;
    ~BinTree();
};

#endif