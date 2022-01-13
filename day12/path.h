#ifndef ADVENT2021_PATH_H
#define ADVENT2021_PATH_H

#include "vertex.h"
#include <map>

class Path {
public:
	Path(Vertex lastVisited);
	Path(const Path& p, Vertex last_visited);
	Vertex last_visited;
	std::map<Vertex,bool> visited;
};

#endif //ADVENT2021_PATH_H
