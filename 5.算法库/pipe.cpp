#include <iostream>
#include <tuple>
#include <variant>

template<typename D, typename F>
auto operator|(D d, F f) {
    return f(d);
}

int main() {
    const int i = 3;
    //单参=>多参
    auto f = [](auto i) { return std::make_tuple(100, "string"); };
    //多参=>返回多态
    auto g = [](std::tuple<int, std::string> data)->std::variant<int, std::string> {
        if (0) return std::get<0>(data);
        else return std::get<1>(data);
    };
    // 接收多态分别处理
    auto h = [](std::variant<int, std::string> state) {
        if (std::holds_alternative<int>(state))
            std::cout << std::get<int>(state);
        if (std::holds_alternative<std::string>(state))
            std::cout << std::get<std::string>(state);
    };
    i | f | g | h ;
}
