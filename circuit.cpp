#include "circuit.h"

#include <fstream>
#include <sstream>
#include <string>

#define ELEMENT_MEMBER_COUNT 6

void Circuit::load(std::string file_path)
{
    std::ifstream input_stream(file_path);
    std::string buffer;

    while (std::getline(input_stream, buffer))
    {
        std::stringstream buffer_stream(buffer);
        std::string token;

        int token_index = 0;

        int element_id;
        Element element;

        while (std::getline(buffer_stream, token, ','))
        {
            switch (token_index)
            {
            case TokenType::EDGE_ID:

                element_id = std::stoi(token);
                break;

            case TokenType::VOLTAGE:

                element.voltage = std::stod(token);
                break;

            case TokenType::CURRENT:

                element.current = std::stod(token);
                break;

            case TokenType::RESISTANCE:

                element.resistance = std::stod(token);
                break;

            case TokenType::NODE_POS:

                element.node_pos = std::stoi(token);
                break;

            case TokenType::NODE_NEG:

                element.node_neg = std::stoi(token);
                break;

            default:
                return;
            }

            token_index++;
        }

        if (token_index < ELEMENT_MEMBER_COUNT - 1)
        {
            return;
        }

        element_list.insert({element_id, element});

        circuit_graph.add_edge(element_id, element.node_pos, element.node_neg);
    }
}

bool Circuit::satisfiesKCL()
{
    for (std::pair<int, std::vector<Graph::Vertex>> pair : circuit_graph.adjacency_list())
    {
        double net_current = 0;

        for (Graph::Vertex vertex : pair.second)
        {
            double element_current = element_list.at(vertex.connecting_edge).current;

            int polarity = element_list.at(vertex.connecting_edge).node_pos == vertex.id ? -1 : 1;
            net_current += (element_current * polarity);
        }

        if (net_current != 0)
        {
            return false;
        }
    }

    return true;
}

bool Circuit::satisfiesKVL()
{
    for (std::vector<int> independent_loop : circuit_graph.cycles())
    {
        double net_voltage = 0;

        for (int i = 0; i < independent_loop.size(); i += 2)
        {
            int node = independent_loop[i];
            int element = independent_loop[i + 1];

            int polarity = element_list.at(element).node_pos == node ? 1 : -1;

            net_voltage += element_list.at(element).voltage * polarity;
        }

        if (net_voltage != 0)
        {
            return false;
        }
    }

    return true;
}
