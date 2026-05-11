#include "circuit.h"

int main()
{
    Circuit circuit;

    circuit.load("input/c1");

    circuit.satisfiesKVL();

    return 0;
}
