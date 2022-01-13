#include "path.h"

Path::Path(Vertex lastVisited) : last_visited(lastVisited), _visitedSmallTwice(false) {
	visited[lastVisited] = true;
}

Path::Path(const Path &p, Vertex last_visited) :
		last_visited(last_visited),
		visited(p.visited),
		_visitedSmallTwice(p._visitedSmallTwice) {
	visited[last_visited] = true;
}

Path::Path(const Path &p, Vertex last_visited, bool _visitedSmallTwice) :
		last_visited(last_visited),
		visited(p.visited),
		_visitedSmallTwice(_visitedSmallTwice) {
	visited[last_visited] = true;
}

bool Path::visitedSmallTwice() const {
	return _visitedSmallTwice;
}
