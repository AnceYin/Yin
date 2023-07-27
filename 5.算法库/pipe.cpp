#include <iostream>
#include <tuple>

template<typename D, typename F>
auto operator|(D d, F f) {
    return f(d);
}


int main() {
    const int i = 3;
    auto f = [](auto i) { return std::make_tuple(10, "string"); };
    auto g = [](std::tuple<int, std::string> data) { return std::get<1>(data); };
    auto h = [](std::string s) {return s + "123"; };
    std::cout << (i | f | g | h);
    return 0;
}
