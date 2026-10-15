//一、再探构造函数

//1.初始化列表的使⽤⽅式是以⼀个冒号开始，
//接着是⼀个以逗号分隔的数据成员列表，每个"成员变量"后⾯跟⼀个放在括号中的初始值或表达式
//2.每个成员变量在初始化列表中只能出现⼀次，
//语法理解上初始化列表可以认为是每个成员变量定义初始化的地⽅！
//3. 引⽤成员变量，const成员变量，没有默认构造的类类型变量，必须放在初始化列表位置进⾏初始化，否则会编译报错。
//4.尽量使⽤初始化列表初始化，因为那些你不在初始化列表初始化的成员也会⾛初始化列表，
//如果这个成员在声明位置给了缺省值，初始化列表会⽤这个缺省值初始化
//5.初始化列表中按照成员变量在类中声明顺序进⾏初始化，跟成员在初始化列表出现的的先后顺序⽆
//关。建议声明顺序和初始化列表顺序保持⼀致
#include<iostream>
using std::cout;
using std::endl;

class Time
{
public:
	Time(int hour)
		:_hour(hour)
	{
		cout << "Time()" << endl;
	}
private:
	int _hour;
};


class Date3
{
public:
    Date3(int& rx , int year = 2026 , int month = 10, int day = 15)
        //冒号开始 都好分隔成员变量 就是初始化列表
        //对每个成员变量初始化
        : _month(month)
        , _year(year)
        , _day(day) 
        , _n(1) //const类型成员变量只能放在列表中初始化
        , _ref(rx)//引用类型成员也必须在列表中初始化
        , _t(10)//类类型成员也必须在列表中初始化
        {
            //_yaer = year;
           // _n = 1; //这里会报错 因为const类型不能修改
        }


private:
    //声明
    int _year;
    int _month;
    int _day;
    const int _n;
    int& _ref;
    Time _t;
};

class Stack1
{
public:
	Stack1(int n) 
    {
        cout << "Stack()" << n << endl;
	}
};

class MyQueue1
{
public:
	MyQueue1(int n = 4)
		// :_st1(n)
		// ,_st2(n)
        : _size(10)//如果没写这个 初始化列表就会用缺省值给_size初始化
	{

    }

private:
	Stack1 _st1 = 10;
	Stack1 _st2 = 12;
    int _size ;//如果size没有显式写在初始化列表 就给个缺省值 初始化列表胡勇这个缺省值初始化
};

// int main() 
// {
//     int x = 0;
//     //整个类初始化
//     Date3 d1(x,2026,10,15);

//     MyQueue1 q;
// }

//总结：建议用初始化列表初始化成员变量
//1.要么显示在初始化列表初始化
//2.建议声明时给缺省值 初始化列表也会用那个值初始化这个成员


//二、类型转换
//1.C++⽀持内置类型隐式(接近int/char/unsigned int/double)类型转换为类类型对象，需要有相关内置类型为参数的构造函数
//int i = 1; char ch = i ; double d = i; 类型意义表示数据大小
//int* p = (int*) i  指针和整形为什么可以相互转换 指针是地址 在内存中相当于按字节的编号 编号就是整形
//2.构造函数前⾯加explicit就不再⽀持隐式类型转换。
//3.类类型的对象之间也可以隐式转换，需要相应的构造函数⽀持。
class A
{
public:
	// 构造函数explicit就不再支持隐式类型转换
	//explicit A(int a1)
	A(int a1)
		:_a1(a1)
	{
		cout << "A(int a1)" << endl;
	}

    A(int a1,int a2)
		:_a1(a1)
        ,_a2(a2)
	{
		cout << "A(int a1,int a2)" << endl;
	}

    //不会进入拷贝构造 被优化了 
    A(const A& aa0)
    {
        cout << "A(const A& aa)" << endl;
    }


	void Print()
	{
		cout << _a1 << " " << _a2 << endl;
	}

    int Get() const
	{
		return _a1 + _a2;
	}


private:
	int _a1 = 1;
	int _a2 = 2;
};

class Array {
public:
	void PushBack(const A& a) 
    {	

	}
};

class B 
{
public:
    //加了A类类型参数的构造就可以实现 A类 转换成 B类
	B(const A& aa)
		:_b(aa.Get())
	{

    }

private:
	int _b = 1;
};


// int main()
// {
//     //构造
//     A aa1(1);
//     //类型转换 整形转换成类A
//     //过程是 用1构造了一个A类型的临时变量 然后把临时变量拷贝给aa2
//     //语法逻辑是构造+拷贝构造 编译器直接优化成构造减少拷贝了
//     A aa2 = 1;

//     //A& aa3 = 1; 与之前double = int 一样 由于中间临时变量有常性 所以要加const
//     const A& aa3 = 1;

//     Array arr;
//     A aa4(4);
//     arr.PushBack(aa4);
//     //等价于 arr.PushBack(4);

//     //如果调用两个参数以上的构造函数 要加花括号
//     A aa5 = {5 , 5};
//     arr.PushBack(aa5);
//     arr.PushBack({5 , 5});

//     B bb1 = aa1;
//     const B& bb2 = aa1;

// }

//事实上 类型转换的本质：就是将不同类型的变量 转换成 对应对象的类型的临时变量 最后对应的对象拷贝这个临时变量 实现类型转换


//三、satic成员
//1.⽤static修饰的成员变量，称之为静态成员变量，静态成员变量⼀定要在类外进⾏初始化。
//2.静态成员变量为所有类对象所共享，不属于某个具体的对象，不存在对象中，存放在静态区
//3.⽤static修饰的成员函数，称之为静态成员函数，静态成员函数没有this指针
//4.静态成员函数可以访问其他的静态成员，但是不能访问⾮静态的，因为没有this指针
//5.⾮静态的成员函数，可以访问任意的静态成员变量和静态成员函数
//6.突破类域就可以访问静态成员
//全局的count 可以修改 不安全
//int count = 0;
class A1 
{
public:
    // static int _scount;

	A1(int a = 1)
		:_a(a)
	{
		++_scount;
	}

	A1(const A1& aa)
		:_a(aa._a)
	{
		++_scount;
	}

    int Get()
    {
        return _scount;
    }

    //static成员函数 没有this指针
    static int Get1()
    {
       // _a++;//就不能访问私有成员
        return _scount;
    }

private:
    int _a;
    //如果想让count放在类里 但生命周期是全局的的话就加上static
    
    //声明
    static int _scount;//不能用缺省值 缺省值是给对象成员用的 它是在静态区的不是类成员 
    
};

int A1::_scount = 0; //只能在类外初始化

// int main()
// {
//     A1 aa1(1);
//     A1 aa2 = 2;

//     //public
//     //公有就可以直接访问
//     // cout << A1::_scount << endl;
//     // cout << aa1._scount << endl;

//     //private
//     //私有要通过公有的成员函数来访问
//     cout << aa1.Get() << endl;
//     //静态成员函数调用 指定类域
//     cout << A1::Get1() << endl;

//     return 0 ;

// }

//四、求1+...+n 不能用乘除和公式运算
class Sum
{
public:
    Sum()
    {
        _ret += _i ;
        ++_i;
    }

    static int GetRet()
    {
        return _ret;
    }
private:
    static int _i;
    static int _ret;
};

int Sum::_i = 1;
int Sum::_ret = 0;


class Solution 
{
public:
    //构造一个对象构造一次构造函数 
   int Sum_Solution(int n) 
    {
        Sum arr[n];//构造n个对象 调用n次构造函数

        return Sum::GetRet();
    }

};

int main()
{
    int n = 5;
    Solution s1;
    cout << s1.Sum_Solution(n) << endl;
}

