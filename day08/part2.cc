#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "Segment.h"

template<typename T>
void print_vec(const std::vector<T>& vec, std::string msg) {
	std::cout << msg << ": ";
	for (T t : vec)
		std::cout << t << " ";
	std::cout << std::endl;
}

uint add_segments(uint val, Segment& s) {
	return val + s.decode();
}

int main() {
	// parse input into list of strings
	std::string line;
	std::vector<Segment> segments;
	while (std::getline(std::cin, line))
		segments.emplace_back(line);

	const uint sum = std::accumulate(segments.begin(), segments.end(), 0, add_segments);
	std::cout << "Sum of outputs = " << sum << std::endl;
	return EXIT_SUCCESS;
}
