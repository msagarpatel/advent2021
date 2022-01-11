#include <iostream>
#include <vector>
#include <sstream>
#include <numeric>
#include <cassert>
#include <algorithm>

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

// the writeup suggests there is a bijection between the low points and basins. Otherwise, I
// would have seen no reason why a basin couldn't contain two low points.
// Use recursion for simplicity. Not a good idea in general, due to stack usage. Not sure if
// there are any opportunities for tail recursion.
// Maintain a separate 2D array of bools instead of overwriting map with sentinels (like -1). Not
// strictly needed by our problem since basin size only depends on number of locations.
template <typename T>
int basin_size(const std::vector<std::vector<T>>& map,
			   std::vector<std::vector<bool>>& bool_map,
			   const int row, const int col, uint count = 1) {
	assert(map[row][col] >= 0);
	assert(map[row][col] < 9);

	// bail if already visited this place
	if (bool_map[row][col])
		return count-1;
	bool_map[row][col] = true;

	// check up
	if (row-1 >= 0 && map[row-1][col] != 9)
		count = basin_size(map, bool_map, row-1, col, count+1);
	// check down
	if (row+1 < map.size() && map[row+1][col] != 9)
		count = basin_size(map, bool_map, row+1, col, count+1);
	// check left
	if (col-1 >= 0 && map[row][col-1] != 9)
		count = basin_size(map, bool_map, row, col-1, count+1);
	// check right
	if (col+1 < map[row].size() && map[row][col+1] != 9)
		count = basin_size(map, bool_map, row, col+1, count+1);

	return count;
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

	// find low points, and then find the size of the basins of those low points
	// works for non-square heightmaps as well
	// cheaper to just sort basin_sizes at the end instead of using a std::map (which is ordered)
	std::vector<int> basin_sizes;
	for (int i = 0; i < heightmap.size(); i++) {
		for (int j = 0; j < heightmap[i].size(); j++) {
			if (is_local_minimum(heightmap, i, j)) {
				// bool_maps assumes a retangular map
				std::vector<std::vector<bool>> bool_map(heightmap.size(),
											std::vector<bool> (heightmap[0].size()));
				basin_sizes.push_back(basin_size(heightmap, bool_map, i, j));
			}
		}
	}

	// sort basin_sizes and print output
	print_vec(basin_sizes, "Basin Sizes");
	std::sort(basin_sizes.begin(), basin_sizes.end());
	print_vec(basin_sizes, "Sorted Basin Sizes");
	auto iter = basin_sizes.rbegin();
	int prod = std::accumulate(iter, iter+3, 1, std::multiplies<>());
	std::cout << "Product = " << prod << std::endl;
	return EXIT_SUCCESS;
}
