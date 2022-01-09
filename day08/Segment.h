#ifndef ADVENT2021_SEGMENT_H
#define ADVENT2021_SEGMENT_H

#include <array>
#include <locale>

class Segment {
	static const uint NUM_SIGNAL = 10;
	static const uint NUM_OUTPUT = 4;
	std::array<std::string, NUM_SIGNAL> signals;
	std::array<std::string, NUM_OUTPUT> outputs;

public:
	Segment(std::string line);
	uint count_output_length(std::vector<uint> lengths);
};

#endif //ADVENT2021_SEGMENT_H
