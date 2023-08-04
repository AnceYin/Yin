// 实现多态的两种方法
#include <variant>
#include <iostream>
#include <functional>

void test01() {
	struct A { void operator()() { printf("逻辑A\n"); } };
	struct B { void operator()() { printf("逻辑B\n"); } };
	using State = std::variant<A, B>;
	State state{A{}};
	std::visit([](auto&& s) {s(); }, state);
	state = B{};
	std::visit([](auto&& s) {s(); }, state);
}

void test02() {
	auto a = []() {printf("逻辑A\n"); };
	auto b = []() {printf("逻辑B\n"); };
	auto c = [](std::function<void()> f) {f(); };
	c(a);
	c(b);
}

int main() {
	test01();
}