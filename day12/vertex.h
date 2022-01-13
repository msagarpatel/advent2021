#ifndef ADVENT2021_VERTEX_H
#define ADVENT2021_VERTEX_H

// This class is not very useful. It's just a wrapper around std::string right now. Maybe part 2
// will introduce some complexity?

#include <vector>
#include <string>

class Vertex {
public:
	std::string name;
	Vertex(std::string name);
	friend bool operator<(const Vertex &lhs, const Vertex &rhs);
	friend bool operator==(const Vertex &lhs, const std::string &rhs);
	bool isBig() const;
	bool isSentinel() const;
};

#endif //ADVENT2021_VERTEX_H
