#include <unordered_map>
#include <vector>
#include <stack>

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

    std::vector<unsigned int> find_cycle(unsigned int start_vertex, unsigned int end_vertex, unsigned int cycle_edge)
    {
        std::stack<unsigned int> frontier;
        std::unordered_map<unsigned int, Vertex> traversal_map;
        frontier.push(start_vertex);

        unsigned int prev_vertex = start_vertex;

        // DFS while memorising which edge takes you back to the start_vertex
        while (!frontier.empty())
        {
            unsigned int current_vertex = frontier.top();
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

        std::vector<unsigned int> path_edge_list;

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

public:
    // Adds an edge to the graph such that it remains a tree
    // Edges that would make cycles are put into a seperate list
    // Graph is stored as an adjacency list
    void add_edge(unsigned int edge_id, unsigned int vertex_1, unsigned int vertex_2)
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
    std::vector<std::vector<unsigned int>> cycles()
    {
        std::vector<std::vector<unsigned int>> cycle_list;

        for (Edge edge : cycle_edge_list)
        {
            cycle_list.push_back(find_cycle(edge.vertex_1, edge.vertex_2, edge.id));
        }

        return cycle_list;
    }

    // Return adjacency list for entire graph (incuding cycle edges)
    const std::unordered_map<unsigned int, std::vector<Vertex>> adjacency_list()
    {
        std::unordered_map<unsigned int, std::vector<Vertex>> adjacency_list = graph;

        for (Edge edge : cycle_edge_list)
        {
            adjacency_list.at(edge.vertex_1).push_back(Vertex{edge.id, edge.vertex_2});
            adjacency_list.at(edge.vertex_2).push_back(Vertex{edge.id, edge.vertex_1});
        }

        return adjacency_list;
    }
};

int main()
{
    Graph graph;

    graph.add_edge(0, 'A', 'B');
    graph.add_edge(1, 'A', 'B');
    graph.add_edge(2, 'A', 'E');
    graph.add_edge(3, 'B', 'E');
    graph.add_edge(4, 'B', 'C');
    graph.add_edge(5, 'B', 'D');

    std::vector<std::vector<unsigned int>> cycles = graph.cycles();

    std::unordered_map<unsigned int, std::vector<Graph::Vertex>> adjacency_list = graph.adjacency_list();

    return 0;
}
