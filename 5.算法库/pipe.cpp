#include <iostream>

template<typename D, typename F>
D operator|(D d, F f) {
    return d = f(d), d;
}

int main() {
    const int i = 3;
    std::cout << (i | [](auto i) { return i - 1; } | [](auto i) { return i + 1; });
    return 0;
}
