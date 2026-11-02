#include <iostream>
using namespace std;
#include <vector>

class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{}

	bool operator<(const Date& d)const
	{
		return (_year < d._year) ||
			(_year == d._year && _month < d._month) ||
			(_year == d._year && _month == d._month && _day < d._day);
	}
	bool operator>(const Date& d)const
	{
		return (_year > d._year) ||
			(_year == d._year && _month > d._month) ||
			(_year == d._year && _month == d._month && _day > d._day);
	}

	// 友元声明
	friend ostream& operator<<(ostream& _cout, const Date& d);
private:
	int _year;
	int _month;
	int _day;
};

ostream& operator<<(ostream& _cout, const Date& d)
{
	_cout << d._year << "-" << d._month << "-" << d._day;
	return _cout;
}

//模板进阶
// template <class T> //T类型模板参数 固定了大小
// class Stack 
// {
// private:
// 	T _a[N];
// 	int _top;
// };
// N非类型模板参数
template <class T, size_t N = 5> //N非类型模板参数
class Stack 
{
private:
    T _a[N];
    int _top;
};

//函数模板 参数匹配
template <class T>
bool Less(T left , T right)
{
    return left < right;
}

//函数模板的特化 -- 针对某些特殊类型的处理
template<>
bool Less<Date*>(Date* left, Date* right)
{
    return *left < *right;
}


#include<array>

// int main()
// {
    // Stack<int, 10> st1;
    // Stack<int, 20> st2;
    // Stack<int> st3; // 使用默认值 5

    // int arr1[10];
    // array<int, 10> arr2;
    // // 初始化数组
    // arr2.fill(0);
    // arr1[1] = 100;
    // arr2[2] = 200;

    // //静态数组 越界检查不出来
    // cout << arr1[10] << endl;
    // cout << arr1[11] << endl;

    // //无论越界读写都可以很好的检查
    // cout << arr2.size() << endl;
    // cout << arr2[11] << endl;

    // for(auto e : arr1)
    // {
    //     cout << e << " ";   
    // }
    // cout << endl;

    // for(auto e : arr2)
    // {
    //     cout << e << " ";   
    // }
    // cout << endl;

//     cout << Less(10, 20) << endl;
//     Date d1(2026, 11, 2);
//     Date d2(2026, 11, 3);
//     cout << Less(d1, d2) << endl;

//     Date* p2 = new Date(2022, 7, 8); // 可以比较 结果正确
//     Date* p1 = new Date(2022, 7, 6); // 可以比较 结果正确
//     cout << Less(p1, p2) << endl; // 可以比较 指针的地址 结果错误
//     //对于这些特殊的指针 我们就用特化函数来比较

//     return 0;
// }

template<class T1 , class T2>
class Date1
{
public:
    Date1() 
    {
        cout << "Date1<T1,T2>" << endl;
    }

private:
    T1 _d1;
    T2 _d2;


};

//全特化 全部类型都指定
template<>
class Date1<int , char>
{
public:
    Date1()
    {
        cout << "Date1<int , char>" << endl;
    }   
    private:
        int _d1;
        char _d2;

};

//偏特化 只对部分类型进行指定
template<class T1>
class Date1<T1 , double>
{
public:
    Date1() 
    {
        cout << "Date1<T1 , double>" << endl;
    }       
    private:
        T1 _d1;
        double _d2;               
};


//两个参数偏特化为指针类型
template <typename T1, typename T2>
class Date1 <T1*, T2*>
{
public:
	Date1() { cout << "Date1<T1*, T2*>" << endl; }
private:
	T1 _d1;
	T2 _d2;
};
//两个参数偏特化为引用类型
template <typename T1, typename T2>
class Date1 <T1&, T2&>
{
public:
	Date1()
	{
		cout << "Date1<T1&, T2&>" << endl;
	}
private:
};
//一个参数偏特化为引用类型，一个参数偏特化为指针类型
template <typename T1, typename T2>
class Date1 <T1&, T2*>
{
public:
	Date1()
	{
		cout << "Date1<T1&, T2*>" << endl;   
	}
private:
};

int main()
{
    Date1<int , char> d1; //调用全特化
    Date1<int , double> d2; //调用偏特化
    Date1<char , double> d3; //调用偏特化
    Date1<char , char> d4; //调用通用模板
    Date1<int* , char*> d5; //调用偏特化
    Date1<int& , char&> d6; //调用偏特化    
    Date1<int& , char*> d7; //调用偏特化
    return 0;
}