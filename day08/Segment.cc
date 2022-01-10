#include <sstream>
#include <vector>
#include <array>
#include <cassert>
#include <algorithm>
#include <map>
#include <stdlib.h>
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

	// sort each of the strings. ordered ranges are needed for std::set_intersection.
	for (auto& s : signals)
		std::sort(s.begin(), s.end());
	for (auto& s : outputs)
		std::sort(s.begin(), s.end());
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

size_t static set_intersection_size(const std::string& s1, const std::string& s2) {
	std::array<char,7> tmp{};
	auto iter = std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), tmp.begin());
	return std::distance(tmp.begin(), iter);
}

size_t static set_union_size(const std::string& s1, const std::string& s2) {
	std::array<char,7> tmp;
	auto iter = std::set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), tmp.begin());
	return std::distance(tmp.begin(), iter);
}

uint Segment::decode() {
	// encoded digits
	std::array<std::string,10> encodings;

	// find four digits with unique encoding (1,4,7,8)
	for (const auto& s : signals) {
		const auto len = s.size();
		if (len == 2) {
			assert(encodings[1].empty());
			encodings[1] = s;
		}
		else if (len == 4) {
			assert(encodings[4].empty());
			encodings[4] = s;
		}
		else if (len == 3) {
			assert(encodings[7].empty());
			encodings[7] = s;
		}
		else if (len == 7) {
			assert(encodings[8].empty());
			encodings[8] = s;
		}
	}

	// disambiguate three digits that use six segments (0,6,9)
	for (const auto& s : signals) {
		const auto len = s.size();
		if (len != 6)
			continue;

		if (set_intersection_size(s, encodings[1]) == 1) {
			assert(encodings[6].empty());
			encodings[6] = s;
		}
		else if (set_union_size(s, encodings[4]) == 6) {
			assert(encodings[9].empty());
			encodings[9] = s;
		}
		else {
			assert(encodings[0].empty());
			encodings[0] = s;
		}
	}

	// disambiguate three digits that use 5 segments (2,3,5)
	// TODO: could combine with previous loop if not depending encodings found in that loop.
	for (const auto& s : signals) {
		const auto len = s.size();
		if (len != 5)
			continue;

		if (set_union_size(s, encodings[1]) == 5) {
			assert(encodings[3].empty());
			encodings[3] = s;
		}
		else if (set_union_size(s, encodings[9]) == 7) {
			assert(encodings[2].empty());
			encodings[2] = s;
		}
		else {
			assert(encodings[5].empty());
			encodings[5] = s;
		}
	}

	// sanity check that each encoding has been found
	for (const auto& e : encodings)
		assert(e.length() != 0);

	// determine output value
	// this is not the best way to do this, but I haven't used a dictionary in AoC yet
	std::map<std::string,uint> encoding_map;
	for (uint i = 0; i < encodings.size(); i++)
		encoding_map[encodings[i]] = i;

	std::string ret;
	for (const auto& s : outputs)
		ret += std::to_string(encoding_map[s]);

	return std::atoi(ret.c_str());
}
