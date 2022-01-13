#ifndef ADVENT2021_GRAPH_H
#define ADVENT2021_GRAPH_H

#include "vertex.h"
#include <map>
#include <vector>

class Graph {
private:
	// list of vertices and their connections
	std::map<Vertex,std::vector<Vertex>> adjacency_list;
public:
	Graph();
	void insert_edge(const std::string &edge);
	int num_paths();
	// make two separate functions for backward compatibility with part 1.
	int num_paths_part2();
};


#endif //ADVENT2021_GRAPH_H
