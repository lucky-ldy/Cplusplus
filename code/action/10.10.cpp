
//一、函数重载(自动识别类型的本质)
//C++⽀持在同⼀作⽤域中出现同名函数，
//但是要求这些同名函数的形参不同，可以是参数个数不同或者类型不同


#include <iostream>

using namespace std;

// 1、参数类型不同
int Add(int left, int right)
{
    cout << "int Add(int left, int right)" << endl;
    return left + right;
}

double Add(double left, double right)
{
    cout << "double Add(double left, double right)" << endl;
    return left + right;
}

// 2、参数个数不同
//构成函数重载 但是调用的时候会存在歧义
//不传参的时候会显示对重载调用函数不明确
//全缺省和无参的不能同时存在
void f()
{
    cout << "f()" << endl;
}

void f(int a)
{
    cout << "f(int a)" << endl;
}

// 3、参数类型顺序不同
void f(int a, char b)
{
    cout << "f(int a,char b)" << endl;
}

void f(char b, int a)
{
    cout << "f(char b, int a)" << endl;
}

void Swap(int* p1 , int* p2);
void Swap(char* p1 , char* p2);
void Swap(double* p1 , double* p2);

// int main()
// {
//     Add(10, 20);
//     Add(10.1, 20.2);
//     f();
//     f(10);
//     f(10, 'a');
//     f('a', 10);
//     return 0;
// }



//二、引用（在数据结构已经大概了解过了）

//前提：引用的目标不是提出带指针  而是和指针互补 解决一些指针用起来比较复杂的地方
//引⽤不是新定义⼀个变量，⽽是给已存在变量取了⼀个别名，
//编译器不会为引⽤变量开辟内存空间，它和它引⽤的变量共⽤同⼀块内存空间。

//类型& 引⽤别名 = 引⽤对象;

// 返回值与返回引用（以取栈顶元素为例）
// int STTop(ST& rs) { return rs.a[rs.top]; }
// 返回 int：取出元素的值，交给调用者的是副本，不是原元素。
// STTop(st1) += 10; // 错误：返回的 int 临时值不能作为 += 的左边。
// int& STTop(ST& rs) { return rs.a[rs.top]; }
// 返回 int&：交给调用者的是原元素的别名，+= 10 会修改原元素。
// 逻辑：参数中的 & 决定怎样传入；返回类型中的 & 决定怎样传出。
// 普通局部变量可以返回值：先取出值，函数结束后局部变量才销毁。
// 不能返回普通局部变量的引用：变量销毁后，引用就失效了。
// 要引用出了这个函数还存在的

//错误示例（返回变量出当前函数作用域就销毁了 ，不能引用返回 否则结果未可知）
int& func (int x, int y)
{
    int ret = x + y; 
    return ret;

}

// int main()
// {
//     int& a = func(1 , 2);
//     cout << a << endl;

//     func(100 , 200);
//     cout << a << endl;

//     printf("!!!!!!");
//     cout << a << endl;
//     return 0;
// }

//CPP写法
void Swap(int& rx, int& ry)
{
    int tmp = rx;
    rx = ry;
    ry = tmp;
}

void Swap(double& rx, double& ry)
{
    double tmp = rx;
    rx = ry;
    ry = tmp;
}

//C语言写法
void Swap(int* rx, int* ry)
{
    int tmp = *rx;
    *rx = *ry;
    *ry = tmp;
}



#include<iostream>
using namespace std;
int main()
{
    int a = 0;
    // 引⽤：b和c是a的别名
    cout << a << endl;

    int& b = a;
    int& c = a;
    // 也可以给别名b取别名，d相当于还是a的别名
    int& d = b;
    ++d;
    // 这⾥取地址我们看到是⼀样的
    
    cout << &a <<endl;
    cout << &b << endl;
    cout << &c << endl;
    cout << &d << endl;
    cout << a << endl;

    //引用加函数重载 十分好用 便捷
    int x = 0, y = 1;
    cout << x <<" " << y << endl;
    Swap(x, y);
    cout << x << " " << y << endl;

    double m = 1.1 , n = 1.0;
    cout << m <<" " << n << endl;
    Swap(m ,n);
    cout << m <<" " << n << endl;

    return 0;
}

//ps：也有指针专门使用的地方 就是树形结构和链式结构的时候 指针是不可替代的

//2.2 引用的特性 1.引用必须在定义的时候初始化 2.一个变量可以有多个引用 3.引用了一个实体之后不能引用另一个



//三、const 引用

int main()
{
    //权限不能放大 a 是 const int 类型, r是 int类型的别名 权限放大了
    const int a = 1;
    //int& r = a; 这是错误的
    const int& r = a;//这样就平等了 是被允许的

    //权限可以缩小
    int b = 2; //这里的b可以读 也可以修改
    const int& rr = b;//这里的rr 作为别名只能读 不能修改

    const int* m = &a;
    const int* n = &b;

    int c = a ; //这里没有权限的放大 因为复制时一种拷贝 本质时a拷贝给c c的改变不会影响a

    int d = 1;
    double e = d;
    const double& re = d; //d-> double临时变量 ->double
    //double 临时变量具有常性 所以权限放大了 要加const
    //总的来说 只有指针和引用才有权限的放大和缩小 
    return 0 ;
}

typedef int Type;
void Push(const Type& x);
//这里的形参不进行修改 加上const 相当于缩小权限 也保证了安全性
//还有这里的const& 可以省去复制和限制修改 提高运行效率
//使用场景：未知类型 大对象  

 

//四、指针和引用的关系
//1.语法概念上引⽤是⼀个变量的取别名不开空间，指针是存储⼀个变量地址，要开空间
//2.引⽤在定义时必须初始化，指针建议初始化，但是语法上不是必须的。
//3.引⽤在初始化时引⽤⼀个对象后，就不能再引⽤其他对象；⽽指针可以在不断地改变指向对象
//4.引⽤可以直接访问指向对象，指针需要解引⽤才是访问指向对象
//5.• 指针很容易出现空指针和野指针的问题，引⽤很少出现，引⽤使⽤起来相对更安全⼀些


int main()
{
    //语法上不开空间（但是汇编底层上也是开空间的）
    int a = 1;
    int& ra = a;
    ra += 1;

    //语法上要开一个指针大小空间
    int* pa = &a;
    *pa += 1;

    return 0;
}


//五、inline 内联函数（适合代码短、调用频繁的小函数)
//前提：inline 不保证一定展开，由编译器决定
//用inline修饰的函数叫做内联函数,编译时C++编译器会在调用的地方展开内联函数
//这样调用内联函数就不需要建立栈帧了，就可以提⾼效率
//C语⾔实现宏函数也会在预处理时替换展开，
//但是宏函数实现很复杂很容易出错的，且不方便调试，C++设计了inline目的就是替代C的宏函数

//注意！:inline不建议声明和定义分离到两个⽂件，分离会导致链接错误。
//因为inline被展开，就没有函数地址，链接时会出现报错。

//宏函数是一种替换 不是函数
#define ADD(x , y) x+y;
#define ADD(x , y) x+y
#define ADD(x , y) (x+y)
#define ADD(x , y) ((x)+(y))

inline int Add(int x , int y)//省去进入函数、返回调用处等开销 提高效率
{
    return x + y;
}


int main()
{
    int ret = ADD(1,2);
  //int ret = x+y;;
  //int ret = x+y;
  //int ret = (x+y);
  //int ret = ((x)+(y));
  //保证运算符的优先级 而且x,y 可能是表达式

    int ret = Add(1,2);
  //int ret = 1 + 2; 

  

}
