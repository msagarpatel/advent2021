#include <iostream>
#include <forward_list>
#include <map>
#include <cassert>
#include <unordered_map>
#include <numeric>

int main() {
	// get polymer template and store as std::forward_list<char>
	std::string line;
	getline(std::cin, line);
	std::forward_list<char> chain(line.begin(), line.end());

	// consume empty line
	std::cin.get();

	// parse pair insertion rules into map.
	// TODO: Would have been better to use unordered_map, but we'd need to create our own hash
	//  function for std::pair since the STL doesn't have one.
	std::map<std::pair<char,char>,char> rules;
	while (getline(std::cin, line)) {
		char c1, c2, c3;
		assert(sscanf(line.c_str(), "%c%c -> %c", &c1, &c2, &c3) == 3);
		rules.insert({{c1,c2},c3});
	}

	// run the process 10 times
	for (int step = 0; step < 10; step++) {
		// + is not defined for list iterators, so iterate over the list a bit unconventionally
		for (auto i = chain.cbegin(); ;) {
			// check if last character (which is the stopping condition)
			auto i_plus_1 = i;
			i_plus_1++;
			if (i_plus_1 == chain.cend())
				break;

			// make sure rule exists
			auto rule = rules.find({*i, *(i_plus_1)});
			assert(rule != rules.end());

			// apply rule
			chain.insert_after(i, rule->second);

			// minor optimization: skip inserted element here since we've already incremented
			// This assumes copy construction is cheaper than two increments.
			i = i_plus_1;
		}
	}

	// compute all frequencies
	std::unordered_map<char,int> freq;
	for (const auto& c : chain)
		freq[c]++;

	// find min and max frequencies
	const auto res = std::minmax_element(freq.cbegin(), freq.cend(),
	                                     [](const auto& a, const auto& b){
		return a.second < b.second;
	});
	std::cout << "Difference = " << res.second->second - res.first->second << std::endl;
	return EXIT_SUCCESS;
}
