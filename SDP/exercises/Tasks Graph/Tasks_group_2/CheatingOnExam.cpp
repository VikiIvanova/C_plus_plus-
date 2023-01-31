/*Интегралчо има изпит по СДП и неговата група е от N
студента(включително и него). Той знае кой на кого има възможност
да подскаже и измежду тях за кои е безопасно и за кои - не.
Той си харесва студентката Снежанка и иска да ѝ подскаже по
възможно най-безопасният начин. Понеже Интегралчо си е решил
задачите в първите 20 мин от изпита, сега иска да напише
програма, която по дадени студенти X(Интегралчо) и Y(Снежанка),
да се изчисли възможно най-безопасният “път” ( по брой опасни
директни подсказвания). Помогнете му да напише този алгоритъм*/

#include <iostream>
#include <list>
#include <vector>
#include <set>
#include <climits>

#define INF INT_MAX
using Edge = std::pair<int, int>;
using Vertex = std::list<Edge>;

class Graph
{
    int V;
    std::vector<Vertex> adj;

    public:
    Graph(int V): V(V)
    {
        for(int i = 0; i < V; i++)
            adj.push_back(Vertex());
    }
    void addEdge(int u, int v, int w);
    void shortestPath(int s);
};

void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(std::make_pair(v, w));
    adj[v].push_back(std::make_pair(u, w));
}

void Graph::shortestPath(int src)
{
    std::set<int> setds;
    std::vector<int> dist(V, INF);

    setds.insert(src);
    dist[src] = 0;

    while(!setds.empty())
    {
        int u = *(setds.begin());
        setds.erase(setds.begin());
        for(const Edge& e : adj[u])
        {
            int v = e.first;
            int weight = e.second;
            if(dist[v] > dist[u] + weight)
            {
                if(dist[v] != INF)
                   setds.erase(v);
                
                dist[v] = dist[u] + weight;
                setds.insert(v);
            }
        }
    }
    std::cout << "Vertex Distance from Source\n";
    for(int i = 0; i < V; ++i)
       std::cout << i << "\t\t" << dist[i] << std::endl;
}

int main() 
{
	int V = 9; 
	Graph g(V); 

	g.addEdge(0, 1, 1); 
	g.addEdge(0, 7, 1); 
	g.addEdge(1, 2, 1); 
	g.addEdge(1, 7, 0); 
	g.addEdge(2, 3, 1); 
	g.addEdge(2, 8, 0); 
	g.addEdge(2, 5, 0); 
	g.addEdge(3, 4, 1); 
	g.addEdge(3, 5, 0); 
	g.addEdge(4, 5, 0); 
	g.addEdge(5, 6, 1); 
	g.addEdge(6, 7, 0); 
	g.addEdge(6, 8, 1); 
	g.addEdge(7, 8, 1); 

	g.shortestPath(0); 

	return 0; 
} 
