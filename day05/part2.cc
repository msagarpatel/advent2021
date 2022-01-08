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

int get_inc(uint first, uint second) {
	if (first == second)
		return 0;
	if (first < second)
		return 1;
	return -1;
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
		const int row_inc = get_inc(begin.second, end.second);
		const int col_inc = get_inc(begin.first, end.first);
		auto row_pred = row_inc == 1 ? std::less_equal<>() :
		                (std::function<bool(int,int)>)std::greater_equal<>();
		auto col_pred = col_inc == 1 ? std::less_equal<>() :
		                (std::function<bool(int,int)>)std::greater_equal<>();
		for (int row = begin.second, col = begin.first;
		     row_pred(row, end.second) && col_pred(col, end.first);
		     col += col_inc, row += row_inc)
			map[row][col] += 1;
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
