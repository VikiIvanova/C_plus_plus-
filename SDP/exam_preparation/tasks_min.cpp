/*Задача 1. Нека имаме двоично дърво от цели числа представено или като обект от клас (например
BinTree), или с указател към корена на дървото. Да се реализира външна функция, която приема едно
такова дърво и пресмята сумата на елементите от четните нива, които имат само ляв наследник.
Забележка: приемаме, че коренът е на ниво 0 и това е четно ниво.*/
#include <iostream>
struct BinTreeNode
{
    int data;
    BinTreeNode* left;
    BinTreeNode* right;
    BinTreeNode(int data, BinTreeNode* left = nullptr, BinTreeNode* right = nullptr):data(data), left(left), right(right) {}
};

int sumEvenHelper(BinTreeNode* root, int sum, int level)
{
    if(root == nullptr)
       return 0;
    
    if(level % 2 == 0 && root->left && !root->right)
       return sum += root->data;
    
    return sumEvenHelper(root->left, sum, level + 1) + 
           sumEvenHelper(root->right, sum, level + 1);
    

}

int sumEvenLevelWithLeft(BinTreeNode* root)
{
   return sumEvenHelper(root, 0, 0);
}

// int main()
// {
//     BinTreeNode* tree = new BinTreeNode(1, new BinTreeNode(2, new BinTreeNode(4, new BinTreeNode(5))), 
//                                         new BinTreeNode(3, new BinTreeNode(6, new BinTreeNode(8)), new BinTreeNode(7, new BinTreeNode(9))));
    
//     int sum = sumEvenLevelWithLeft(tree);
//     std::cout << sum << std::endl;
//     return 0;
// }

/*Задача 2. Нека имаме ориентиран граф от символи g и двоично дърво от символи t. Множеството от
елементите на двете структури е едно и също, като в рамките на всяка една от структурите символите са
уникални.
Напишете функция, която проверява дали съществува път от корена на дървото до листо, който да
отговаря на път в графа и ако има такъв го извежда (Заб.: достатъчно е да изведете само един път, който
отговаря на условието).
Пример:
В случая пътят a - f - c - h отговаря на условието*/
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

bool match_path(const std::string &tree_path, const std::unordered_set<std::string> &graph_paths) {
    return graph_paths.count(tree_path) > 0;
}

void find_path(const std::vector<std::string> &tree, int node, std::string path, 
               const std::unordered_set<std::string> &graph_paths, std::string &result) {
    if (node >= tree.size()) {
        if (match_path(path, graph_paths)) {
            result = path;
        }
        return;
    }
    find_path(tree, node * 2 + 1, path + tree[node], graph_paths, result);
    find_path(tree, node * 2 + 2, path + tree[node], graph_paths, result);
}

// int main() {
//     std::vector<std::string> tree = {"t", "g", "t", "t", "g", "t", "g"};
//     std::unordered_set<std::string> graph_paths = {"tg", "gt"};
//     std::string result;
//     find_path(tree, 0, "", graph_paths, result);
//     if (!result.empty()) {
//         std::cout << "Found matching path: " << result << std::endl;
//     } else {
//         std::cout << "No matching path found" << std::endl;
//     }
//     return 0;
// }

/*Задача 3. Създайте (чрез включване) двоично наредено дърво от интервали от числа ([a, b], a ≤ b).
Наредбата в дървото да бъде по средната стойност на интервала.
Намерете максималния интервал от дървото (спрямо описаната наредба в дървото), чието сечение с
всеки един от другите интервали интервали на двоичното наредено дърво не е празно или върнете [0,0],
ако такъв не съществува. Използвайте наредеността на дървото, където е удачно.
Заб.: можете да използвате реализация на двоично наредено дърво или ако предпочитате да използвате
указател към корен на дървото.*/

#include <iostream>
#include <vector>

struct Interval {
  int start, end;
};

struct Node {
  Interval interval;
  int maxEnd;
  Node *left, *right;
};

Node* newNode(Interval i) {
  Node *temp = new Node;
  temp->interval = i;
  temp->maxEnd = i.end;
  temp->left = temp->right = nullptr;
  return temp;
}

Node* insert(Node* root, Interval i) {
  if (!root) return newNode(i);

  int mid = (i.start + i.end) / 2;

  if (mid < root->interval.start)
    root->left = insert(root->left, i);
  else
    root->right = insert(root->right, i);

    root->maxEnd = std::max(root->maxEnd, i.end);

  return root;
}

bool doOVerlap(Interval a, Interval b) {
  if (a.start <= b.end && b.start <= a.end) 
      return true;
  return false;
}

Interval maxInterval(Node* root) {
  if (!root) return {0, 0};

  Interval result = root->interval;

  Interval leftResult = maxInterval(root->left);
  if (doOVerlap(leftResult, result))
    result = { std::min(leftResult.start, result.start), std::max(leftResult.end, result.end) };

  Interval rightResult = maxInterval(root->right);
  if (doOVerlap(rightResult, result))
    result = { std::min(rightResult.start, result.start), std::max(rightResult.end, result.end) };

  return result;
}

// int main() {
//   std::vector<Interval> intervals = {{1, 5}, {3, 7}, {2, 6}, {10, 15}, {5, 6}, {4, 100}};

//   Node *root = nullptr;
//   for (auto i : intervals)
//     root = insert(root, i);

//   Interval result = maxInterval(root);
//   std::cout << "[" << result.start << ", " << result.end << "]" << std::endl;

//   return 0;
// }

/*1. Да се реализира абстрактен клас TrainStation, който описва ЖП гара и поддържа
следните операции:
• bool link([попълнете правилния тип] station) – установява връзка между
дадената гара и друга гара station. Създадената връзка трябва да е двупосочна.
Операцията не е възможна, ако поне една от двете гари не може да бъде свързана с
повече гари. В този случай методът връща false.
• [попълнете правилния тип] getLinkedStation(int i) – връща i-тата поред гара
(при избрана от вас подредба), към която дадената гара е свързана, и nullptr, ако
дадената гара е свързана с по-малък брой гари.
2. Да се рeализират наследници Terminal и Hub на TrainStation. За Terminal е
характерно, че гарата може да е свързана най-много с още една гара. За Hub е характерно, че
гарата може да е свързана с максимум 50 други гари.
3. Да се реализира функция bool connected([попълнете правилния тип] s1, [попълнете
правилния тип] s2), която проверява дали има връзка (пряка или косвена) между двете гари
s1 и s2.
4. Да се реализира подходяща функция serialize, сериализираща цяла мрежа от гари, т.е.
функция, която да съхрани информацията за гарите и техните връзки във файл по избор. Не се
изисква реализация на функция за четене на записана мрежа от гари, но избраният формат за
сериализация трябва да позволява така възможност (т.е. представянето да е пълно и
еднозначно).*/

#include <iostream>
#include <vector>
#include <list>
#include <queue>

class TrainStation
{
private:
    std::vector<TrainStation*> adj;
    int numberStation;
    size_t capacity;

public:
    TrainStation(unsigned int numberStation, size_t capacity);
    bool link(TrainStation station);
    unsigned int getLinkedStation(int i, std::vector<TrainStation> stations);
    int getNumberStation();
    std::vector<TrainStation*> getAdj();
};

TrainStation::TrainStation(unsigned int numberStation, size_t capacity) : adj(0, 0), numberStation(numberStation), capacity(capacity) {}

bool TrainStation::link(TrainStation station)
{
    if (this->adj.size() < this->capacity && station.adj.size() < station.capacity)
    {
        this->adj.push_back(&station);
        station.adj.push_back(this);
        return true;
    }
    return false;
}

unsigned int TrainStation::getLinkedStation(int i, std::vector<TrainStation> stations)
{
    std::vector<bool> visited(stations.size(), false);

    std::queue<TrainStation> queue;
    queue.push(stations[0]);

    std::vector<unsigned int> result;
    while (!queue.empty())
    {
        TrainStation current = queue.front();
        queue.pop();

        if (visited[current.numberStation])
            continue;
        visited[current.numberStation] = true;
        result.push_back(current.numberStation);

        for (auto& currentStation : current.adj)
        {
            if (!visited[currentStation->numberStation])
                queue.push(*currentStation);
        }
    }
    std::cout << result[i] << std::endl;
}

class Hub : public TrainStation
{
    size_t capacity = 50;
};

class Terminal : public TrainStation
{
    size_t capacity = 50;
};

int TrainStation::getNumberStation()
{
    return numberStation;
}

std::vector<TrainStation*> TrainStation::getAdj()
{
   return adj;
}

bool connected(TrainStation s1, TrainStation s2, size_t countStations)
{
    std::vector<bool> visited(countStations, false);

    std::queue<TrainStation> queue;
    queue.push(s1);

    while (!queue.empty())
    {
        TrainStation current = queue.front();
        queue.pop();

        if (visited[current.getNumberStation()])
              continue;
        visited[current.getNumberStation()] = true;
        if(current.getNumberStation() == s2.getNumberStation())
        {
            std::cout << "There is a path between s1 and s2!" << std::endl;
            return true;
        }

        for (auto& currentStation : current.getAdj())
        {
            if (!visited[currentStation->getNumberStation()])
                queue.push(*currentStation);
        }
    }
    return false;
}