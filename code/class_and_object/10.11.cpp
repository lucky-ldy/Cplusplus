//一、类的定义

//为了区分成员变量，⼀般习惯上成员变量会加⼀个特殊标识
//如成员变量前⾯或者后⾯加_ 或者 m 开头  _year 
//驼峰法 类 函数这样写：StackInit  变量这样写：tempTop
//或者有的用下划线分割 stack_init 具体看公司要求


#include <iostream>
using namespace std;
//class为定义类的关键字，Stack为类的名字，{}中为类的主体
//注意! 类定义结束时后⾯分号不能省略。

// class Stack
// {

// public:
   
//     void Init(int n =4);
//     void Push(int x);

// private:

//     int* _a;
//     int _top;
//     int _capacity;

// };
//注意区分 这两个类里面 定义的函数名相同 但是不是函数重载 因为他们在不同的类域里面
class Queue
{
public:
    void Init();
    void Push(int x);

};

//1.1 struct 和 class 区别
//C++中struct也可以定义类，C++兼容C中struct的⽤法，同时struct升级成了类
//明显的变化是struct中可以定义函数，⼀般情况下我们还是推荐⽤class定义类。

//特殊的是 - struct：结构体关键字。
//        - class：类关键字。
//两者都能定义类型，都能包含成员变量和成员函数。 最主要的区别是默认访问权限
//struct 默认公开，class 默认私有

// struct A
// {
//     int x;  // 默认 public，类外可以访问
// };

// class B
// {
//     int x;  // 默认 private，类外不能直接访问
// };

// int main()
// {
//     A a;
//     a.x = 10;  // 可以

//     B b
// //    b.x = 10;  // 报错，x 是私有成员
//     Stack q;
//     Queue p;
//     q.Push(1);
//     p.Push(1);

// }
 

//1.2 访问限定符

// C++⼀种实现封装的⽅式，⽤类将对象的属性(成员)与⽅法(函数)结合在⼀块，让对象更加完善
//通过访问权限 选择性的将接口提供给外部使用
//访问限定符有三种 1.公有public 2.私有private 3.保护protected
//public修饰的成员在类外可以直接被访问 
//protected和private修饰的成员在类外不能直接被访问
// 在继承部分的时候才能体现protected 和 private 的区别


// class Date
// {

// //访问权限作⽤域从该访问限定符出现的位置开始直到下⼀个访问限定符出现时为止
// //如果后⾯没有访问限定符，作用域就到 }即类结束
// public:
//     //成员函数大部分是公有的
//     void Init(int year , int month , int day)
//     {
//         _year = year;
//         _month = month;
//         _day = day;

//     }

// private:
//     //成员变量大部分是私有的
//     int _year;
//     int _month;
//     int _day; 

// }; 

//1.3 类域
//类定义了⼀个新的作⽤域，类的所有成员都在类的作⽤域中
//在类体外定义成员时，需要使⽤ :: 作⽤域操作符指明成员属于哪个类域
// #include<iostream>
// using namespace std;

// class Stack
// {
// public:
//     // 成员函数
//     void Init(int n = 4);
// private:
//     // 成员变量
//     int* array;
//     size_t capacity;
//     size_t top;
// };

// // 声明和定义分离，需要指定类域
// void Stack::Init(int n)
// {
//     array = (int*)malloc(sizeof(int) * n);
//     if (nullptr == array)
//     {
//         perror("malloc申请空间失败");
//         return;
//     }
//     capacity = n;
//     top = 0;
// }

// int main()
// {
//     //类实例化对象
//     Stack st;
//     st.Init();
//     return 0;
// }



//二、实例化
// 用类类型在物理内存中创建对象的过程，称为类实例化出对象 
//类是对象进⾏⼀种抽象描述 是⼀个模型⼀样的东西（类似画的建筑图纸），限定了类有哪些成员变量
//这些成员变量只是声明，没有分配空间，用类实例化出对象时，才会分配空间
//类->对象
//一 对 多

//2.1 类域

#include <iostream>
using namespace std;

// class Date
// {

// public:
//     //成员函数大部分是公有的
//     void Init(int year , int month , int day)
//     {
//         Date::year = year; //成员变量和形参同名的时候 要指定类域
//         _month = month;
//         _day = day;
//     }

//     void Print()
//     {
//         cout << Date::year << '/' << _month << '/' << _day <<endl;
//     }
// private:
//     //成员变量大部分是私有的
//     int year;
//     int _month;
//     int _day; 

// }; 

// int main()
// {
//     //类实例化对象
//     Stack s;

//     //Stack::_top = 1; 
// //不能通过类直接访问成员变量赋值 因为类没有给成员变量开空间 仅仅只是声明了
//     //s._top = 1;  //只能通过实例化对象来访问
//     Date m1;
//     m1.Init(2026 , 10 ,11);
//     m1.Print();

//     Date m2;
//     m2.Init(2026 , 10 ,12);
//     m2.Print();
// }


//2.2 对象大小
//Date实例化d1和d2两个对象，d1和d2都有各自独立的成员变量
//_year/_month/_day存储各自的数据，
//但是d1和d2的成员函数Init/Print指针却是⼀样的，存储在对象中就浪费了。

//其实函数指针是不需要存储的，函数指针是⼀个地址
//其实编译器在编译链接时，就要找到函数的地址
#include<iostream>
using namespace std;
// 计算⼀下A/B/C实例化的对象是多⼤？
class A
{
public:
    void Print()
    {
        cout << _ch << endl;
    }

private:
    char _ch;
    int _i;
};

class B
{
public:
    void Print()
    {
    //...
    }
};

class C
{};

// int main()
// {
//     A a;
//     B b;
//     C c;
//     cout << sizeof(a) << endl;//8
//     cout << sizeof(b) << endl;//1
//     cout << sizeof(c) << endl;//1
//     //成员函数不占存储空间 没有成员变量的类的空间大小都是1
//     //这里给1字节 纯粹是为了占位表示对象存在 是占位空间
//     return 0;
// }


//三、this指针
//编译器编译后，类的成员函数默认都会在形参第⼀个位置，增加⼀个当前类类型的指针，叫做this指针
//void Init(Date* const this, int year,int month, int day) 
//不能显式写出来 编译器已经帮我们指出来了 但是可以在函数体内显式使用this指针
//类的成员函数中访问成员变量，本质都是通过this指针访问的
//如Init函数中给_year赋值， this->_year = year;

//this指针存在内存的栈上 因为this指针是函数的隐含参数 所以在栈上

#include<iostream>
using namespace std;

class Date
{
public:
// void Init(Date* const this, int year, int month, int day)
    void Init(int year, int month, int day)
    {
        // 编译报错：error C2106: “=”: 左操作数必须为左值
        // this = nullptr;
        // this->_year = year;
        _year = year;
        this->_month = month;
        this->_day = day;
    }

//这里明明是一样的Print函数为什么打印的值不一样
//实际上编译器会对Print()进行处理成 Print(Date* this)
    //     void Print(Date* this)
    // {
    //     cout << this->_year << "/" << this->_month << "/" << this->_day << endl;
    // }
    void Print()
    {
        cout << this << endl;
        cout << _year << "/" << _month << "/" << _day << endl;
    }

private:
// 这⾥只是声明，没有开空间
    int _year;
    int _month;
    int _day;
};

// int main()
// {
// //类实例化对象
//     Date m1;
//     m1.Init(2026 , 10 ,11);
//     m1.Print();
//     //m1.Print(&m1); 编译器处理

//     Date m2;
//     m2.Init(2026 , 10 ,12);
//     m2.Print();
//     //m1.Print(&m2);

// }


//四、C++和C语⾔实现Stack对⽐

// C++ ⾯向对象三⼤特性：封装、继承、多态，下面的对比我们可以初步了解一下封装
//C++中数据和函数都放到了类里面，通过访问限定符进⾏了限制，不能再随意通过对象直接修改数据
//这是C++封装的一种体现，这个是最重要的变化
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

using namespace std;

typedef int STDataType;
class Stack
{
public:
    //成员函数
    void Init(int n = 4)
    {
        _a = (STDataType*)malloc(sizeof(STDataType) * n);
        if(nullptr == _a)
        {
            perror("malloc申请空间失败");
            return ;
        }
        _capacity = n;
        _top = 0;

    }

    void Push(STDataType x)
    {
        if(_top == _capacity)
        {
            int newcapacity = _capacity * 2;
            STDataType* tmp = (STDataType*)realloc(_a , newcapacity * sizeof(STDataType));
            if(tmp == NULL)
            {
                perror("realloc fail");
                return;
            }
            _a = tmp;
            _capacity = newcapacity;
        }
        _a[_top++] = x;

    }

    void Pop()
    {
        assert(_top > 0);
        --_top;
    }

    bool Empty()
    {
        return _top == 0;
    }

    int Top()
    {
        assert(_top > 0);
        return _a[_top - 1];
    }

    void Destroy()
    {
        free(_a);
        _a = nullptr;
        _top = _capacity = 0;
    }

private:
    //成员变量
    STDataType* _a;
    size_t _capacity;
    size_t _top;
};

int main()
{
    Stack s;
    s.Init();
    s.Push(1);
    s.Push(2);
    s.Push(3);
    s.Push(4);

    while(!s.Empty())
    {
        printf("%d\n" , s.Top());
        s.Pop();
    }

    s.Destroy();
    return 0;
}



