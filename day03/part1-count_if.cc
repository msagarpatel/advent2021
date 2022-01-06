#include <iostream>
#include <vector>
#include <algorithm>

// This implementation is similar to that of part1.cc, but it uses more memory since it reads
// all lines at once, and stores them in memory. This is not a generally good solution, but I
// want to try it so I can use one of the C++ specific functions under <algorithm>.

int main() {
	// current line/number
	std::string line;
	// vector of all lines
	std::vector<std::string> lines;
	// total number of lines in stdin
	uint num_lines = 0;

	// read all lines
	while (std::cin >> line) {
		lines.push_back(line);
		num_lines++;
	}

	// compute gamma and epsilon
	// assumes there is always a most/least common bit
	// So, the case where the number of zeros and ones are the same is not considered.
	// assumes the length of each bitstring is the same
	std::string gamma, epsilon;
	for (int i = 0; i < line.length(); i++) {
		uint count = std::count_if(lines.begin(), lines.end(), [i](const std::string& str){
			return str[i] == '1';
		});
		gamma += count > num_lines/2 ? "1" : "0";
		epsilon += count < num_lines/2 ? "1" : "0";
	}

	// compute power consumption
	uint gamma_i = std::stoi(gamma, nullptr, 2);
	uint epsilon_i = std::stoi(epsilon, nullptr, 2);
	std::cout << "gamma = " << gamma << " = " << gamma_i << std::endl;
	std::cout << "epsilon = " << epsilon << " = " << epsilon_i << std::endl;
	std::cout << "Power consumption = " << gamma_i*epsilon_i << std::endl;
	return EXIT_SUCCESS;
}
