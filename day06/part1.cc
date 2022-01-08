#include <iostream>
#include <vector>

static const uint NUM_DAYS = 80;

void print_school(const std::vector<uint>& school, std::string msg) {
	std::cout << msg << "\t";
	for (uint i = 0; i < school.size(); i++) {
		std::cout << school[i];
		if (i != school.size()-1)
			std::cout << ",";
	}
	std::cout << std::endl;
}

int main() {
	// school of fish
	std::vector<uint> school;

	// parse input
	uint tmp;
	while (std::cin >> tmp) {
		school.push_back(tmp);
		// consume comma
		std::cin.get();
	}

	print_school(school, "Initial State:");

	// loop over number of days
	for (uint i = 1; i <= NUM_DAYS; i++) {
		uint original_size = school.size();
		// can't use for-each iterator since push_back() would invalidate iterator
		for (uint i = 0; i < original_size; i++) {
			uint& fish = school[i];
			// check for new fish creation
			if (fish == 0) {
				fish = 6;
				school.push_back(8);
			}
			else
				fish--;
		}
		print_school(school, "After " + std::to_string(i) + " days:");
	}

	std::cout << "Number of Fish = " << school.size() << std::endl;
	return EXIT_SUCCESS;
}
