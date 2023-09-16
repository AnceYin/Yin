#include <iterator>
#include <numeric>

int main(){
    std::begin();
    std::end();//及cr版本

    std::advance();//接收并修改任意类型迭代器使其向前或向后移动
    std::distance();//接收两个来自同一个容器的迭代器获取该范围内包含元素的个数
    std::next();//可看作不修改源迭代器的advance版本
    std::prev();
    std::iter_swap();//交换两个不同类型的迭代器的值

    std::size();
    std::empty();
    std::erase();//及_if版本
    std::find();//及_if版本, 返回迭代器
    std::iota();//接收两个迭代器, 初始值. 将初始值依次加一填充到指定范围
    //折叠
    std::accumulate();//接收两个迭代器, 初始值, [](初始值, 范围元素){}.其还有一个并行版本std::reduce,但不依序执行
    std::inner_product();//接收三个迭代器, 初始值, [](初始值, 范围元素){}, [](范围元素, 范围元素){}.将两个范围的元素作用并将结果与初始值作用
    //扫描
    std::partial_sum();//接收三个迭代器,[](第一个元素，第二个元素){}将第一个和第二个元素的作用结果写入第三个迭代器的下一个元素
}
