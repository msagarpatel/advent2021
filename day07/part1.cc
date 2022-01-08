#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
void print_vec(const std::vector<T>& vec, std::string msg) {
	std::cout << msg << ": ";
	for (T t : vec)
		std::cout << t << " ";
	std::cout << std::endl;
}

int main() {
	// parse input into list of integers
	uint pos;
	std::vector<uint> crabs;
	while (std::cin >> pos) {
		crabs.push_back(pos);
		// consume comma
		std::cin.get();
	}
	// print_vec(crabs, "Crabs");

	// find largest position tpo determine size of list
	const uint max_row = (*std::max_element(crabs.begin(), crabs.end()));
	std::cout << "Max Row = " << max_row << std::endl;

	// convert list to vector of size max_position
	std::vector<uint> pos_count(max_row+1, 0);
	for (auto crab : crabs)
		pos_count[crab]++;
	// print_vec(pos_count, "pos_count");

	// check cost for each possible row. This will be a nested loop. Store in another array, costs.
	// Would be more efficient to just store minimum, and it's cost instead of cost of each row.
	std::vector<uint> costs(max_row+1 ,0);
	for (int row = 0; row <= max_row; row++) {
		for (int i = 0; i <= max_row; i++) {
			const uint dist = std::abs(row - i);
			costs[row] += dist*pos_count[i];
		}
	}

	// find min in cost array
	const uint min_cost = *std::min_element(costs.begin(), costs.end());

	std::cout << "Minimum Cost = " << min_cost << std::endl;
	return EXIT_SUCCESS;
}
