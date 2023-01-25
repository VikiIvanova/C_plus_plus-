#include "MatrixGraph/matrixGraph.hpp"
#include <queue>
#include <iostream>
#include <list>

using vertex_t = MatrixGraph::vertex_t;
using weight_t = MatrixGraph::weight_t;

bool relax(std::vector<weight_t> &distance, const MatrixGraph &g, vertex_t reached, vertex_t currentVertex)
{
    if (distance[reached] > distance[currentVertex] + g.getWeight(currentVertex, reached))
    {
        distance[reached] = distance[currentVertex] + g.getWeight(currentVertex, reached);
        return true;
    }
    return false;
}

// Намиране на най-късия път между два върха
int Dijkstra(const MatrixGraph &g, vertex_t start, vertex_t end)
{
    std::vector<vertex_t> parent(g.vertexCount(), -1);
    std::vector<weight_t> distances(g.vertexCount(), INT_MAX);

    struct VertexDistancePair
    {
        vertex_t vertex;
        weight_t distanceFromStart;

        bool operator<(const VertexDistancePair &other) const
        {
            return distanceFromStart > other.distanceFromStart;
        }
    };
    std::priority_queue<VertexDistancePair> q;

    distances[start] = 0;
    q.push({start, 0});

    while (!q.empty())
    {
        auto currentPair = q.top();
        q.pop();

        if (currentPair.vertex == end)
        {
            auto currentVertex = currentPair.vertex;

            std::list<vertex_t> path;

            while (currentVertex != start)
            {
                path.insert(path.begin(), currentVertex);
                currentVertex = parent[currentVertex];
            }
            path.insert(path.begin(), start);
            for (const auto &v : path)
                std::cout << v << std::endl;

            return distances[currentPair.vertex];
        }
        const auto &adjacent = g.adjacent(currentPair.vertex);
        for (auto reached : adjacent)
        {
            if (relax(distances, g, reached, currentPair.vertex))
            {
                parent[reached] = currentPair.vertex;
                q.push({reached, distances[reached]});
            }
        }
    }
    return INT_MAX;
}

int main()
{
    MatrixGraph g(8);

    g.addEdge(0, 1, 23);
    g.addEdge(0, 2, 74);
    g.addEdge(0, 3, 24);

    g.addEdge(1, 2, 35);
    g.addEdge(1, 4, 23);

    g.addEdge(2, 4, 24);
    g.addEdge(2, 3, 26);

    g.addEdge(3, 6, 32);

    g.addEdge(4, 5, 51);
    g.addEdge(4, 7, 17);

    g.addEdge(5, 7, 15);

    g.addEdge(6, 7, 32);

    int sp = Dijkstra(g, 0, 7);

    std::cout << std::endl
              << sp;
}
/*
Функцията връща най - късия път между start и end.
За да имаме този път ни трябва масив, в който ще пазим предшествениците. Този масив наричаме parent.
Ако имаме път 1 3 7, то
parent[1] = -1
parent[3] = 1
parent[7] = 3
Също така в масивът distances ще записваме локално колко е цената на най - късия път от старта,
открит до момента. Нека v e връх. Сега знаем, че distances[v] e дължината на най - късия път,
който сме намерили до момента. Тоест, има някакъв път s -> v.
Нека u e наследник на v. Знаем, че в distances[u] rма дължината на най - късия път, който сме открили до момента.
Има два начина да стигнем до u. Първият начин е s -> u (пътят, чиято стойност е записана във distances[u].
Забележете, че ако такъв път не е открит, фактът, че стойността е INT_MAX отново води до коректно изпълнение).
Вторият начин е s -> v -> u.
Възможно ли е да сме намерили по - лек път от s -> u? Нека проверим.
Тази проверка е отговорност на функцията relax:
Създаваме приоритетна опашка в която ще държим наредени двойки от типа (връх, тегло на най - къс път).
Всеки път от тази опашка ще вадим върхът с най - лек път. Затова съзваме структурата, представляваща двойка.
В приоритетната опашка пътят от старта до върха ще представлява приоритета на върха.
Оригиналният алгоритъм зарежда в приоритетната опашка веднага всички върхове и ъпдейтва
ключовете им директно в опашката чрез функцията decrease-key.
В началото всички ключове без началния са INT_MAX и след това постепенно се прилага decrease key всеки път когато открием по - кратък път. Тук приемаме друг подход, постепенно добавяме върхове в опашката, понеже std::priority_queue не поддържа decrease key. Това ще доведе до добавяне на върха няколко пъти в опашката но с различни ключове (всеки път когато намерим по - къс път). Това обаче не прави алгоритъма некоректен, просто върти малко повече.
Сега, докато има елементи в опашката вземаме най - лекия връх v (този с минимален ключ т.е. с най - малък открит път от старта до него).
За всеки негов съсед u, ако можем да го релаксираме го добавяме в опашката с разстоянието, което сме намерили.
Когато върхът, който извадим от опашката е end в distances[end] e записан най - късия път от началото до end.
Това твърдение също не е очевидно, но е вярно.
Та, когато извадим end от опашката ни остава само да възстановим пътя и да върнем неговата стойност.
Извеждаме го на стандартния изход, понеже това е примерен код. След това връщаме и самата дължина.
Използваме std::list понеже добавянето в началото е бързо, но със същия успех бихме могли да добавяме
в края на вектор примерно и да го обърнем след това.
Ако искаме най - късите пътища от s до всички достижими върхове, просто ще изчакаме алгоритъма да приключи.
След това ще върнем distances и parent за да можем да възстановим пътя за всеки връх.
Сложността на представената версия на Dijkstra е O(|E|log(|E|)).
Сложността на оригиналната Dijkstra реализирана с binary heap е O(|V|log|V| + |E|log|V|)
|V|*log(|V|) - в началото добавяме |V| елемента в приоритетната опашка. Всяко добавяне е log(|V|) време
|E|log|V| - Можем да имаме |E| операции decrease key (ако релаксираме за всяко ребро). Всеки decrease-key е log|V|.
С изтънчени структури от данни Dijkstra може да стане и по - бърз асимптотично.
*/