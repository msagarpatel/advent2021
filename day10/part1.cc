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

static int is_corrupt(const std::string& line) {
	std::stack<char> stack;
	for (char c : line) {
		if (c == '(' || c == '[' || c == '{' || c == '<')
			stack.push(c);
		else {
			assert(c == ')' || c == ']' || c == '}' || c == '>');
			if (is_matching(stack.top(), c))
				stack.pop();
			else
				return points(c);
		}
	}

	// Only checking for corrupt lines right now
	// return stack.size() == 0;
	return 0;
}

int main() {
	// parse input into list of strings
	std::vector<std::string> lines;
	std::string tmp;
	while (std::cin >> tmp)
		lines.push_back(tmp);

	// parse lines one-by-one to find corrupt lines
	int points = 0;
	for (auto line : lines)
		points += is_corrupt(line);

	std::cout << "Points = " << points << std::endl;
	return EXIT_SUCCESS;
}
