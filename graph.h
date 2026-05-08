#pragma once
#include <unordered_map>
#include <vector>

class Graph
{
    public:

    struct Vertex
    {
        int connecting_edge;
        int id;
    };

    struct Edge
    {
        int id;
        int vertex_1;
        int vertex_2;
    };

    private:

    std::unordered_map<int, std::vector<Vertex>> graph;

    std::vector<Edge> cycle_edge_list;

    std::vector<int> find_cycle(int start_vertex, int end_vertex, int cycle_edge);

    public:

    void add_edge(int edge_id, int vertex_1, int vertex_2);

    const std::unordered_map<int, std::vector<Vertex>> adjacency_list();

    std::vector<std::vector<int>> cycles();

};
