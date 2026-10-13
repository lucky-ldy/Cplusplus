//一、赋值运算符重载
//1.1 运算符重载

//1_1 当运算符被⽤于类类型的对象时，C++语⾔允许我们通过运算符重载的形式指定新的含义
//1_2 C++规定类类型对象使⽤运算符时，必须转换成调⽤对应运算符重载，
//若没有对应的运算符重载，则会编译报错

//1_3 运算符重载是具有特殊名字的函数 他的名字是由operator和后⾯要定义的运算符共同构成
//和其他函数⼀样，它也具有其返回类型和参数列表以及函数体

//1_4 重载运算符函数的参数个数与运算对象数量相同。
// 一元运算符：一个参数。
// 二元运算符：两个参数，左侧对象传给第一个参数，右侧对象传给第二个参数


#include<iostream>
using namespace std;

// 编译报错：“operator +”必须⾄少有⼀个类类型的形参
// int operator+(int x, int y)
// {
//     return x - y;
// }

// class A
// {
// public:
//     void func()
//     {
//         cout << "A::func()" << endl;
//     }
// };

// class Date
// {

// public:
//     Date()
//     {
//         _year = 2026;
//         _month = 10;
//         _day =12;
//     }
//     Date(int year , int month , int day)
//     {
//         _year = year;
//         _month = month;
//         _day = day;
//     }
//     //函数写到内部时候 因为内部调用参数有一个this指针所以参数要修改
//     bool operator==(/*Date* const this,*/ const Date& d)
//     {
//         //这里this可省略
//         return this->_year == d._year
//         &&     this->_month == d._month
//         &&     this->_day == d._day;
//     }
//     //调用的时候也要改变成 d1.operator==(d2);
//     //d1 == d2;

//     //d1 > d2
//     bool operator>(const Date* d)
//     {
//         if(_year > d->_year)    return true;
//         else if(_year == d->_year)
//         {
//             if(_month > d->_month)  return true;
//             else if(_month == d->_month)
//             {
//                 return _day > d->_day;
//             }
//         }
//         return false;

//     }   
// private:
// // 成员都是内置类型不做处理
//     int _year;
//     int _month;
//     int _day;

// };

//运算符重载要用到内部成员变量的时候 有以下解决办法
    //1.把内部成员函数变成公有 简单操作 但是有点不妥当
    //2.写一个读取函数 int GetYear(){ return _year;} 让外部可以读取到内置成员
    //3.重载运算符函数写到类内部
//  bool operator==(const Date& x1 , const Date& x2)
// {
//         return x1._year == x2._year
//         &&x1._month == x2._month
//         &&x1._day == x2._day;
// }

// int main()
// {
//     Date d1(2026,10,12);
//     Date d2(2026,10,13);

//     //运算符重载
//     //在全局定义
//     // cout << operator==(d1,d2) << endl;
//     // cout << (d1 == d2) << endl;

//     //在类内部定义
//     cout << (d1 == d2) << endl;
//     cout << d1.operator==(d2) << endl;
//     return 0;
// }

//------------------------------------

//二、实现声明和定义分明日期类
#include "10.13.h"

Date::Date(int year  , int month , int day)
{
    _year = year;
    _month = month;
    _day = day;
}

bool Date::operator==(const Date& d)
{
    return this->_year == d._year
    &&     this->_month == d._month
    &&     this->_day == d._day;
}

bool Date::operator>(const Date& d)
{
    if(_year > d._year)    return true;
    else if(_year == d._year)
    {
        if(_month > d._month)  return true;
        else if(_month == d._month)
        {
            return _day > d._day;
        }
    }
    return false;
}

int GetMonthDay(int year , int month)
{
    assert(month > 0 && month < 13);
    int monthDayArr[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    if(month == 2 && ((year % 4 == 0 && year % 100 !=0) || year % 400 == 0))
        return 29; 

    return monthDayArr[month];
}

//d1 += 100
 Date& Date::operator+=(int day) 
 {
    _day += day;
    while(_day > GetMonthDay(_year , _month))
    {
        _day -= GetMonthDay(_year , _month);
        _month++;
        if(_month == 13)
        {
            ++_year;
            _month = 1;
        }
    }
    return *this;
    //this指向对象 *this就是对象类型
 }

 //d1 + 100
Date Date::operator+(int day) 
{
    Date tmp = *this;
    tmp += day;
    return tmp;
}

//++d; 返回++之后的值
Date& Date::operator++()
{
    *this += 1;
    return *this;
}

//d++; 返回++之前的值
Date Date::operator++(int)
{
    Date tmp(*this);
    *this += 1;

    return tmp;
}

class A
{
public:
    void func()
    {
        cout << "调用了 func" << endl;
    }
};


 //成员函数的函数指针
// A::*	指向 A 类的非静态成员函数
// ()	指向的函数没有参数
// PF	给这种指针类型起的名字
//  typedef void (A::*PF)();
//要指定类域

//  int main()
//  {

//     // C++规定成员函数要加&才能取到函数指针
//     //pf 是指针变量。
//     //&A::func 表示取得成员函数 func 的指针。
//     PF pf = &A::func;
//     A obj;//定义ob类对象temp
//     // 对象调⽤成员函数指针时，使⽤.*运算符
//     (obj.*pf)();
//     //因为 pf 指向 A::func，所以这里相当于：obj.func();

//     Date d1(2026 , 10 , 14);
//     Date d2(2026 , 8 , 6);
//     d1.Print();
//     d2.Print();

//     Date d5 = d1++;
//     Date d6 = ++d1;
//     d5.Print();
//     d6.Print();    
    
//     cout << (d1 == d2) <<endl;
//     cout << (d1 > d2) << endl; 

//     Date d3 = d2 += 100;
//     d3.Print();
//     d2.Print();
//     Date d4 = d2 + 100;
//     d4.Print(); 
//     d2.Print();


//  }

 
//1.2 赋值运算符重载

//1_1 赋值运算符重载是⼀个运算符重载，规定必须重载为成员函数！
//1_2 有返回值，且建议写成当前类类型引⽤ 提高运行效率
//1_3 如果⼀个类显⽰实现了析构并释放资源，那么他就需要显⽰写赋值运算符重载，否则就不需要
#include <iostream>

using namespace std;

Date& Date::operator=(const Date& d)
{
    //防止自己给自己赋值 提高运行效率
    if(this != &d)
    {
        _year = d._year;
        _month = d._month;
        _day = d._day;
        return *this;
    }
} 

int main()
{
    Date d1(2026,10,13);
    Date d2(2026,10,14);
    //拷贝构造，一个已经存在的对象取初始化一个要创建的对象
    Date d3(d1);
    Date d4 = d1;
    d3.Print();
    d4.Print();

    //赋值重载, 一个已经存在的对象拷贝给另一个已经存在的对象
    d1 = d2 = d3;
    d1 = d2;
    d1.Print();
    d2.Print();

}



//二、补充总结：Date、Stack、MyQueue 的默认赋值与深浅拷贝


//      需要手动实现的
//Date  构造
//Stack 构造 析构 拷贝构造 赋值重载
//MyQueue 无


//1.没有自己写 operator= 时，编译器通常会自动生成，按成员进行赋值。
//  内置类型成员：复制值；指针只复制地址，不复制它指向的数据。
//  自定义类型成员：调用该成员所属类的 operator=。
//  注意：逐成员赋值不等于把整个对象简单地逐字节复制。

//2.Date：成员都是 int，默认赋值已经够用，不必自己写 operator=。
//  Date d1(2026, 10, 13);
//  Date d2(2025, 1, 1);
//  d2 = d1;                     //两个对象都已经存在，这是赋值
//  默认赋值效果相当于：
//  d2._year  = d1._year;
//  d2._month = d1._month;
//  d2._day   = d1._day;
//  两个对象各自保存年月日，修改 d2 不影响 d1。
//  上面访问私有成员的代码仅用于说明内部赋值效果。

//3.Stack：_a 是指针，默认赋值只复制地址，属于浅拷贝。
//  s2 = s1;
//  默认赋值效果相当于：
//  s2._a        = s1._a;        //只复制地址！没有创建新数组
//  s2._top      = s1._top;
//  s2._capacity = s1._capacity;
//  s1._a 和 s2._a 指向同一个数组：修改数据会互相影响，析构可能重复释放。
//  如果 s2 原来还有自己的数组，直接覆盖其指针还会造成内存泄漏。
//  深拷贝的核心步骤示意（假设 _top 表示有效元素个数）：
//  Stack& operator=(const Stack& s)
//  {
//      if (this != &s)                         //防止自身赋值
//      {
//          int* newArray = new int[s._capacity];
//          for (int i = 0; i < s._top; ++i)
//              newArray[i] = s._a[i];          //复制数组数据
//          delete[] _a;                       //释放左侧对象的旧数组
//          _a = newArray;                     //接管自己的新数组
//          _top = s._top;
//          _capacity = s._capacity;
//      }
//      return *this;                          //放在 if 外，自身赋值也返回
//  }
//  注意：申请与释放必须配套；new[] 对应 delete[]，malloc 对应 free。
//  深拷贝后：s1._a 指向数组1，s2._a 指向数组2，数据相同但内存独立。

//4.MyQueue：内部由两个 Stack 组成，让 Stack 自己负责复制。
//  class MyQueue
//  {
//      Stack s1;
//      Stack s2;
//  };
//  q2 = q1;
//  默认赋值效果相当于：
//  q2.s1 = q1.s1;               //调用 Stack::operator=
//  q2.s2 = q1.s2;               //调用 Stack::operator=
//  只要 Stack 的赋值重载已正确实现深拷贝，MyQueue 通常不必自己写。

//5.区分拷贝构造和拷贝赋值：
//  Date d2 = d1;                //创建新对象：拷贝构造
//  d2 = d1;                     //给已有对象赋值：拷贝赋值
//  自己管理动态资源的类，通常要同时考虑析构、拷贝构造、拷贝赋值。
//  判断关键：默认的逐成员复制能否满足需求，而不是仅看有没有析构函数。