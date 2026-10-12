//一、类的默认成员函数
//默认成员函数就是⽤⼾没有显式实现，编译器会⾃动⽣成的成员函数称为默认成员函数
//编译器会默认⽣成以下6个默认成员函数，需要注意的是这6个中最重要的是前4个，最后两个取地址重载不重要

//默认成员函数很重要，也⽐较复杂，我们要从两个⽅⾯去学习
//1、我们不写的时候 编译器默认生成的函数行为是什么 是否满足我们的要求
//2、编译器默认生成的函数不满足我们的需求 我们需要自己实现 如何实现？

//6个默认成员函数 1.初始化（Init)和清理(Destory) 2.拷贝赋值 3.取地址重载


//1.1 构造函数 
//构造函数是特殊的成员函数，需要注意的是，构造函数虽然名称叫构造 
//但是构造函数的主要任务并不是开空间创建对象 ⽽是对象实例化时初始化对象(Init)
//构造函数的本质是要替代我们以前Stack和Date类中写的Init函数的功能

//构造函数的特点 1.函数名与类名相同 2.无返回值(也不需要写void) 3.对象实例化时系统会⾃动调⽤对应的构造函数
//4.构造函数可以函数重载 5.如果类中没有显式定义构造函数，则C++编译器会⾃动⽣成⼀个⽆参的默认构造函数 一旦显式定义构造函数 编译器将不再生成
//6.不只有编译器自动生成的叫默认构造 实际上⽆参构造函数、全缺省构造函数也是默认构造，总结⼀下就是不传实参就可以调⽤的构造就叫默认构造。
//7.编译器默认⽣成的构造，对内置类型成员变量的初始化没有要求
// 对于⾃定义类型成员变量，要求调⽤这个成员变量的默认构造函数初始化
//如果这个类成员变量，没有默认构造函数


#include <iostream>

using namespace std;

// class Date
// {

// public:
//     Date()
//     {
//         _year = 2026;
//         _month = 10;
//         _day =12;
//     }
// //可以直接用全缺省 把无参和有参数合并 这样在调用Date d1;的时候就不会有歧义
//     // Date(int year = 1, int month = 1, int day = 1)
//     // {
//     //     _year = year;
//     //     _month = month;
//     //     _day = day;
//     // }

//     //这是显式定义构造 如果只定义这一个函数没有Date() 那在调用Date d1;的时候就不再⽣成
//     Date(int year, int month, int day)
//     {
//         _year = year;
//         _month = month;
//         _day = day;
//     }


// private:
// // 成员都是内置类型不做处理
//     int _year;
//     int _month;
//     int _day;

// };

// typedef int STDataType;
// class Stack
// {
// public:
//     Stack(int n = 4)
//     {
//         _a = (STDataType*)malloc(sizeof(STDataType) * n);
//         if(nullptr == _a)
//         {
//             perror("malloc申请空间失败");
//             return;
//         }
//         _capacity = n;
//         _top = 0;
//     }

// private:
//     STDataType* _a;
//     size_t _capacity;
//     size_t _top;
// };

// //用两个栈实现一个队列(实现封装)
// class Myqueue
// {
// private:
//     //默认构造 对类类型这种自定义类型成员会调用它的默认构造 可以不写构造
//     //类类型成员
//     Stack _st1;
//     Stack _st2;

// };


// int main()
// {
//     Date d1;// 对象实例化自动调用构造函数 初始化
//   //Date d1();//不能这样写 这样会被认为是函数声明
//     Date d2(2026, 10, 13); //对象实例化

//     Stack st1;
//     Stack st2(100);

//     Myqueue m1;//这里对象实例化 自动调用Stack类的默认构造

//     return 0;
// }




//1.2 析构函数(和构造函数大致相反)
//C++规定对象在销毁时会⾃动调⽤析构函数，完成对象中资源的清理释放⼯作
//析构函数的功能类⽐我们之前Stack实现的Destroy功能

//析构函数的特点 1.析构函数名是在类名前加上字符 ~   2. ⽆参数⽆返回值 3.⼀个类只能有⼀个析构函数
//4.对象⽣命周期结束时，系统会⾃动调⽤析构函数 5.跟构造函数类似 内置类型不做处理 自定类型会调用他的析构函数
//6.⾃定义类型成员⽆论什么情况都会⾃动调⽤析构函数
//7.如果默认⽣成的析构就可以⽤，也就不需要显⽰写析构，如MyQueue；但是有资源申请时，⼀定要⾃⼰写析构，否则会造成资源泄漏，如Stack。
//8.⼀个局部域的多个对象，C++规定： 后定义的 先析构

#include<iostream>
using namespace std;

typedef int STDataType;
// class Stack
// { 
// public:
//     //构造函数
//     Stack(int n = 4)
//     {
//         _a = (STDataType*)malloc(sizeof(STDataType) * n);
//         if (nullptr == _a)
//         {
//             perror("malloc申请空间失败");
//             return;
//         } 
//         _capacity = n;
//         _top = 0;
//     } 
//     //析构函数
//     ~Stack()
//     {
//         cout << "~Stack()" << endl;
//         free(_a);
//         _a = nullptr;
//         _top = _capacity = 0;
//     }

// private:
//     STDataType* _a;
//     size_t _capacity;
//     size_t _top;
// };

// class MyQueue
// {
// public:
//     ~MyQueue()
//     {
//         cout << "~MyQueue()" << endl;
//     }

// private:
//     Stack pushst;
//     Stack popst;

// };

// int main()
// {
//     //后定义的先析构 
//     Stack st;
//     MyQueue mq;
//     return 0;

// }


//1.3 拷贝构造函数
//⼀个构造函数的第⼀个参数是⾃⾝类类型的引⽤，且任何额外的参数都有默认值
//拷贝构造函数的特点:1.拷⻉构造函数是构造函数的⼀个重载 2.拷⻉构造函数的第⼀个参数必须是类类型对象的引⽤
//3.⾃动⽣成的拷⻉构造对内置类型成员变量会完成值拷⻉/浅拷⻉(⼀个字节⼀个字节的拷⻉)，对⾃定义类型成员变量会调⽤他的拷⻉构造。
class Date
{
public:
    Date()
    {
        _year = 2026;
        _month = 10;
        _day =12;
    }

    //拷贝构造函数
    //Date d3(d2); this指向d3 形参d是d2的别名 将d2 拷贝到 d3
    // Date(const Date& d)
    // {
    //     _year = d._year;
    //     _month = d._month;
    //     _day = d._day;

    // }

    Date(int year, int month, int day)
    {
        _year = year;
        _month = month;
        _day = day;
    }

    void Print()
    {
        cout<< _year << "/" << _month << "/" << _day << endl;
    }

private:
// 成员都是内置类型不做处理
    int _year;
    int _month;
    int _day;

};


typedef int STDataType;
class Stack
{
public:
    Stack(int n = 4)
    {
        _a = (STDataType*)malloc(sizeof(STDataType) * n);
        if(nullptr == _a)
        {
            perror("malloc申请空间失败");
            return;
        }
        _capacity = n;
        _top = 0;
    }

    //Stack st2(&st1) 深拷贝
    //创建一个新栈 单独写一个拷贝函数
    Stack(const Stack& st)
    { 
        // 需要对_a指向资源创建同样⼤的资源再拷⻉值
        _a = (STDataType*)malloc(sizeof(STDataType) * st._capacity);
        if (nullptr == _a)
        {
            perror("malloc申请空间失败!!!");
            return;
        } 
        memcpy(_a, st._a, sizeof(STDataType) * st._top);
        _top = st._top;
        _capacity = st._capacity;
    }

private:
    STDataType* _a;
    size_t _capacity;
    size_t _top;
};

//用两个栈实现一个队列(实现封装)
class Myqueue
{
private:
    //默认构造 对类类型这种自定义类型成员会调用它的默认构造 可以不写构造
    //类类型成员
    Stack _st1;
    Stack _st2;

};


int main()
{
    Date d1;
    Date d2(2026,10,12);
    //拷贝构造
    Date d3(d2);//把d2拷贝给d3
    Date d4 = d2;//把d2拷贝给d3

    d3.Print();
    d4.Print();

    Stack st1;
    Stack st2 = st1;
//(在没有单独写栈的拷贝函数的时候)这样拷贝会让两个指针指向同一块空间 导致函数结束 st1 st2 析构同一块空间两次 就报错了 

//在单独写了类类型成员的拷贝函数之后 
    Myqueue q1;
    Myqueue q2(q1);
//这里q1 q2 都是使用的各自的空间不会出现报错
}

 