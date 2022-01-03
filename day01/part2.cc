#include <iostream>
#include <vector>
#include <numeric>

template <typename T>
class Window {
private:
    std::vector<T> window;
    uint size;
    uint pos;

public:
    Window(int size) : window(size), size(size), pos(0) {}

    void add(T elt) {
        window[pos] = elt;
        pos = pos + 1;
        if (pos == size)
            pos = 0;
    }

    auto begin() noexcept {
        return window.begin();
    }

    auto end() noexcept {
        return window.end();
    }
};


int main() {
    // assumes depths are non-negative.
    uint tmp, cur, prev, count = 0;
    const uint WINDOW_SIZE = 3;
    Window<uint> window(WINDOW_SIZE);

    // read first window worth of elements
    for (uint i = 0; i < WINDOW_SIZE; i++) {
        if (! (std::cin >> tmp))
            return EXIT_FAILURE;
        window.add(tmp);
    }
    prev = std::accumulate(window.begin(), window.end(), 0);

    // now compute moving sums
    while (std::cin >> tmp) {
        window.add(tmp);
        cur = std::accumulate(window.begin(), window.end(), 0);
        if (cur > prev)
            count++;
        prev = cur;
    }

    std::cout << count << " increases in depth." << std::endl;
    return EXIT_SUCCESS;
}
