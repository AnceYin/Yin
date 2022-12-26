// #include <iostream>
// using namespace std;
// class complex
// {
// private:
//     double m_re, m_im;
//
// public:
//     complex(const double re, const double im = 0) : m_re(re), m_im(im) {}
//     complex &operator()(const double re, const double im) { return m_re = re, m_im = im, *this; }
//     complex operator+(const complex &z) const { return complex(m_re + z.m_re, m_im + z.m_im); }
//     friend ostream &operator<<(ostream &os, const complex &x) { return os << x.m_re << '+' << x.m_im << 'i'; }
// };
// int main()
// {
//     complex *p = new complex[2]{0, 1};
//     cout << (p[0] = ((complex)1)(1, 1) + 1 + complex(1)(1, 1) + p[1]) << endl;
//     delete[] p;
// }

#include <iostream>

// 名字空间是为了区分同一作用域下相同的标识符 ，一个命名空间会定义一个新的作用域
using namespace std;

// C++基于C的结构体进行了拓展并提出了类和对象的概念
// 每创建一个类都会定义一个新的作用域，如果在类体外定义成员，需要使用::作用域解析符指明成员属于哪个类域
// 这里运用到了基于对象的思想，创建了一个复数类并实现了复数类的加法
class complex
{
private:
    // 定义复数类的实部m_re(real part)和虚部m_im(imaginary part)
    double m_re, m_im;

    // 公共属性，一般用来创建对外的函数接口来对数据进行处理。成员函数互为友元，在类内定义还会建议编译器内联
    // 除了我们自己定义的接口外，编译器也会生成一些默认接口来对类成员数据初始化，赋值，清理及对类的寻址
    // 当成员中含有指针时，用默认接口值拷贝的话将带来很大的隐患，需要另外开辟空间来拷数据，在堆区的数据则还需要手动清理
public:
    // 初始化列表能让一些在定义时必须初始化的类型初始化：const类型，引用类型，没有默认构造函数的自定义类型
    // 单参构造函数可以实现对内质类型的隐式类型转换，如果要避免这种情况可以在构造函数前面加上explicit
    complex(const double re, const double im = 0) : m_re(re), m_im(im) {}

    // 这里用到了逗号表达式，他会从左往右计算各个表达式，只有最后一个表达式的值会保留，其他的值会被丢掉
    // 将传入的两个参数分别赋给调用他的类的成员并以引用的方式传回类自身，这样的操作可以实现一些重复调用操作
    complex &operator()(const double re, const double im) { return m_re = re, m_im = im, *this; }

    // 这里构造了一个匿名对象对加号两边的类的成员属性分别进行相加
    // 因为构造的匿名对象生命周期只在这一行，所以不能以引用的方式传出
    // 因为不会对调用加号的类和以参数传入的类进行修改，所以分别在函数体和形参前加了const
    complex operator+(const complex &z) const { return complex(m_re + z.m_re, m_im + z.m_im); }

    // 友元函数不属于类成员函数，但能够访问私有成员变量，一般用来处理左操作数非本类的操作符重载
    // 所以不需要加类作用域，函数体前也不能加const。特别注意的是，这里的os不能加const，因为每次操作都会改变os的状态
    friend ostream &operator<<(ostream &os, const complex &x) { return os << x.m_re << '+' << x.m_im << 'i'; }
};

int main()
{
    // new操作符会先开辟空间再创建类并调用构造函数， delete则是先调用析构函数再回收空间
    // 中括号会连续开辟空间依次创建类并调用构造函数，大括号的两个参数会分别传给各个对象
    complex *p = new complex[2]{0, 0};

    // ((complex)1)(1, 1)会发生强制类型转换，1会发生隐式类型转换，complex(1)(1, 1)会创建匿名对象，三者的底层原理相同：
    // 都创建了一个临时对象并调用构造函数将1作为参数来初始化，再用重载的小括号操作符对其赋值
    // 注意各操作符的优先级，比如赋值操作必须加括号，因为=操作符优先级低于<<操作符
    cout << (p[0] = ((complex)1)(1, 1) + 1 + complex(1)(1, 1) + p[1]) << endl;

    // 如果没加方括号，虽然也会将new出来的堆区空间释放,但只会调用一次析构函数，可能会导致内存释放不彻底
    delete[] p;
}

// 总结：
// 1.类由定义类的关键字struct或class(仅默认访问方式不同)起头，中间是类名和类体，并以分号结尾
// 2.类体包括成员变量和成员函数，成员变量遵循结构体的内存对齐规则，成员函数通过形参中隐藏的this指针决定调用权
// 3.一个类最多有6个默认成员函数，一般我们只会写一个全缺省的构造函数，当成员有指针时，则还需重写拷贝构造、等号重载和析构函数
// 4.当函数体内语句较少时定义在类内，当我们不会改变某些东西的时候要习惯加const，一般我们常使用引用传递