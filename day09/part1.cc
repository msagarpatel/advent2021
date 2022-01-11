#include <iostream>
#include <vector>
#include <sstream>

template<typename T>
void print_vec(const std::vector<T>& vec, std::string msg) {
	std::cout << msg << ": ";
	for (T t : vec)
		std::cout << t << " ";
	std::cout << std::endl;
}

template <typename T>
bool is_local_minimum(const std::vector<std::vector<T>>& map, const int row, const int col) {
	const T point = map[row][col];
	if (row-1 >= 0 && map[row-1][col] <= point)
		return false;
	if (row+1 < map.size() && map[row+1][col] <= point)
		return false;
	if (col-1 >= 0 && map[row][col-1] <= point)
		return false;
	if (col+1 < map[row].size() && map[row][col+1] <= point)
		return false;
	return true;
}

int main() {
	// parse input into list of ints
	std::vector<std::vector<int>> heightmap;
	std::string line;
	while (std::getline(std::cin, line)) {
		std::stringstream ss(line);

		// read characters one-by-one from the line and then convert to int
		std::vector<int> row;
		char height;
		while (ss >> height)
			row.push_back(height-'0');
		heightmap.push_back(row);
	}

	// compute risk
	// works for non-square heightmaps as well
	int risk = 0;
	for (int i = 0; i < heightmap.size(); i++) {
		for (int j = 0; j < heightmap[i].size(); j++) {
			if (is_local_minimum(heightmap, i, j))
				risk += heightmap[i][j] + 1;
		}
	}

	std::cout << "Risk Level = " << risk << std::endl;
	return EXIT_SUCCESS;
}
