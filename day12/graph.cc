#include <deque>
#include <string>
#include "graph.h"
#include "path.h"

Graph::Graph() {}

void Graph::insert_edge(const std::string& edge) {
	auto hyphen = edge.find("-");
	std::string v1 = edge.substr(0, hyphen);
	std::string v2 = edge.substr(hyphen+1);
	// use twice the memory with an adjacency list
	adjacency_list[v1].push_back(v2);
	adjacency_list[v2].push_back(v1);
}

int Graph::num_paths() {
	int count = 0;
	std::deque<Path> paths;
	paths.emplace_back(Vertex(std::string("start")));
	while (!paths.empty()) {
		auto path = paths.front();
		paths.pop_front();
		if (path.last_visited == "end") {
			count++;
			continue;
		}
		for (const auto& i : adjacency_list[path.last_visited]) {
			if (!path.visited[i] || i.isBig())
				paths.emplace_back(path, i);
		}
	}
	return count;
}

