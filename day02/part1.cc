#include <iostream>

int main() {
    // global state -- the position
    // x could be unsigned since there is no "backward" command, but lets use int to mirror y.
    int x, y;

    // current command -- it's basically a vector
    std::string direction;
    int magnitude;

    while (std::cin >> direction) {
        std::cin >> magnitude;
        if (direction == "forward")
            x += magnitude;
        else if (direction == "down")
            y += magnitude;
        else if (direction == "up")
            y -= magnitude;
    }

    std::cout << "Final Position: (" << x << ", " << y << ") = " << x*y << std::endl;
    return EXIT_SUCCESS;
}