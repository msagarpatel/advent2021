#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <deque>
#include <algorithm>

template<typename T>
void print_2d_vec(const std::vector<std::vector<T>>& vec, std::string msg) {
	std::cout << msg << std::endl;
	for (auto& row : vec) {
		for (T t : row)
			std::cout << t << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

template<typename T>
void print_vec(const std::vector<T>& vec, std::string msg) {
	std::cout << msg << ": ";
	for (T t : vec)
		std::cout << t << " ";
	std::cout << std::endl;
}
template <typename T>
bool is_valid_index(int i, int j, std::vector<std::vector<T>>& vec) {
	if (i < 0 || j < 0)
		return false;
	// assumes rectangular 2D vector
	if (i >= vec.size() || j >= vec[0].size())
		return false;
	return true;
}

void flash(std::vector<std::vector<int>>& octopi, std::deque<std::pair<int, int>>& to_flash) {
	auto index = to_flash.front();
	to_flash.pop_front();

	for (int i = index.first-1; i <= index.first+1; i++) {
		for (int j = index.second-1; j <= index.second+1; j++) {
			// increase energy of *surrounding* octopi
			if (is_valid_index(i,j,octopi) && !(i == index.first && j == index.second)) {
				octopi[i][j]++;
				if (octopi[i][j] == 10)
					to_flash.push_back({i,j});
			}
		}
	}
}

int main() {
	// parse input into list of strings
	std::string line;
	std::vector<std::vector<int>> octopi;
	while (std::cin >> line) {
		std::stringstream ss(line);
		std::vector<int> char_vec;
		char tmp_char;
		while (ss >> tmp_char)
			char_vec.push_back(tmp_char-'0');
		octopi.push_back(char_vec);
	}
	// print_2d_vec(octopi, "Before");

	// iterate steps
	int flashes = 0;
	for (int step = 1; ; step++) {
		// increase energy level of each octopus
		std::for_each(octopi.begin(), octopi.end(), [](auto& vec) {
			std::for_each(vec.begin(), vec.end(), [](auto& num) {num++;});
		});

		// Each octopus can flash only once per step. Keep track of this by assuming that an
		// octopus only flashes when it has energy level == 10.
		std::deque<std::pair<int,int>> to_flash;
		for (int i = 0; i < octopi.size(); i++) {
			for (int j = 0; j < octopi[i].size(); j++) {
				if (octopi[i][j] == 10)
					to_flash.push_back({i,j});
			}
		}

		// begin the flashing
		while (!to_flash.empty())
			flash(octopi, to_flash);

		// count and reset flashed octopi
		int iter_flashes = 0;
		for (auto& row : octopi) {
			for (auto& o : row) {
				if (o > 9) {
					iter_flashes++;
					o = 0;
				}
			}
		}
		flashes += iter_flashes;
		// std::cout << step << ": " << iter_flashes << " -> " << flashes << std::endl;
		// print_2d_vec(octopi, "Step " + std::to_string(step));
		if (iter_flashes == octopi.size()*octopi.size()) {
			std::cout << "Step = " << step << std::endl;
			break;
		}
	}

	return EXIT_SUCCESS;
}
