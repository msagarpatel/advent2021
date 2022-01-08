#ifndef ADVENT2021_PATH_H
#define ADVENT2021_PATH_H

#include <utility>

class path {
private:
	std::pair<uint,uint> _begin;
	std::pair<uint,uint> _end;

public:
	explicit path(const std::string& line);
	std::pair<uint,uint> begin();
	std::pair<uint,uint> end();
	uint max();

	// it would have been cool to create an iterator that produces each point between begin and end
	// UPDATE: Now that I think of it, this class it pretty useless without the iterator.
};


#endif //ADVENT2021_PATH_H
