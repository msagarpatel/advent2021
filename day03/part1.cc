#include <iostream>
#include <vector>
#include <cassert>

void bstr_to_count(const std::string &line, std::vector<uint> &counts) {
	for (uint i = 0; i < line.length(); i++) {
		if (line[i] == '1')
			counts[i]++;
	}
}

int main() {
	// current line/number
	std::string line;

	// assume the length of each bitstring is the same as the first, and read that first string
	std::cin >> line;
	// len is the length of each bitstring
	uint len = line.length();
	uint num_lines = 1;
	std::vector<uint> counts(len, 0);
	bstr_to_count(line, counts);

	// read remaining lines
	while (std::cin >> line) {
		assert(line.length() == len);
		bstr_to_count(line, counts);
		num_lines++;
	}

	// use counts to create gamma
	std::string gamma, epsilon;
	// assumes there is always a most/least common bit
	// So, the case where the number of zeros and ones are the same is not considered.
	for (int i = 0; i < len; i++) {
		gamma += counts[i] > num_lines/2 ? "1" : "0";
		epsilon += counts[i] < num_lines/2 ? "1" : "0";
	}

	// compute power consumption
	uint gamma_i = std::stoi(gamma, nullptr, 2);
	uint epsilon_i = std::stoi(epsilon, nullptr, 2);
	std::cout << "gamma = " << gamma << " = " << gamma_i << std::endl;
	std::cout << "epsilon = " << epsilon << " = " << epsilon_i << std::endl;
	std::cout << "Power consumption = " << gamma_i*epsilon_i << std::endl;
	return EXIT_SUCCESS;
}
