#include <iostream>
#include <vector>
#include <algorithm>
#include "Segment.h"

template<typename T>
void print_vec(const std::vector<T>& vec, std::string msg) {
	std::cout << msg << ": ";
	for (T t : vec)
		std::cout << t << " ";
	std::cout << std::endl;
}

int main() {
	// parse input into list of strings
	std::string line;
	std::vector<Segment> segments;
	while (std::getline(std::cin, line))
		segments.emplace_back(line);

	// find lines that have desired length
	// Would be more memory efficient to check this while reading.
	uint count = 0;
	// The digit to length map is:
	//   1 -> 2
	//   4 -> 4
	//   7 -> 3
	//   8 -> 7
	for (auto seg : segments)
		count += seg.count_output_length({2,4,3,7});

	std::cout << "Count = " << count << std::endl;
	return EXIT_SUCCESS;
}
