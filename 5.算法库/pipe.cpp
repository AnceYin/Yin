#include <iostream>
#include <tuple>

template<typename D, typename F>
auto operator|(D d, F f) {
    return f(d);
}


int main() {
    const int i = 3;
    std::cout << (i | [](auto i) { return std::make_tuple(10, "string"); } | [](std::tuple<int, std::string> data) { return std::get<1>(data); });
    return 0;
}
