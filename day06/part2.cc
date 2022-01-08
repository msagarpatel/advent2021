#include <iostream>
#include <array>
#include <cassert>
#include <numeric>

// Need a new strategy due to the (exponential?) increase in processing time. We don't care about
// individual fish, or their ages in number of cycles. We just need to know the age of the fish
// in terms of days left until it gives birth to another fish. So rather than representing each
// fish with a number of days, only keep track of 9 integers -- the number of fish with that
// number of days left until birth.

static const uint NUM_DAYS = 256;
static const uint CYCLE_LENGTH = 9;

void print_school(const std::array<uint64_t,CYCLE_LENGTH>& school, std::string msg) {
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
	std::array<uint64_t,CYCLE_LENGTH> school{};

	// parse input
	uint tmp;
	while (std::cin >> tmp) {
		assert(tmp <= CYCLE_LENGTH);
		school[tmp]++;
		// consume comma
		std::cin.get();
	}

	print_school(school, "Initial State:");

	// loop over number of days
	for (uint i = 1; i <= NUM_DAYS; i++) {
		// move each number one down the list
		// TODO: more efficient to use an offset into the list to avoid moving 9 integers in each
		//  iteration.
		// shift over each fish
		std::rotate(school.begin(), school.begin() + 1, school.end());

		// address fish that transitioned from day 0 to day 6
		school[6] += school.back();
		print_school(school, "After " + std::to_string(i) + " days:");
	}

	std::cout << "Number of Fish = " << std::accumulate(school.begin(), school.end(),
													 (uint64_t) 0) << std::endl;
	return EXIT_SUCCESS;
}
