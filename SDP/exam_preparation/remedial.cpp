/*1. Да се реализира абстрактен клас TrainStation, който описва ЖП гара и поддържа следните операции:
bool link([попълнете правилния тип] station) – установява връзка между дадената гара и друга гара station.
Създадената връзка трябва да е двупосочна.
Операцията не е възможна, ако поне една от двете гари не може да бъде свързана с повече гари.
В този случай методът връща false.
[попълнете правилния тип] getLinkedStation(int i) – връща i-тата поред гара (при избрана от вас подредба),
към която дадената гара е свързана, и nullptr, ако дадената гара е свързана с по-малък брой гари.

2. Да се рeализират наследници Terminal и Hub на TrainStation.
За Terminal е характерно, че гарата може да е свързана най-много с още една гара.
За Hub е характерно, че гарата може да е свързана с максимум 50 други гари.

3. Да се реализира функция bool connected([попълнете правилния тип] s1, [попълнете правилния тип] s2),
която проверява дали има връзка (пряка или косвена) между двете гари s1 и s2.

4. Да се реализира подходяща функция serialize, сериализираща цяла мрежа от гари.
Не се изисква реализация на функция за четене на записана мрежа от гари,
но избраният формат за сериализация трябва да позволява така възможност (т.е. представянето да е пълно и еднозначно).*/

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
