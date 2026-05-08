#include "graph.h"

#include <stack>
#include <unordered_map>
#include <vector>

std::vector<int> Graph::find_cycle(int start_vertex, int end_vertex, int cycle_edge)
{
    std::stack<int> frontier;
    std::unordered_map<int, Vertex> traversal_map;
    frontier.push(start_vertex);

    int prev_vertex = start_vertex;

    // DFS while memorising which edge takes you back to the start_vertex
    while (!frontier.empty())
    {
        int current_vertex = frontier.top();
        frontier.pop();

        if (current_vertex == end_vertex)
        {
            break;
        }

        // when doing DFS through a tree every neighbour vertex will be new except for vertex we came from
        for (Vertex vertex : graph.at(current_vertex))
        {
            if (vertex.id == prev_vertex)
            {
                continue;
            }

            frontier.push(vertex.id);
            traversal_map.insert({vertex.id, Vertex{vertex.connecting_edge, current_vertex}});
        }

        prev_vertex = current_vertex;
    }

    std::vector<int> path_edge_list;

    // Backtracking starting from end_vertex
    // Follow the traversal map from end_vertex until start_vertex
    while (end_vertex != start_vertex)
    {
        Vertex current_vertex = traversal_map.at(end_vertex);

        path_edge_list.push_back(current_vertex.connecting_edge);

        end_vertex = current_vertex.id;
    }

    path_edge_list.push_back(cycle_edge);

    return path_edge_list;
}

void Graph::add_edge(int edge_id, int vertex_1, int vertex_2)
{
    if (graph.contains(vertex_1) && graph.contains(vertex_2))
    {
        cycle_edge_list.push_back(Edge{edge_id, vertex_1, vertex_2});
        return;
    }

    if (!graph.contains(vertex_1))
    {
        graph.insert({vertex_1, {}});
    }

    if (!graph.contains(vertex_2))
    {
        graph.insert({vertex_2, {}});
    }


    graph.at(vertex_1).push_back(Vertex{edge_id, vertex_2});
    graph.at(vertex_2).push_back(Vertex{edge_id, vertex_1});
}

// Returns all cycles in the graph
std::vector<std::vector<int>> Graph::cycles()
{
    std::vector<std::vector<int>> cycle_list;

    for (Edge edge : cycle_edge_list)
    {
        cycle_list.push_back(find_cycle(edge.vertex_1, edge.vertex_2, edge.id));
    }

    return cycle_list;
}

// Return adjacency list for entire graph (incuding cycle edges)
const std::unordered_map<int, std::vector<Graph::Vertex>> Graph::adjacency_list()
{
    std::unordered_map<int, std::vector<Vertex>> adjacency_list = graph;

    for (Edge edge : cycle_edge_list)
    {
        adjacency_list.at(edge.vertex_1).push_back(Vertex{edge.id, edge.vertex_2});
        adjacency_list.at(edge.vertex_2).push_back(Vertex{edge.id, edge.vertex_1});
    }

    return adjacency_list;
}
