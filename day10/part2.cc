#include <iostream>
#include <vector>
#include <sstream>
#include <cassert>
#include <stack>
#include <map>

template<typename T>
void print_vec(const std::vector<T>& vec, std::string msg) {
	std::cout << msg << ": ";
	for (T t : vec)
		std::cout << t << " ";
	std::cout << std::endl;
}

static int inline points(char a) {
	switch (a) {
		case '(':
		case ')':
			return 3;
		case '[':
		case ']':
			return 57;
		case '{':
		case '}':
			return 1197;
		case '<':
		case '>':
			return 25137;
		default:
			assert(false);
	}
}

static int inline incomplete_points(char a) {
	switch (a) {
		case '(':
		case ')':
			return 1;
		case '[':
		case ']':
			return 2;
		case '{':
		case '}':
			return 3;
		case '<':
		case '>':
			return 4;
		default:
			assert(false);
	}
}

const std::map<char,char> parens = {
		{'(', ')'},
		{'[', ']'},
		{'{', '}'},
		{'<', '>'}
};

// throws exception if key not present
static bool inline is_matching(char top, char bot) {
	return parens.at(top) == bot;
}

static std::pair<uint,uint64_t> is_corrupt_or_incomplete(const std::string& line) {
	std::stack<char> stack;

	// check for corrupt lines
	for (char c : line) {
		if (c == '(' || c == '[' || c == '{' || c == '<')
			stack.push(c);
		else {
			assert(c == ')' || c == ']' || c == '}' || c == '>');
			if (is_matching(stack.top(), c))
				stack.pop();
			else
				return {points(c), 0};
		}
	}

	// check for incomplete lines
	if (stack.size() != 0) {
		uint64_t points = 0;
		while (!stack.empty()) {
			auto elt = stack.top();
			points *= 5;
			points += incomplete_points(elt);
			stack.pop();
		}
		return {0,points};
	}

	// line is correct, which should be none of them
	assert(false);
	return {0,0};
}

int main() {
	// parse input into list of strings
	std::vector<std::string> lines;
	std::string tmp;
	while (std::cin >> tmp)
		lines.push_back(tmp);

	// parse lines one-by-one to find corrupt lines
	int points = 0;
	std::vector<uint64_t> incomplete;
	for (auto line : lines) {
		auto tmp = is_corrupt_or_incomplete(line);
		if (tmp.first)
			points += tmp.first;
		else if (tmp.second)
			incomplete.push_back(tmp.second);
	}

	// sort incomplete points
	std::sort(incomplete.begin(), incomplete.end());
	auto midpoint = incomplete.begin() + incomplete.size()/2;

	std::cout << "Middle Incomplete Point = " << *midpoint << std::endl;
	return EXIT_SUCCESS;
}
