#include <sstream>
#include <vector>
#include "Segment.h"

// assumes line follows correct format
Segment::Segment(std::string line) : signals(), outputs() {
	std::stringstream ss(line);
	for (uint i = 0; i < NUM_SIGNAL; i++)
		ss >> signals[i];

	// consume pipe
	std::string pipe;
	ss >> pipe;

	for (uint i = 0; i < NUM_OUTPUT; i++)
		ss >> outputs[i];
}

uint Segment::count_output_length(std::vector<uint> lengths) {
	uint count = 0;
	// TODO: use std::count_if here?
	for (auto s : outputs) {
		for (auto l : lengths) {
			if (s.length() == l)
				count++;
		}
	}
	return count;
}
