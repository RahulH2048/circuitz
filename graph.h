#pragma once
#include <unordered_map>
#include <vector>

class Graph
{
    public:

    struct Vertex
    {
        unsigned int connecting_edge;
        unsigned int id;
    };

    struct Edge
    {
        unsigned int id;
        unsigned int vertex_1;
        unsigned int vertex_2;
    };

    private:

    std::unordered_map<unsigned int, std::vector<Vertex>> graph;

    std::vector<Edge> cycle_edge_list;

    std::vector<unsigned int> find_cycle(unsigned int start_vertex, unsigned int end_vertex, unsigned int cycle_edge);

    public:

    void add_edge(unsigned int edge_id, unsigned int vertex_1, unsigned int vertex_2);

    const std::unordered_map<unsigned int, std::vector<Vertex>> adjacency_list();

    std::vector<std::vector<unsigned int>> cycles();

};
