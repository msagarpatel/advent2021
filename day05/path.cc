#include <sstream>
#include "path.h"

path::path(const std::string& line) : _begin(), _end() {
	uint tmp;
	std::stringstream ss(line);

	uint args = std::sscanf(line.c_str(), "%u,%u -> %u,%u", &_begin.first, &_begin.second,
	                  &_end.first, &_end.second);
	if (args != 4)
		throw std::length_error("path does not follow format: " + line);
}

std::pair<uint, uint> path::begin() {
	return _begin;
}

std::pair<uint, uint> path::end() {
	return _end;
}

uint path::max() {
	return std::max(std::max(_begin.first, _begin.second), std::max(_end.first, _end.second));
}
