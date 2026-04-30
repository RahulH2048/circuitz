#pragma once
#include <unordered_map>

class Circuit {
    private:

    struct Element
    {
        double voltage;
        double current;
        double resistance;
        int node_pos;
        int node_neg;
    };

    enum TokenType
    {
        EDGE_ID,
        VOLTAGE,
        CURRENT,
        RESISTANCE,
        NODE_POS,
        NODE_NEG
    };

    std::unordered_map<int, Element> element_list;

    public:

    void load(std::string file_path);

    bool verifyKCL();

    bool verifyKVL();
};
