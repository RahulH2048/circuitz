#include "graph.h"

#include <stack>
#include <unordered_map>
#include <vector>

std::vector<int> Graph::find_cycle(int start_vertex, int end_vertex, int cycle_edge)
{
    struct SearchState
    {
        int current_vertex;
        int prev_vertex;
    };

    std::stack<SearchState> frontier;
    std::unordered_map<int, Vertex> traversal_map;

    frontier.push(SearchState{start_vertex, start_vertex});

    // DFS while memorising which edge takes you back to the start_vertex
    while (!frontier.empty())
    {
        SearchState state = frontier.top();
        frontier.pop();

        if (state.current_vertex == end_vertex)
        {
            break;
        }

        for (Vertex vertex : graph.at(state.current_vertex))
        {
            if (vertex.id == state.prev_vertex)
            {
                continue;
            }

            frontier.push(SearchState{vertex.id, state.current_vertex});
            traversal_map.insert({vertex.id, Vertex{vertex.connecting_edge, state.current_vertex}});
        }
    }

    std::vector<int> path;

    // Backtracking starting from end_vertex
    // Follow the traversal map from end_vertex until start_vertex

    int current_vertex = end_vertex;

    while (current_vertex != start_vertex)
    {
        Vertex next_vertex = traversal_map.at(current_vertex);

        path.push_back(current_vertex);
        path.push_back(next_vertex.connecting_edge);

        current_vertex = next_vertex.id;
    }

    path.push_back(current_vertex);
    path.push_back(cycle_edge);

    return path;
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
