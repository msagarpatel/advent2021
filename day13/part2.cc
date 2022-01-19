#include <iostream>
#include <set>
#include <cassert>

// problem assumes dot never occurs along line

int main() {
	// parse dots
	// use set instead of unordered_set since we want to insert elements while using an iterator.
	std::set<std::pair<int,int>> dots;
	for (std::string s; std::getline(std::cin, s);) {
		if (s.length() == 0)
			break;
		int row, col;
		assert(sscanf(s.c_str(), "%d,%d", &row, &col) == 2);
		dots.insert({row,col});
	}
	std::cout << "Initial number of dots = " << dots.size() << '\n';

	// parse instructions
	int count = 1;
	for (std::string instr; std::getline(std::cin, instr);) {
		int val;
		if (sscanf(instr.c_str(), "fold along y=%d", &val) == 1) {
			// fold horizontal
			for (auto i = dots.begin(); i != dots.end();) {
				if (i->second > val) {
					auto old = *i;
					dots.erase(i++);
					old.second = val - (old.second - val);
					dots.insert(old);
				}
				else
					i++;
			}
		}
		else if (sscanf(instr.c_str(), "fold along x=%d", &val) == 1) {
			// fold vertical
			for (auto i = dots.begin(); i != dots.end();) {
				if (i->first > val) {
					auto old = *i;
					dots.erase(i++);
					old.first = val - (old.first - val);
					dots.insert(old);
				}
				else
					i++;
			}
		}
		else
			assert(false);

		std::cout << "Number of dots after " << count++ << " folds = " << dots.size() << '\n';
	}

	// try printing array
	std::cout << "\nFinal Array\n";
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 20; j++) {
			if (dots.count({i,j}))
				std::cout << '#';
			else
				std::cout << ".";
		}
		std::cout << '\n';
	}

	return EXIT_SUCCESS;
}
