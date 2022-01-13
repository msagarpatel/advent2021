#include "path.h"

Path::Path(Vertex lastVisited) : last_visited(lastVisited) {
	visited[lastVisited] = true;
}

Path::Path(const Path &p, Vertex last_visited) :
		last_visited(last_visited),
		visited(p.visited) {
	visited[last_visited] = true;
}
