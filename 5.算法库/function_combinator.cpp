/*
用途：h(g(f(x)))=>run(f,g,h)(x)
问题：不支持lambda函数
*/
#include <iostream>
#include <functional>

// 定义辅助函数，用于将函数组合起来
template<typename Func>
auto compose(Func f) {
    return f;
}

template<typename Func1, typename... Funcs>
auto compose(Func1 f1, Funcs... funcs) {
    return [=](auto&&... args) {
        return compose(funcs...)(f1(std::forward<decltype(args)>(args)...));
    };
}

// 示例函数
int f(int x, int y) {
    return x * y;
}

int g(int x) {
    return x + 1;
}

int h(int x) {
    return x - 3;
}

int main() {
    // 定义函数组合并运行
    auto composed = compose(f, g, h);
    int result = composed(5， 3);
    std::cout << "Result: " << result << std::endl;  // 输出: Result: 8

    return 0;
}
