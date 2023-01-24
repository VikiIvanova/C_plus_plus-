/*
 Ориентиран тегловен граф представен чрез матрица на съседство.
 Плюсове:
 * Лесна имплементация
 * Проверка за ребро, премахване на ребро, добавяне на ребро са О(1)
 Минуси:
 * Паметта винаги е О(|V|^ 2)
 * Намирането на предшественици(наследници) или в неориентирания случай на съседи отнема О(|V|) време.
 
  weight_t => тип, чрез който представяме тежест
  vertex_t => тип, чрез който представяме връх
*/

#ifndef MATRIXGRAPH_HPP
#define MATRIXGRAPH_HPP

#include <iostream>
#include <vector>
#include <cstddef>

class MatrixGraph
{
    public:
    using vertex_t = unsigned int;
    using weight_t = unsigned int;

    private:
    std::vector<std::vector<weight_t>> data;

    public:
    MatrixGraph(size_t);

    void addVertex();
    void removeVertex(vertex_t);

    void addDirectedEdge(vertex_t from, vertex_t to, weight_t w);
    void addEdge(vertex_t from, vertex_t to, weight_t w);
    void removeEdge(vertex_t from, vertex_t to);

    bool validVertex(vertex_t) const;
    weight_t getWeight(vertex_t, vertex_t) const;

    std::vector<vertex_t> getSuccessors(vertex_t) const;
    std::vector<vertex_t> getPredecessors(vertex_t) const;

    std::vector<vertex_t> adjacent(vertex_t) const;
    bool adjacent(vertex_t from, vertex_t to) const;
    size_t vertexCount() const;
};

#endif