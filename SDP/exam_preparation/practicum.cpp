/*Да се дефинира подходяща структура TreeNode,
описваща възел в двоично дърво, съдържащо цели числа.

Да се напише функция findSubtree, която по дадено е двоично дърво T, съдържащо цели числа,
връща такова поддърво на T, в което сумата от елементите с четни стойности е равна на сумата
от елементите с нечетни стойности. Ако такова дърво няма, функцията да връща празно дърво.

Да се дефинира функция, която записва двоично дърво във файл по подходящ начин.
Не се изисква реализация на функция за четене на записано дърво,
но избраният формат за извеждане трябва да позволява така възможност (т.е. представянето да е пълно и еднозначно).

Да се подготви примерна програма, която построява произволно примерно двоично дърво с поне 20 елемента,
което е балансирано. Да се подготвят подходящи помощни функции за построяване на дървото.
Горните функции да се демонстрират в примерната програма.*/
#include <vector>
#include <iostream>
#include <fstream>

struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;
    TreeNode(const int &data, TreeNode *left = nullptr, TreeNode *right = nullptr)
        : data(data), left(left), right(right) {}
};

TreeNode *create(int data, TreeNode *left = nullptr, TreeNode *right = nullptr)
{
    return new TreeNode{data, left, right};
}

void deleteTree(TreeNode *&root)
{
    if (root)
    {
        deleteTree(root->left);
        deleteTree(root->right);
        delete (root);
        root = nullptr;
    }
}
void print(TreeNode *root)
{
    if (nullptr == root)
    {
        return;
    }
    std::cout << root->data << std::endl;
    print(root->left);
    print(root->right);
}

int sumOfEvenValues(TreeNode *root)
{
    if (root == nullptr)
    {
        return 0;
    }

    int sum = 0;
    if (root->data % 2 == 0)
    {
        sum += root->data;
    }

    return sum + sumOfEvenValues(root->left) + sumOfEvenValues(root->right);
}

int sumOfOddValues(TreeNode *root)
{
    if (root == nullptr)
    {
        return 0;
    }

    int sum = 0;
    if (root->data % 2 != 0)
    {
        sum += root->data;
    }

    return sum + sumOfOddValues(root->left) + sumOfOddValues(root->right);
}

TreeNode *findSubtree(TreeNode *root)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    int sumEven = sumOfEvenValues(root);
    int sumOdd = sumOfOddValues(root);

    if (sumEven == sumOdd)
    {
        return root;
    }
    TreeNode *left = findSubtree(root->left);
    TreeNode *right = findSubtree(root->right);

    if (left != nullptr)
    {
        return left;
    }
    if (right != nullptr)
    {
        return right;
    }

    return nullptr;
}

void writeTree(TreeNode *root, std::ofstream &out)
{
    if (!root)
        return;

    out.write((char *)&root->data, sizeof(root->data));

    bool hasLeft = root->left != nullptr;
    out.write((char *)&hasLeft, sizeof(hasLeft));
    if (hasLeft)
        writeTree(root->left, out);

    bool hasRight = root->right != nullptr;
    out.write((char *)&hasRight, sizeof(hasRight));
    if (hasRight)
        writeTree(root->right, out);
}

int main()
{
    TreeNode *root = create(7, create(2, create(5, create(1, create(8), create(12)), create(2, create(8, create(1), create(3)), create(6, create(5), create(7)))), create(25)),
                            create(3, create(1), create(13)));
    std::cout << "Print tree: " << std::endl;
    print(root);
    std::cout << std::endl;
    TreeNode *root2 = create(1, create(3), create(4));

    TreeNode *rootResult = findSubtree(root);
    std::cout << "Print result tree: " << std::endl;
    print(rootResult);

    std::ofstream out("tree.bin", std::ios::binary);
    writeTree(root, out);
    out.close();

    deleteTree(root);
    deleteTree(root2);
    deleteTree(rootResult);

    return 0;
}