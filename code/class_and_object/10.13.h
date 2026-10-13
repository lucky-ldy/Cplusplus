#include<iostream>
#include<assert.h>
using namespace std;

class Date
{

public:
    Date(int year=2026 , int month=10 , int day=13);
    //类里面直接定义的函数 默认是inline 不能声明和定义分离
    void Print()
    {
        cout << _year << "/" << _month << "/" << _day << endl;
    }

    bool operator==(/*Date* const this,*/ const Date& d);
    bool operator>(const Date& d);
    bool operator>=(const Date& d);
    bool operator<(const Date& d);
    bool operator<=(const Date& d);
    bool operator!=(const Date& d);
    //用引用返回 减少拷贝次数 还能支持连续操作    
    Date& operator+=(int day);
    Date operator+(int day);

    //++d; d++; 怎么区分
    //C++规定对后置增加⼀个int形参，跟前置++构成函数重载，⽅便区分
    Date& operator++();//++d
    Date operator++(int);//d++

    //拷贝构造
    Date(const Date& d)
    {
        _year = d._year;
        _month = d._month;
        _day = d._day;
    }
    //赋值重载
    Date& operator=(const Date& d);

private:
// 成员都是内置类型不做处理
    int _year;
    int _month;
    int _day;

};
