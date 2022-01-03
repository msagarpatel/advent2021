#include <iostream>

int main() {
	// global state -- the position
	// x could be unsigned since there is no "backward" command, but lets use int to mirror y.
	int x = 0, y = 0, aim = 0;

	// current command -- it's basically a vector
	std::string direction;
	int magnitude;

	while (std::cin >> direction) {
		std::cin >> magnitude;
		if (direction == "forward") {
			x += magnitude;
			y += magnitude * aim;
		}
		else if (direction == "down")
			aim += magnitude;
		else if (direction == "up")
			aim -= magnitude;
	}

	std::cout << "Final Position: (" << x << ", " << y << ") = " << x*y << std::endl;
	return EXIT_SUCCESS;
}
