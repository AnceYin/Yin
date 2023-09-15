#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <map>

int main()
{
    // vector:
    // 容量和大小
    std::vector<int> v(10); // 初始化容器为10个0
    v.size();               // 获取容器的元素个数
    v.resize(5);            // 修改容器中的元素个数
    v.clear();              // 将容器中的元素清空
    v.empty();              // 判断容器是否为空

    v.capacity();               // 获取i的容量
    std::vector<int>().swap(v); // 将i的容量变为0
    v.reserve(12);              // 预分配i的容量, 注意vector永远不会释放内存

    // 增删查改操作
    v.assign(5, 100); // 先删除原有的元素，再填充5个100代之
    v.push_back(100); // 适合将已构造元素追加到容器, 可调用std::move()调用元素的移动构造
    v.pop_back();
    v.front();
    v.back() = 1;

    v.insert(begin(v) + 2, {0, 1});  // 在下标为二的位置插入0, 1
    v.erase(begin(v), begin(v) + 2); // 删除下标为0和下标为1的元素, 注意范围为左闭右开
    v.at(1) = 0;                     // 查看下标为一的位置上的元素, 为1

    // list(对比vector):
    // 少了capacity和reserve
    // 少了[], 多了头插头删
    // list的特殊操作：
    std::list<int> list1 = {3, 3, 1};
    std::list<int> list2 = {1, 2, 3};
    auto pos = list1.begin();
    std::advance(pos, 2);
    // 将list2的指定范围(左闭右开)的元素串联到list1的pos位置(之前): list1: 3,3,1,2,1,list2: 3
    list1.splice(pos, list2, begin(list2), std::next(begin(list2), 2));
    list1.sort([](int i, int j)
               { return i > j; }); // 3,3,2,1,1
    list1.reverse();               // 1,1,2,3,3
    list1.unique();                // 1,2,3
    list1.merge(list2);            // 将list2的所有元素默认按<插入list1中: list1: 1,2,3,3 list2:

    // string(对比vector):
    // 名称改变但作用未变：size->length, push_back->append +=, <=>->compare
    // 新增方法：c_str, starts_with, ends_with, substr, find, rfind, replace(替换), +, <<, >>
    // 数值转换:to_string, stod, stoi, ""s:需要引入using namespace std::string_literals;

    // string_view(对比string):
    // 少了内存相关的方法, 不能更改源string, to_str. 增加了视图的收缩remove_prefix, remove_suffix

    // span(对比vector):
    // 提供了[], front, back, size, empty, subspan

    // queue:
    // push,pop,front,back,size,empty,sawp

    // priority_queue:
    // push,pop,top,size,empty,sawp

    // stack:
    // push,pop,top,size,empty,sawp

    // pair
    // 定义于<utility>, make_pair, first, second

    // map:
    std::map<int, std::string> m{
        {1, "1"},
        {2, "2"},
        {3, "3"}
    };
    if (auto [iter, success]{m.insert({4, "4"})}; success){
        std::cout << "Insert successed\n";
    }
    m.insert_or_assign(4, "5"); // 将用新值替换旧值
    m[4] = {"6"};               // 将用新值替换旧值
    if (auto iter{m.find(4)}; iter != end(m)){
        iter->second = "7";
    }
    if (m.contains(4)){
        m[1] = "8";
    }
    for (const auto &[key, value] : m){
        std::cout << value << std::endl;
    }
    m.erase(4);
    std::map<int, std::string> m2{
        {4, "4"},
        {5, "5"}
    };
    m.insert(m2.extract(4)); // m2将失去key为4的结点
    m.merge(m2);             // 将m2与m未重复的结点合并到m

    // multmap
    //[]->equal_range, insert会返回迭代器

    // set/multset
    // 无法修改元素

    // unordered_map/...
    // 哈希方法：桶：load_factot平均冲突,bucket_count桶数, begin(bucket(key))元素
}
