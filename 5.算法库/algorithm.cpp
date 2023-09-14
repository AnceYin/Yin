#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <random>
#include <ranges>
using namespace std::ranges;

int main() {
	//源数据
	std::vector R1{ 0， 1， 2， 3， 4， 5}; 
	std::map<int, std::string> R2 {{0， "H"}， { 1，"e" }， { 2，"l" }， { 3，"l" }， { 4，"o" }}; 
	auto print = [](auto x) {std::cout << x << "\t"; };
	auto one = [](auto x) {return x % 2 == 0; };
	auto two = [](auto x, auto y) {return x < y; }; 
	auto fun = [](auto x) {return 2 * x; };

	//示例1,输出8,4
	auto R3 = views::iota(0， 9) | views::filter(one) | views::reverse | views::drop(2) | views::transform(fun) | views::take(2);

	//示例2
	print( is_sorted(R1) && is_partitioned(R1, one) && binary_search(R1, 6)
		|| any_of(R1, one) || all_of(R1, one) && none_of(R1, one)
		|| equal(R1, R2 | views::keys, two) && includes(R1, R2 | views::keys, two)); 

	//示例3
	std::vector<int> R4,R5,R6,R7,R8;
	set_union(R1, R2 | views::keys, std::back_inserter(R4),two); //0,1,2,3,4,5
	merge(R1, R3 | views::reverse, std::back_inserter(R5), two); //0,1,2,3,4,4,5,8
	set_difference(R5, R4, std::back_inserter(R6), two);//4,8
	set_intersection(R6, R4, std::back_inserter(R7), two);//4
	set_symmetric_difference(R6, R4, std::back_inserter(R8), two);//0,1,2,3,5,8
	mismatch(R4,R8);//返回指向(4，5)这对迭代器

	//示例4
	move(R8, R4.begin());// R4:0,1,2,3,5,8
	swap(R4, R5); //R4:0,1,2,3,4,4,5,8 R5:0,1,2,3,5,8
	reverse(R5);//R5:8,5,3,2,1,0
	rotate(R5, R5.begin() + 2); //R5:3,2,1,0,8,5
	std::random_device rd;
	std::mt19937 g(rd()); 
	shuffle(R5, g);//R5被洗牌
	sample(R5,R6.begin()， 2, g);//R5被抽样到R6

	//示例5
	count_if(R1,one);//3
	find_if(R1,one);//返回指向0的迭代器
	copy_if(R7,R6.begin(), one);//R6:4,R5中的牌
	std::erase_if(R4,one);//剩下1，3，5
	replace_if(R5,one,0);//替换成了0,1,0,3,0,5,0

	//示例6
	transform(R1, R5, R4.begin(), two); //R4:6位随机01序列和5，8
	generate(R4, []() {return 0; }); 
	unique_copy(R4,R7.begin());//R7:0
	for_each(R7, print);
	stable_sort(R4);
	stable_partition(R4, one);
	max(R4);
} 
