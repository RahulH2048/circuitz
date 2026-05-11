#include "circuit.h"

#include <iostream>

int main(int argc, char *argv[])
{
    Circuit circuit;

    circuit.load(argv[1]);

    if (circuit.satisfiesKCL())
    {
        std::cout << "KCL: \u2714" << std::endl;
    }
    else
    {
        std::cout << "KCL \u2718" << std::endl;
    }

    if (circuit.satisfiesKVL())
    {
        std::cout << "KVL \u2714" << std::endl;
    }
    else
    {
        std::cout << "KVL \u2718" << std::endl;
    }

    return 0;
}
