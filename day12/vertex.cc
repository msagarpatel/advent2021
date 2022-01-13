#include "vertex.h"
#include <cctype>

Vertex::Vertex(std::string name) : name(name) {}

bool operator<(const Vertex &lhs, const Vertex &rhs) {
	return lhs.name < rhs.name;
}

bool Vertex::isBig() const {
	return isupper(name.front());
}

bool Vertex::isSentinel() const {
	return name == "start" || name == "end";
}

bool operator==(const Vertex &lhs, const std::string &rhs) {
	return lhs.name == rhs;
}
