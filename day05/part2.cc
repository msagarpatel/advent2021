#include <iostream>
#include <vector>
#include <array>
#include "path.h"
#include <cassert>
#include <functional>

const uint MAX_SIZE = 1000;

void print_map(std::array<std::array<uint, MAX_SIZE>, MAX_SIZE>& map) {
	std::cout << "MAP" << std::endl;
	for (auto& row : map) {
		for (uint val : row) {
			if (val != 0)
				std::cout << val << " ";
			else
				std::cout << ". ";
		}
		std::cout << std::endl;
	}
}

int main() {
	// parse input
	std::string line;
	std::vector<path> paths;
	while (std::getline(std::cin, line))
		paths.emplace_back(line);

	// create map
	// just make it "large enough"
	std::array<std::array<uint, MAX_SIZE>, MAX_SIZE> map{};

	// add segments to map
	// could have just counted the number of overlaps here, but eh
	for (path& p: paths) {
		assert(p.max() < MAX_SIZE);
		auto begin = p.begin();
		auto end = p.end();
		if (begin.first == end.first) {
			// traverse column
			const uint col = begin.first;
			const uint start = std::min(begin.second, end.second);
			const uint stop = std::max(begin.second, end.second);
			for (uint i = start; i <= stop; i++)
				map[i][col] += 1;
		}
		else if (begin.second == end.second) {
			// traverse row
			const uint row = begin.second;
			const uint start = std::min(begin.first, end.first);
			const uint stop = std::max(begin.first, end.first);
			for (uint i = start; i <= stop; i++)
				map[row][i] += 1;
		}
		else {
			// traverse diagonally
			// TODO: the three if-clauses can just become this one clause
			const int row_inc = begin.second < end.second ? 1 : -1;
			const int col_inc = begin.first < end.first ? 1 : -1;
			auto pred = row_inc == 1 ? std::less_equal<>() :
			        (std::function<bool(int,int)>)std::greater_equal<>();
			for (int row = begin.second, col = begin.first; pred(row, end.second);
				col += col_inc, row += row_inc)
				map[row][col] += 1;
		}
		// print_map(map);
	}

	// find number of points > 2
	uint danger = 0;
	for (auto& row : map) {
		for (uint val : row) {
			if (val >= 2)
				danger++;
		}
	}

	std::cout << "Overlaps = " << danger << std::endl;
	return EXIT_SUCCESS;
}
