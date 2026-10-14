//一、运算符重载的应用——完善日期的功能
#include "10.14.h"

Date::Date(int year  , int month , int day)
{
    _year = year;
    _month = month;
    _day = day;

    if(!IsValid())
    {
        cout << *this << "构造日期非法" << endl;
        
    }
}

bool Date::operator==(const Date& d) const
{
    return this->_year == d._year
    &&     this->_month == d._month
    &&     this->_day == d._day;
}


bool Date::operator>(const Date& d) const
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


bool Date::operator>=(const Date& d) const
{
    // if(_year > d._year)    return true;
    // else if(_year == d._year)
    // {
    //     if(_month > d._month)  return true;
    //     else if(_month == d._month)
    //     {
    //         return _day >= d._day;
    //     }
    // }
    // return false;

    //直接复用 > 和 == 重载运算符
    return *this > d || *this == d ;
}

bool Date::operator<(const Date& d) const
{
    //再次复用 互斥的逻辑 <就是>=取反
    return !(*this >= d);
}

bool Date::operator<=(const Date& d) const
{
    //再次复用 互斥的逻辑  <= 就是 > 取反
    return !(*this > d);
}

bool Date::operator!=(const Date& d) const
{
    //不等于就是等于取反
    return !(*this == d);
}


int GetMonthDay(int year , int month)
{
    assert(month > 0 && month < 13);
    int monthDayArr[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    if(month == 2 && ((year % 4 == 0 && year % 100 !=0) || year % 400 == 0))
        return 29; 

    return monthDayArr[month];
}

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

Date Date::operator+(int day) const
{
    Date tmp = *this;
    tmp += day;
    return tmp;
}

Date& Date::operator-=(int day)
{
    //这里有三次拷贝
    //按照+=的逻辑去写是没有拷贝的
    //所以复用+= 或者 -=  写 + 和 - 是更好的方式
    // *this = *this - day;
    // return *this;

    //这种方式更好 
    _day -= day;
    while(_day < 1)
    {
        --_month;
        if(_month == 0)
        {
            --_year;
            _month = 12;
        }
        _day += GetMonthDay(_year , _month);
    }
    return *this;

}

Date Date::operator-(int day) const
{
    // Date tmp = *this;
    // tmp._day -= day;
    // while(tmp._day < 1)
    // {
    //     --tmp._month;
    //     if(tmp._month == 0)
    //     {
    //         --tmp._year;
    //         tmp._month = 12;
    //     }
    //     tmp._day += GetMonthDay(tmp._year , tmp._month);
    // }
    // return tmp;

    //复用-= 实现-的方式更好
    Date tmp(*this);
    tmp -= day;
    return tmp;
}

int Date::operator-(const Date& d) const
{
    Date max = *this;
    Date min = d;
    int flag = 1;
    if(*this < d)
    {
        max = d;
        min = *this;
        flag = -1;
    }
    int n = 0;
    while(min != max)
    {
        min+=1;
        ++n;
    }
    return n*flag;


}

bool Date::IsValid() const
{
    if(_year < 1)   return false;
    if(_month < 1 || _month > 12)   return false;
    if(_day < 1 || _day > GetMonthDay(_year,_month))    return false;
    return true;
}

//重载<<为全局函数 可以控制流对象和成员函数的位置 但是这样就不能访问私有成员函数
ostream& operator<<(ostream& _cout , const Date& d)
{
    _cout << d._year << "/" << d._month << "/" << d._day << endl;
}

istream& operator>>( istream& _cin ,  Date& d)
{
    while(1)
    {
        cout<< "请依此输入年月日:>" ;
        _cin >> d._year >> d._month >> d._day ;
        if(d.IsValid())
        break;
        else
        cout << "日期非法,请重新输入" << endl;
    }
}

//cin：输入输出会改变流对象的内部状态，所以第一个参数不能加 const。 

// int main()
// {   
//     Date d1(2026 , 10 , 14);
//     Date d2(2026 , 10 , 15);
//     d1.Print();
//     d2.Print();

//     Date d3(d1);

//     cout << (d1 < d2) << endl;
//     cout << (d1 > d2) << endl;
//     cout << (d1 == d3) << endl;

//     Date d4 = d1 - 15;
//     Date d5 = d2 - 16;
//     d4.Print();
//     d5.Print();
    
//     cout << (d2 - d1) << endl;
//     cout << (d1 - d2) << endl;
    
//     //测试非法日期
//     Date d6(2026 ,10 , 32);
    
//     //运算符重载要满足左侧操作数是第一个参数 右侧是第二个参数
//     //左侧是this 指针要指向类对象
//     //cout<< d1;//错误
//     //d1 << cout;//正确
//     Date d;
//     cin >> d;
//     cout << d;


// }

//二、取地址运算符重载

//2.1 const成员函数
//1.取地址运算符重载分为普通取地址运算符重载和const取地址运算符重载
//2.const实际修饰该成员函数隐含的this指针，表明在该成员函数中不能对类的任何成员进⾏修改

#include<iostream>
using namespace std;
class Date0
{
public:
    Date0(int year = 1, int month = 1, int day = 1)
    {
        _year = year;
        _month = month;
        _day = day;
    }
    // void Print(const Date* const this) const
    void Print() const//加上const后 就可以接收const Date* 和 Date*
    {
        cout << _year << "-" << _month << "-" << _day << endl;
    }
private:
    int _year;
    int _month;
    int _day;
};

void TestDate()
{
    const Date d3(2026,10,14);
    Date d4(2026,10,15);
    d3.Print();//这里调用不了Print因为权限放大了
    //const Date* -> Date*
    d4.Print(); //Date* -> Date*

}
// int main()
// {
//     // 这⾥⾮const对象也可以调⽤const成员函数是⼀种权限的缩⼩
//     Date d1(2024, 7, 5);
//     d1.Print();
//     const Date d2(2024, 8, 5);
//     d2.Print();
//     return 0;
// }


//2.2取地址运算符重载
//取地址运算符重载分为普通取地址运算符重载和const取地址运算符重载
//一般自动生成的就够我们用了 
//如果我们不想让别人取到当前类对象的地址就可以自己构造

class Date1
{
public:
//他们构成函数重载
    Date1* operator&()
    {
        //return this;
        //return nullptr; 让编译器调用运算符重载 这样别人就永远取不到你的地址
        return (Date1*)0x11234f000;//传一个随机地址
    }
    const Date1* operator&() const
    {
        //return this;
        return (const Date1*)0x11234f004;
    
    }
private:
    int a;
    int b;
    int c;

};

int main()
{
    Date1 d1;
    const Date d2;
    cout << &d1 << endl;
    cout << &d2 << endl;
}

