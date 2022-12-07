// 以下为纯代码版，试着先想想每个printf函数打印了什么
// #include <stdio.h>
// #include <stddef.h>
// int main()
// {
//     struct s
//     {
//         void *p;
//         union u
//         {
//             int i;
//             double d;
//             char c[12];
//         } u;
//     } s = {NULL, 1};
//     printf("%s\n", s.u.c[0] == 1 ? "小端" : "大端");
//     printf("%f\n", s.u.d);
//     printf("%d\n", (int)offsetof(struct s, u));
//     printf("%d\n", (int)sizeof s);
//     return 0;
// }

#include <stdio.h>
#include <stddef.h>
int main()
{
    // s是一个s类型的结构体，s类型包括两个成员变量：p和u
    struct s
    {
        // p是一个指向void类型的指针变量，可以指向任何对象
        // 指针变量存储的是操作系统所提供的逻辑地址，其逻辑地址编码采用的地址位数决定指针变量的大小
        void *p;
        // u是一个u类型的联合体，u类型包括三个成员变量：i、f和c
        union u
        {
            // i是一个int类型的整型变量，在内存中以补码的形式存储
            int i;
            // d是一个double类型的浮点型变量，在内存中以国际标准IEEE 754所定义的格式存储
            double d;
            // c是一个存储5个char类型元素的数组，在内存中将每个元素由低地址到高地址连续存储
            // 而每个char类型元素将先按照ASCLL码转化成整型，再在内存中以补码的形式存储
            char c[12];
        } u;
    } s = {NULL, 1}; // 将NULL和1用初始化列表初始化给p和s.u.i

    // 由于联合体各成员地址相同，查看s.u.c[0]可知当前硬件的字节内存分配方式
    // 值得一提的是条件表达式运算的结果在c和c++中略有不同，一个是值，一个是引用。
    printf("%s\n", s.u.c[0] == 1 ? "小端" : "大端"); //打印结果不确定，由当前设备的CPU决定

    // 将打印以浮点型读取的整形形式存储的二进制序列
    printf("%f\n", s.u.d); //打印结果为：0.000000\n

    // 为了能一次访问成员变量u中的double类型，将u分配在8的整数倍偏移处
    printf("%d\n", (int)offsetof(struct s, u)); //打印结果为：8\n

    // 结构体和联合体的总大小为成员最大对齐数的整数倍
    printf("%d\n", (int)sizeof s); //打印结果为：24\n
    return 0;
}

// 总结：
// 类型决定分配的内存空间大小及对数据的操作权限
// 字符型-ASCII码 整型-补码 浮点型-IEEE浮点数编码 指针类型-逻辑地址编码
// 数组-低地址到高地址连续存储 结构体-依次内存对齐存储 联合体-成员共用总内存大小和地址