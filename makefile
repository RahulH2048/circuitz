build/circuitz: main.cpp graph.cpp circuit.cpp
	clang++ -Wall -std=c++20 main.cpp graph.cpp circuit.cpp -o build/circuitz

build/circuitz-debug: main.cpp graph.cpp circuit.cpp
	clang++ -Wall -g -std=c++20 main.cpp graph.cpp circuit.cpp -o build/circuitz-debug

clean:
	rm circuitz
