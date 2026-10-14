#include<iostream>
#include<assert.h>
using namespace std;

class Date
{
    //友元函数声明（能让外部函数访问私有成员）
    friend ostream& operator<<(ostream& _cout , const Date& d);
    friend istream& operator>>(istream& _cin ,  Date& d);
public:
    Date(int year=2026 , int month=10 , int day=13);
    //类里面直接定义的函数 默认是inline 不能声明和定义分离
    void Print() const
    {
        cout << _year << "/" << _month << "/" << _day << endl;
    }
    //只要实现了一个大于 或者 小于 那大于等于和小于等于就可以直接复用
    bool operator>(const Date& d) const; // 都加上const 让const 和非const对象都可以调用
    bool operator>=(const Date& d) const;
    bool operator<(const Date& d) const;
    bool operator<=(const Date& d) const;
    bool operator!=(const Date& d) const;
    bool operator==(const Date& d) const;
    bool IsValid() const;

    Date operator+(int day) const;
    Date operator-(int day) const;
    int operator-(const Date& d) const;

    Date& operator+=(int day);
    Date& operator-=(int day);

    //流插入 只支持 d1 << cout
    //成员的方式重载<< 无法满足我们正常使用流习惯和可读性
    // void operator<<(ostream& _cout)
    // {
    //     _cout << _year << "/" << _month << "/" << _day << endl;
    // }
private:
// 成员都是内置类型不做处理
    int _year;
    int _month;
    int _day;

    int hour;
    int minute;
    int second;

};

