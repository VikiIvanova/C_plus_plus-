#include <iostream>
/* Задача 1: Нека имаме двоично дърво от цели числа представено или като обект от клас (например
BinTree), или с указател към корена на дървото. Да се реализира външна функция, която приема едно
такова дърво и пресмята сумата на елементите от четните нива, които имат само ляв наследник.
Забележка: приемаме, че коренът е на ниво 0 и това е четно ниво.*/

struct BinTree
{
    int data;
    BinTree *left;
    BinTree *right;
};

int sumLeftLeaves(BinTree *root, int level)
{
    if (!root)
        return 0;
    if (level % 2 == 0 && root->left != nullptr && root->right == nullptr)
    {
        return root->data;
    }
    return sumLeftLeaves(root->left, level + 1) + sumLeftLeaves(root->right, level + 1);
}

/*Задача 2. Нека имаме ориентиран граф от символи g и двоично дърво от символи t. Множеството от
елементите на двете структури е едно и също, като в рамките на всяка една от структурите символите са уникални.
Напишете функция, която проверява дали съществува път от корена на дървото до листо, който да
отговаря на път в графа и ако има такъв го извежда (Заб.: достатъчно е да изведете само един път, който отговаря на условието).
Пример:
В случая пътят a - f - c - h отговаря на условието.*/



int main()
{
    // task 1
    BinTree *tree = new BinTree{4,
                                new BinTree{2, new BinTree{1, new BinTree{3, nullptr, nullptr}, nullptr}, nullptr},
                                new BinTree{6, new BinTree{5, nullptr, nullptr}, nullptr}};

    int result = sumLeftLeaves(tree, 0);
    std::cout << "Sum of elements at even levels with only a left child: " << result << std::endl;
    return 0;
}
