#include <iostream>

struct node
{
    int data;
    node *left;
    node *right;
};

node *newNode(int data)
{
    node *root = new node();
    root->data = data;
    root->left = nullptr;
    root->right = nullptr;

    return root;
}
node *toTree(const int *sorted_data, int start, int end)
{
    if (start > end)
        return nullptr;

    int mid = (start + end) / 2;
    node *root = newNode(sorted_data[mid]);

    root->left = toTree(sorted_data, start, mid - 1);
    root->right = toTree(sorted_data, mid + 1, end);

    return root;
}

void release(node *root)
{
    if (!root)
        return;

    release(root->left);
    release(root->right);
    delete root;
    root = nullptr;
}

void inorderTraversal(node *root, int arr[], int &index)
{
    if (!root)
        return;
    inorderTraversal(root->left, arr, index);
    arr[index++] = root->data;
    inorderTraversal(root->right, arr, index);
}

size_t toArray(node *root, int *output)
{
    int size = 0;
    if (!root)
        return 0;
    int height = 0;
    node *temp = root;
    while (temp)
    {
        height++;
        temp = temp->left;
    }
    size = (1 << height) - 1;
    int index = 0;
    inorderTraversal(root, output, index);

    return size;
}

void printTree(node *root)
{
    if (root == nullptr)
        return;
    std::cout << root->data << " ";
    printTree(root->left);
    printTree(root->right);
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    node *root = toTree(arr, 0, n - 1);
    std::cout << "Print Traversal of constructed BST\n";
    printTree(root);
    std::cout << std::endl;

    int *result = (int *)malloc(sizeof(int) * 7);
    size_t size = toArray(root, result);
    for (size_t i = 0; i < size; i++)
    {
        std::cout << result[i] << " ";
    }
    std::cout << "\nSize of array: " << size << std::endl;

    return 0;
}