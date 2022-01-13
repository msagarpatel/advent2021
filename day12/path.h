#ifndef ADVENT2021_PATH_H
#define ADVENT2021_PATH_H

#include "vertex.h"
#include <map>

class Path {
public:
	Path(Vertex lastVisited);
	Path(const Path& p, Vertex last_visited);
	Path(const Path& p, Vertex last_visited, bool _visitedSmallTwice);
	Vertex last_visited;
	std::map<Vertex,bool> visited;
	bool visitedSmallTwice() const;

private:
	bool _visitedSmallTwice;
};

#endif //ADVENT2021_PATH_H
