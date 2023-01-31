#include <iostream>
#include <list>
#include <vector>
#include <set>

#define INF 0x3f3f3f3f

using Edge = std::pair<int, int>;
using Vertex = std::list<Edge>;

//This class represents a directed graph using adjancency list representation
class Graph
{
    int V;

    //In a weighted graph, we need to store vertex
    //and weight pair for every edge
    std::vector<Vertex> adj;

    public:
    Graph(int V): V(V)
    {
        for(int i = 0; i < V; ++i)
            adj.push_back(Vertex());
    }
    void addEdge(int u, int v, int w);

    //prints shortest path from s
    void shortestPath(int s);
};

void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(std::make_pair(v, w));
    adj[v].push_back(std::make_pair(u, w));
}

//Print shortest paths from src to all other vertices
void Graph::shortestPath(int src)
{
    //Create a set to store vertices that are being processed
    std::set<int> setds;

    //Create a vector for distances and initialize all
    //distances as infinite(INF)
    std::vector<int>dist(V, INF);

    //Insert source itself in Set and initialize its distance as 0.
    setds.insert(src);
    dist[src] = 0;

    //Looping till all shortest distance are finalized then setds will become empty
    while(!setds.empty())
    {
        //The fisrt vertex in Set is in minimum distance
        //vertex, extract it from set.
        int u = *(setds.begin());
        setds.erase(setds.begin());

        //vertex label is stored in second of pair(it has to be done 
        //this way to keep the vertices sorted distance(distance must be fisrt item in pair))
        for(const Edge& e: adj[u])
        {
            //Get vertex label and weight of current adjacent of u.
            int v = e.first;
            int weight = e.second;

            //If there is shorter path to v through u.
            if(dist[v] > dist[u] + weight)
            {
                /*If distance of v is not INF then it must be in
                our set, so removing it and inserting again
                with updated less distance.*/
                if(dist[v] != INF)
                   setds.erase(v);
                
                //Updating distance of v
                dist[v] = dist[u] + weight;
                setds.insert(v);
            }
        }
    }
    //Print shortest distances stored in dist[]
    std::cout << "Vertex Distance stored in dist[]";
    for(int i = 0; i < V; ++i)
        std::cout << i << "\t\t" << dist[i] << std::endl;
}

// Driver program to test methods of graph class 
int main() 
{ 
	// create the graph given in above fugure 
	int V = 9; 
	Graph g(V); 

	// making above shown graph 
	g.addEdge(0, 1, 4); 
	g.addEdge(0, 7, 8); 
	g.addEdge(1, 2, 8); 
	g.addEdge(1, 7, 11); 
	g.addEdge(2, 3, 7); 
	g.addEdge(2, 8, 2); 
	g.addEdge(2, 5, 4); 
	g.addEdge(3, 4, 9); 
	g.addEdge(3, 5, 14); 
	g.addEdge(4, 5, 10); 
	g.addEdge(5, 6, 2); 
	g.addEdge(6, 7, 1); 
	g.addEdge(6, 8, 6); 
	g.addEdge(7, 8, 7); 

	g.shortestPath(0); 

	return 0; 
}