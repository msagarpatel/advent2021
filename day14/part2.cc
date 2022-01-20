#include <iostream>
#include <map>
#include <cassert>
#include <unordered_map>
#include <algorithm>

// The part 1 implementation wasn't particularly good since it's memory complexity was O(L * 2^N)
// where N is the number of steps, and L is the length of the initial chain.
//
// For this (better) implementation, we note that we only care about the number of pairs of each
// type that are in the chain. Thus, memory complexity will be O(P^2), where P is the number of
// atoms.

int main() {
	// get polymer template and store as std::map
	std::string line;
	getline(std::cin, line);
	const auto last_char = line.back();
	std::map<std::pair<char,char>,uint64_t> chain;
	for (auto i = line.begin(); i != line.end()-1; i++)
		chain[{*i,*(i+1)}]++;

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

	// run the process 40 times
	for (int step = 0; step < 40; step++) {
		// TODO: can we avoid the copy? It's not a big deal since the number of atom pairs is
		//  quite small, but just wondering.
		std::map<std::pair<char,char>,uint64_t> new_chain;

		for (const auto& [pair,count] : chain) {
			// find rule and make sure it exists
			auto rule = rules.find(pair);
			assert(rule != rules.end());

			// apply rule
			new_chain[{pair.first, rule->second}] += count;
			new_chain[{rule->second, pair.second}] += count;
		}

		std::swap(chain, new_chain);
	}

	// compute all frequencies
	// works since value is default-constructed if key is missing
	// TODO: is it safe to assume int is default constructed to 0?
	std::unordered_map<char,uint64_t> freq;
	for (const auto& [pair,count] : chain)
		freq[pair.first] += count;
	freq[last_char]++;

	// find min and max frequencies
	const auto res = std::minmax_element(freq.cbegin(), freq.cend(),
	                                     [](const auto& a, const auto& b){
		                                     return a.second < b.second;
	                                     });
	std::cout << "Most common = (" << res.second->first << ", " << res.second->second << ")\n";
	std::cout << "Least common = (" << res.first->first << ", " << res.first->second << ")\n";
	std::cout << "Difference = " << res.second->second - res.first->second << std::endl;
	return EXIT_SUCCESS;
}
