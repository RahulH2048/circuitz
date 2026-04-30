#include <fstream>
#include <sstream>
#include <string>

#include "circuit.h"

#define ELEMENT_MEMBER_COUNT 6

void Circuit::load(std::string file_path)
{
    std::ifstream input_stream(file_path);
    std::string buffer;

    while(std::getline(input_stream, buffer))
    {
        std::stringstream buffer_stream(buffer);

        std::string token;

        int token_index = 0;

        int element_id;

        Element element;

        while(std::getline(buffer_stream, token, ','))
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

                    element.node_neg = std::stoi(token);
                    break;

                case TokenType::NODE_NEG:

                    element.node_pos = std::stoi(token);
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
    }

    return;
}

bool Circuit::verifyKCL()
{
    return false;
}

bool Circuit::verifyKVL()
{
    return false;
}
