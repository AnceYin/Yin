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
    auto f =[](int i, std::string s){ return [=](auto i) { return std::make_tuple(i, s); };};
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
    i | f(100， "string") | g | h ;
}
