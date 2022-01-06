#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

// There was a point I've been considering since part 1: is it faster to:
//   - store the lines are strings and perform equality comparisons for offsets into the string, OR
//   - store integers and &-ing the bit positions?
// I wasn't entirely sure since I don't know how expensive &-ing is compared to equality checks,
// but now that I'm typing this out, I think it &-ing is cheaper.
// There are also memory considerations since storing strings takes more space compared to
// storing integers if the lengths of the strings is greater than sizeof(uint) (not considering
// overheads of std::string).

// this function assumes that a rating always exists
std::string find_rating(const uint index, const std::function<bool(uint, uint)>& pred,
						const std::vector<const std::string>& lines) {
	// check stopping condition
	if (lines.size() == 1)
		return lines.front();

	// partition input into zeros and ones at index
	std::vector<const std::string> zeros, ones;
	std::partition_copy(lines.begin(), lines.end(),
					 std::back_inserter(zeros), std::back_inserter(ones),
					 [index] (std::string line) {return line[index] == '0';});

	// TAIL RECURSION!!
	// I'm not sure what the space-complexity of this is since I don't know if the compiler is
	// smart enough to realize it can free the non-used array before the recursive call.
	// Average cases where m is the string length, and n is the number of strings:
	//   - smart compiler: O(m log n)
	//   - dumb compiler: O(mn log m)
	// Could consider m to be a constant if the size of the strings is constant or known to be
	// very small.
	return find_rating(index+1, pred, pred(ones.size(), zeros.size()) ? ones : zeros);
}

int main() {
	// current line/number
	std::string line;
	// vector of all lines
	std::vector<const std::string> lines;
	// total number of lines in stdin
	uint num_lines = 0;

	// read all lines
	while (std::cin >> line) {
		lines.push_back(line);
		num_lines++;
	}

	// find reading that fits criteria
	// assumes the length of each bitstring is the same
	// This solution uses O(n) memory. This can be improved by:
	//   (1) using vectors of std::shared_ptr<std::string>, or
	//   (2) using std::partition instead.
	// (2) is even more memory efficient since (1) requires an array of O(n) pointers.
	std::string oxygen = find_rating(0, std::greater_equal<uint>(), lines);
	std::string co2 = find_rating(0,std::less<uint>(), lines);

	// compute power consumption
	uint oxygen_i = std::stoi(oxygen, nullptr, 2);
	uint co2_i = std::stoi(co2, nullptr, 2);
	std::cout << "Oxygen Generator Rating = " << oxygen << " = " << oxygen_i << std::endl;
	std::cout << "CO2 scrubber rating = " << co2 << " = " << co2_i << std::endl;
	std::cout << "Life Support rating = " << oxygen_i*co2_i << std::endl;
	return EXIT_SUCCESS;
}
