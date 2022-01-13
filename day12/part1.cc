#include <iostream>
#include "graph.h"

// "Your goal is to find the number of distinct paths that start at start, end at end, and don't
// visit small caves more than once." --- I assume this means cycles between large caves are not
// possible.

int main() {
	// parse input into graph
	std::string edge;
	Graph g;
	while (std::cin >> edge)
		g.insert_edge(edge);

	// find the number of paths
	auto paths = g.num_paths();
	std::cout << "Paths = " << paths << std::endl;
	return EXIT_SUCCESS;
}
