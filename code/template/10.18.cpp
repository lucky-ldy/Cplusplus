//一、模板初阶


#include<iostream>
using namespace std;

//1.1  泛型编程

// 使用函数重载虽然可以实现，但是有一下几个不好的地方：
// 1. 重载的函数仅仅是类型不同，代码复用率比较低，只要有新类型出现时，就需要用户自己增
// 加对应的函数
// 2. 代码的可维护性比较低，一个出错可能所有的重载均出错
// void Swap(int& left, int& right)
// {
// 	int temp = left;
// 	left = right;
// 	right = temp;
// }

// void Swap(double& left, double& right)
// {
// 	double temp = left;
// 	left = right;
// 	right = temp;
// }

// void Swap(char& left, char& right)
// {
// 	char temp = left;
// 	left = right;
// 	right = temp;
// }


//二、函数模板
//函数模板代表了一个函数家族，
//该函数模板与类型无关，在使用时被参数化，根据实参类型产生函数的特定类型版本

//2.1 函数模板格式 template<typename T1, typename T2,......,typename Tn>
//T可以是任意类型
class A
{
public:
	A(int a = 0)
		: _a(a)
	{
		cout << "A():" << this << endl;
	}

	// A(const A& a);

	~A()
	{
		cout << "~A():" << this << endl;
	}
private:
	int _a;
};

//早期 template<class T>
template<typename T>

void Swap(T& left , T& right)
{
    T temp = left;
    left = right; 
    right = temp;
}

//这里面调用的不是同一个函数 他们是模板生成的不同的函数
// int main()
// {
//     int i = 1 , j = 2;
//     Swap(i , j);

//     double  x = 1.1 , y = 2.2 ;
//     Swap(x , y);

//     //要支持拷贝构造才可以实现(因为模板函数中有拷贝构造) 只声明不定义拷贝构造会报错
//     A a1(1) , a2(2);
//     Swap(a1 , a2);
// }


//2.2 函数模板的原理
//函数模板是一个蓝图，它本身并不是函数，是编译器用使用方式产生特定具体类型函数的模具。
//所以其实模板就是将本来应该我们做的重复的事情交给了编译器

//2.3 函数模板的实例化
//用不同类型的参数使用函数模板时，称为函数模板的实例化。
//模板参数实例化分为：隐式实例化和显式实例化。

//1.隐式实例化 让编译器根据实参推演模板参数的实际类型
template<class T>
T Add(const T& left, const T& right)
{
	return left + right;
}

//2.显式实例化：在函数名后的<>中指定模板参数的实际类型
template<class T>
T* PoolNew(int n) 
{
	return new T[n];
}

// int main()
// {
// 	int a1 = 10, a2 = 20;
// 	double d1 = 10.1, d2 = 20.2;
//     //隐式实例化
// 	Add(a1, a2);
// 	Add(d1, d2);

//     //推导参数类型不能有歧义
// 	cout << Add(a1, (int)d2) << endl;
// 	cout << Add((double)a1, d2) << endl;

// 	// 显式实例化 指定T的类型
// 	cout << Add<int>(a1,d2) << endl;
// 	cout << Add<double>(a1, d2) << endl;

//     //这里必须调用显式实例化 因为函数的参数中没有T 就不能从传入的实参推导出T是什么类型
// 	A* p1 = PoolNew<A>(10);

// 	return 0;
// }


//2.4 模板参数的匹配原则
//一个非模板函数可以和一个同名的函数模板同时存在，而且该函数模板还可以被实例化为这个非模板函数
// 专门处理int的加法函数 - 成品
int Add1(int left, int right)
{
	return left + right+10;
}

// 通用加法函数 - 半成品 要调用的时候还需要实例化
template<class T>
T Add1(T left, T right)
{
	return left + right;
}

// int main() {
// 	int a1 = 10, a2 = 20;
// 	double d1 = 10.1, d2 = 20.2;
// 	Add1(a1, a2);//直接调用会调用普通函数 不会调用模板函数
// 	Add1<int>(a1, a2);//显式实例化指定了T的类型 就会调用模板函数
// 	Add1(d1, d2);//普通的只处理int类型 所以调用模板函数

// 	return 0;
// }



//三、类模板


#define N 10
// typedef int STDataType;

template<typename T>
class Stack 
{
public:
	Stack()
	:_top(0)
    {

	}
	
//如果模板要做声明和定义分离那要写两次模板
	void Push(const T& x);

private:
	T _a[N];
	int _top;
};

//要再补充一次模板 因为类前面的模板参数声明不能直接管到后面独立的定义
template<typename T>
void Stack<T>::Push(const T& x)
{

}


template<typename T>
void Stack<T>::Push(const T& x) 
{

} 

#include <list>
// 模板是语法的进步，一些本来应该程序员做的重复工作，交给了编译器去完成
int main() 
{
    //typedef 要实现多个不同类型 做不到
	//Stack st1;  // 这个存int
	//Stack st2;  // 这个存double

	// 一个类模板实例化的不同类型
    //类模板必须显式实例化
    //一个类模板实例化的不同类型
	Stack<int> st1;  // 要int的栈
	Stack<double> st2;  // 要double的栈
	Stack<A> st3;

	A aa1(1);
	st3.Push(aa1);
	st3.Push(2);
	st3.Push(A(3));

	//一个类模板实例化的不同类型
	list<int> lt1;
	list<A> lt2;

	return 0;
}


//三、STL简介
//1.STL(standard template libaray-标准模板库)：是C++标准库的重要组成部分
//是一个包罗数据结构与算法的软件框架
//2.STL的六大组件 ： 仿函数 算法 迭代器 空间配置器(专用内存池) 容器 配接器
//3.STL的重要性：在笔试和面试中都占很大的比重 掌握STL是C++程序员的必备技能
//4.学习STL的三个境界:能用,明理,能拓展