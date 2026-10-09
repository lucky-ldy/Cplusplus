#include <stdio.h>
#include <stdlib.h>
//一、IO流 输入输出流 命名空间 namespace


#include<iostream>
 
// 多⽂件中可以定义同名namespace，
//他们会默认合并到⼀起，就像同⼀个namespace⼀样
using namespace std;
namespace ldy
{
    // 命名空间中可以定义变量/函数/类型
    int rand = 10;
    int Add(int left, int right)
    {
        return left + right;
    }

    struct Node
    {
        struct Node* next;
        int val;
    };
}

// int main()
// {
//     cout << "hello world\n" << endl;


//     // 这⾥默认是访问的是全局的rand函数指针
//     printf("%p\n", rand);
//     // 这⾥指定bit命名空间中的rand
//     printf("%d\n", bit::rand);
//     struct bit::Node* L;
//     return 0;
// }

namespace ldy
{
// 鹏哥
    namespace pg
    {
        int rand = 1;
        int Add(int left, int right)
        {
            return left + right;
        }
    }
// 杭哥
    namespace hg
    {
        int rand = 2;
        int Add(int left, int right)
        {
            return (left + right)*10;
        }
    }
}

// int main()
// {
//     printf("%d\n", ldy::pg::rand);
//     printf("%d\n", ldy::hg::rand);
//     printf("%d\n", ldy::pg::Add(1, 2));
//     printf("%d\n", ldy::hg::Add(1, 2));
//     return 0;

// }

// int main()
// {
//     int i = 0;
//     double j = 11.11;
//     //自动识别类型
//     std::cout << "hello world" << std::endl;
//     std::cout << i << std::endl;
//     std::cout << j << std::endl;
//     std::cout << &i << std::endl;
// }

//这里要指定命名空间很麻烦
//方式1. 用using namesapace std;  展开命名空间 
//相当于告诉编译器 不仅仅要取局部查找 还要取这个命名空间查找
//缺陷是有冲突风险 项目里面不推荐用

//折中的方案 部分展开！
//using std::cout; using std::endl; using std::cin;  只展开经常使用的


//二、C++ 输入 输出

//C++的输⼊输出可以⾃动识别变量类型(本质是通过函数重载实现的)
//cout/cin/endl等都属于C++标准库 C++标准库都放在⼀个叫std(standard)的命名空间中
//<<是流插⼊运算符，>>是流提取运算符。

#include <iostream>
using namespace std;
// int main()
// {
//     int a = 0;
//     double b = 0.1;
//     char c = 'x';
//     cout << a << " " << b << " " << c << endl;
//     std::cout << a << " " << b << " " << c << std::endl;
//     scanf("%d%lf", &a, &b);
//     printf("%d %lf\n", a, b);
//     // 可以⾃动识别变量的类型
//     cin >> a;
//     cin >> b >> c;
//     cout << a << endl;
//     cout << b << " " << c << endl;
//     // 在io需求⽐较⾼的地⽅，如部分⼤量输⼊的竞赛题中，加上以下3⾏代码
//     // 可以提⾼C++IO效率
//     ios_base::sync_with_stdio(false);
//     cin.tie(nullptr);
//     cout.tie(nullptr);
//     return 0;
// }



//三、缺省参数
// 在调⽤该函数时，如果没有指定实参
// 则采⽤该形参的缺省值，否则使⽤指定的实参
// 全缺省就是全部形参给缺省值，半缺省就是部分形参给缺省值
//！用的人很舒服 但是读的人更难
#include <fstream>

//全缺省
void Func(int a = 0)
{
    cout << a << endl;

}

//半缺省
//void open (const char* filename . ios_base::openmode mode = ios_base::out);

// int main()
// {
//     Func();//没有传参时 使用参数的默认值
//     Func(10);//传参时 使用指定的实参

//     //这两种写法的作用一样
//     FILE* fout = fopen("main.cpp" , "w");

//     std::ofstream ofs;
//     ofs.open("test.txt"); //只需要填文件名就行
//     return 0;

// }

// 全缺省
void Func1(int a = 10, int b = 20, int c = 30)
{
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl << endl;
}

// 半缺省（缺省的参数必须从右往左依次连续缺省）
void Func2(int a, int b = 10, int c = 20)
{
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl << endl;
}

int main()
{
    Func1();
    Func1(1);
    Func1(1,2);
    Func1(1,2,3);
    Func2(100);
    Func2(100, 200);
    Func2(100, 200, 300);
    return 0;
}





