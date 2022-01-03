#include <iostream>
#include <climits>

int main() {
    // assumes depths are non-negative.
    unsigned int cur, prev = UINT_MAX, count = 0;

    // assumes input is only integers. while-loop exits if input is non-integral.
    while (std::cin >> cur) {
        if (cur > prev)
            count++;
        prev = cur;
    }

    std::cout << count << " increases in depth." << std::endl;
    return EXIT_SUCCESS;
}
