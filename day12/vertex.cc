#include "vertex.h"
#include <cctype>

Vertex::Vertex(std::string name) : name(name) {}

bool operator<(const Vertex &lhs, const Vertex &rhs) {
	return lhs.name < rhs.name;
}

bool Vertex::isBig() const {
	return isupper(name.front());
}

bool operator==(const Vertex &lhs, const std::string &rhs) {
	return lhs.name == rhs;
}
