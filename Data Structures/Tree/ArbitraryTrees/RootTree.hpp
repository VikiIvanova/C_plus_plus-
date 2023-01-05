#pragma once

#include <list>

template<class ValueType, class Container = std::list<ValueType>>
struct RootTree
{
    struct Node;
    using ChildrenList = std::list<Node*>;

    struct Node
    {
        ChildrenList fChildrenList;
        ValueType fValue;
        Node* fParentPtr;
        bool fIsVisited;

        Node(Node* parent, const ValueType& value);

        Node& addChild(const ValueType& value);
    };

    RootTree();
    RootTree(const RootTree& other);
    RootTree operator=(RootTree other);
    ~RootTree();

    //Adds a child to the given node
    //returns a pointer to the newly allocated node
    Node* addNode(Node* node, const ValueType& value);

    //Adds a new node as a root for the tree
    //returns a pointer to the newly allocated node
    Node* addRootNode(const ValueType& value);

    //Deletes the given node as well as all its children recursively
    //Note:If the root is given - the whole tree will be deleted.
    RootTree& deleteBranch(Node* node);

    //Clones the given node as a well as its children
    Node* cloneBranch(const Node* node);

    //Searches and returns a Node containing the given value using DFS
    //returns nullptr if no such no exists.
    const Node* findDeep(const ValueType& value);
    const Node* findDeep(const ValueType& value, const Node* from);

    //Searches and returns a Node containing the given laue using...
    const Node* findDeep(const ValueType& value) const;
    const Node* findDeep(const ValueType& value, const Node* from) const;

    //Searches and returns a Node containing the given value using BFS
    //returns nullptr if no such no exists.
    const Node* findShallow(const ValueType& value) const;
    const Node* findShallow(const ValueType& value, const Node* from) const;

    //Returns the height of the tree(or subtree if given a node)
    size_t height() const;
    size_t height(const Node* from) const;

    //Returns the max branching of all nodes of this tree(or subtree if given a node)
    size_t branchingFactor() const;
    size_t branchingFactor(const Node* from) const;

    //Prints all elements at the given level, where the root level is 0)
    void printLevel(size_t level) const;
    void printLevel(size_t level, const Node* from) const;

    Node* fRootPtr;
}