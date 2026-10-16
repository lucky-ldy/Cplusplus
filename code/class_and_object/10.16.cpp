//一、友元

//1.友元提供了⼀种突破类访问限定符封装的⽅式，友元分为：友元函数和友元类
//2.外部友元函数可访问类的私有和保护成员，友元函数仅仅是⼀种声明，他不是类的成员函数
//3.友元函数可以在类定义的任何地⽅声明，不受类访问限定符限制
//4.一个函数可以是多个类的友元函数
//5.友元类中的成员函数都可以是另⼀个类的友元函数，都可以访问另⼀个类中的私有和保护成员
//6.友元类关系不能传递，如果A是B的友元， B是C的友元，但是A不是C的友元
//7.友元增加了耦合度 破坏了封装 但是 提供了便利
#include<iostream>
using namespace std;
// 前置声明，都则A1的友元函数声明编译器不认识B1
class B1;


class A1
{
    //可以把B1定义为A1的友元 那B1就能访问A1的私有
    friend class B1;
    // 友元声明
    friend void func(const A1& aa, const B1& bb);
    private:
    int _a1 = 1;
    int _a2 = 2;
};

class B1
{
    // 友元声明
    friend void func(const A1& aa, const B1& bb);
    private:
    int _b1 = 3;
    int _b2 = 4;
};

void func(const A1& aa, const B1& bb)
{
    cout << aa._a1 << endl;
    cout << bb._b1 << endl;
}

// int main()
// {
//     A1 aa;
//     B1 bb;
//     func(aa , bb);

//     return 0;
// }


//二、内部类
//如果⼀个类定义在另⼀个类的内部，这个内部类就叫做内部类
//内部类是⼀个独⽴的类，跟定义在全局相⽐，他只是受外部类类域限制和访问限定符限制
//1.所以外部类定义的对象中不包含内部类
//2.内部类默认是外部类的友元类。
//3.内部类本质也是⼀种封装，当A类跟B类紧密关联，A类实现出来主要就是给B类使⽤
//特别的 如果把内部类放到private/protected位置，那么A类就是B类的专属内部类 只能在类的内部使用
#include<iostream>
using namespace std;

//外部类不能访问内部类的私有
class A2
{
private:
    static int _k;//静态变量不是对象成员 不算进类的大小
    int _h = 1;
public:

    class B2 // B默认就是A的友元
    {
    public:
        void foo(const A2& a)
        {
            //内部类可以访问外部类的私有成员
            cout << _k << endl; //OK
            cout << a._h << endl; //OK
        }

        int _b1;
    };

};
int A2::_k = 1;

//专属内部类
class B3
{
private:
    class A3  // A 是 B 的私有内部类
    {
    public:
        void func() 
        {}

    private:
        int x = 0;
    };

public:
    void test()
    {
        A3 a;        // 可以：B 内部能使用 A 这个类型
        a.func();   // 可以：func 是 A 的 public 成员
        // a.x = 1; // 不可以：x 是 A 的 private 成员
    }
};

// int main()
// {
//     cout << sizeof(A2) << endl;//所以这里的A2的大小不包括静态变量 也不包括内部类B2的大小
//     //输出为4个字节
//     A2::B2 b; //内部类受类域的限制
//     A2 aa;
//     b.foo(aa);

//     return 0;
// }


//二、匿名对象
//⽤ 类型(实参) 定义出来的对象叫做匿名对象 相⽐之前我们定义的 类型 对象名(实参) 定义出来的叫有名对象
//


class A4
{
public:
	A4(int a = 0)
		:_a(a)
	{
		cout << "A4(int a)" << endl;
	}

	~A4()
	{
		cout << "~A4()" << endl;
	}
private:
	int _a;
};

class Solution1 
{
public:
	int Sum_Solution1(int n) 
    {
		//...
		return n;
	}
};

void PushBack(A4 aa) 
{

}

// int main() 
// {
// 	A4 aa1;
// 	A4 aa2(2);

// 	// 匿名对象,生命周期只在当前这一行
// 	A4();
// 	A4(2);

//     //有名对象调用成员函数
// 	Solution1  so;
// 	so.Sum_Solution1(1);

//     //匿名对象调用成员函数 在这种只需要调用函数的场景下使用
// 	Solution1().Sum_Solution1(2);

//     //有名传参
// 	A4 aa3(3);
// 	PushBack(aa3);

//     //匿名对象传参
// 	PushBack(A4(3));

// 	return 0;
// }

//三、对象拷⻉时的编译器优化
//对于连续⼀个表达式步骤中的连续拷⻉会进⾏合并优化（我们前面的类型转换就是编译器将构造+拷贝构造 优化成直接构造）

#include<iostream>
using namespace std;
class A5
{
public:
	A5(int a = 0)
		:_a1(a)
	{
		cout << "A5(int a)" << endl;
	}

	A5(const A5& aa)
		:_a1(aa._a1)
	{
		cout << "A5(const A& aa)" << endl;
	}

	A5& operator=(const A5& aa)
	{
		cout << "A5& operator=(const A& aa)" << endl;
		if (this != &aa)
		{
			_a1 = aa._a1;
		}
		return *this;
	}

	~A5()
	{
		cout << "~A()" << endl;
	}
private:
	int _a1 = 1;
};

void f1(A5 aa)
{

}

A5 f2()
{
	A5 aa;
	return aa;//这里返回的是aa的拷贝构造 因为aa除了作用域直接就销毁了
}

int main() {

	//A aa1(1);

	//// 构造临时对象，临时对象拷贝构造aa2 -> 优化直接构造
	//A aa2 = 1; // 优化
	//const A& aa3 = 1;

	// 传值传参
	A5 aa1;
	f1(aa1);
	cout << endl;

	// 1构造临时对象，再拷贝构造 -> 优化直接构造
	f1(1);   // 1先构造临时对象再拷贝构造 优化成: 直接构造
	f1(A5(1));//直接优化
	f1(A5()); //用默认构造 优化
	cout << "****************" << endl;

	// 传值返回
	// 返回时一个表达式中，连续拷贝构造+拷贝构造->优化一个拷贝构造
	// 一些编译器会优化得更厉害，进行跨行合并优化，直接变为构造
	f2(); // 没有接收返回值 所有没有进行拷贝构造
	cout << endl;

    // 返回时一个表达式中，连续拷贝构造+拷贝构造->优化一个拷贝构造
	// 一些编译器会优化得更厉害，进行跨行合并优化，直接变为构造
	A5 aa2 = f2();//这里创建一个对象并且初始化 是拷贝构造
	cout << endl; 

	// 一个表达式中，连续拷贝构造+赋值重载->无法优化
	aa1 = f2(); //给一个已经初始化的对象调用函数 是赋值
	cout << endl;
	cout << endl;

	return 0;
}

//总结 尽量用拷贝构造接收返回值 编译器可以更大空间去优化




