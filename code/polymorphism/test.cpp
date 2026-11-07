//多态
//多态(polymorphism)的概念：通俗来说，就是多种形态。
//多态分为编译时多态(静态多态)和运行时多态(动态多态)

#include <iostream>
using namespace std;
#include <string>

//多态的构成条件！
//1.必须是基类的指针或者引用调用虚函数
//2.被调用的函数必须是虚函数，并且完成了虚函数重写/覆盖.

//虚函数的重写/覆盖
//三同：
//1.函数名相同
//2.参数列表相同
//3.返回值类型相同
//重写派生类的虚函数可以不加virtual关键字，但是建议加virtual关键字

class Person
{
public:
//虚函数 与 虚继承 没有关系
    virtual void BuyTicket()
    {
        cout << "买票-全价" << endl;
    }

};

class Student : public Person
{
public:
	// 重写基类的虚函数 - 重写虚函数的实现
	//virtual void BuyTicket() { cout << "买票-打折" << endl; }
	void BuyTicket() //virtual 可写 可不写
    {
        cout << "买票-打折" << endl;
    }
};

class Soldier : public Person
{
public:
	// 重写基类的虚函数
	virtual void BuyTicket() { cout << "买票-优先" << endl; }
};

void Func(Person* ptr)
{
	// 这里可以看到虽然都是Person指针Ptr在调用BuyTicket
	// 但是跟ptr没关系，而是由ptr指向的对象决定的。
	ptr->BuyTicket();
}

// int main()
// {
// 	Person ps;
// 	Student st;
// 	Soldier soldier;

// 	Func(&ps);// 调用的是基类的BuyTicket()价
// 	Func(&st);// 调用的是子类的BuyTicket()打折
// 	Func(&soldier);// 调用的是子类的BuyTicket()优先


// 	return 0;
// }


//协变
//协变返回值类型：子类指针可以指向父类对象
//协变即基类虚函数返回基类对象的指针或者引用，派生类虚函数返回派生类对象的指针或者引用
class A {};
class B : public A {};
//B是A的子类， B可以作为A的指针或者引用，作为返回类型

class Person1
{
public:
	virtual A* BuyTicket()
	{
		cout << "买票-全价" << endl;
		return nullptr;
	}
};

class Student1 : public Person1
{
public:
	virtual B* BuyTicket()
	{
		cout << "买票-打折" << endl;
		return nullptr;
	}
};

void Func(Person1* ptr)
{
	ptr->BuyTicket();
}

// int main()
// {
// 	Person1 ps;
// 	Student1 st;
// 	Func(&ps);
// 	Func(&st);

// 	return 0;
// }


class A1
{
public:
	virtual ~A1()
	{
		cout << "~A1()" << endl;
	}
};

class B1 : public A1
{
public:
    //加了override关键字后，会检查是否重写了基类的虚函数
	virtual ~B1() override//名字被特殊处理 会调用子类的析构函数
	{
		cout << "~B1()->delete:" << _p << endl;
		delete _p;
	}

protected:
	int* _p = new int[10];
};

// 只有派生类Student的析构函数重写了Person的析构函数，
//  下面的delete对象调用析构函数，才能构成多态，才能保证p1和p2指向的对象正确的调用析构函数。
// int main()
// {
//     //这个场景下无影响
// 	// A1 a;
// 	// B1 b;

//     //期望构成多态析构函数
// 	A1* p1 = new A1;
// 	A1* p2 = new B1;
// 	delete p1;
// 	delete p2;

// 	return 0;
// }


//重载 重写 隐藏的对比
//1.重载：函数名相同，参数列表不同
//2.重写：函数名相同，参数列表相同，返回值类型相同 必须是虚函数
//3.隐藏：函数名相同，参数列表相同，返回值类型不同
//4.虚函数：函数名相同，参数列表相同，返回值类型相同，但是建议加virtual关键字


//纯虚函数 和 抽象类
//纯虚函数不需要定义实现(实现没啥意义因为要被派生类重写，但是语法上可以实现)
//在虚函数的后面写上 =0 ，则这个函数为纯虚函数
//包含纯虚函数的类，称为抽象类
//抽象类不能实例化，只能作为基类被继承
//抽象类的指针可以指向派生类的对象

// 抽象类
//某种程度上说 纯虚函数 强制了 派生类必须重写该函数 不然就实例化不了对象
class Car
{
public:
	virtual void Drive() const = 0;
};

class Benz :public Car
{
public:
	virtual void Drive() const
	{
		cout << "Benz-舒适" << endl;
	}
};

class BMW :public Car
{
public:
	virtual void Drive() const
	{
		cout << "BMW-操控" << endl;
	}
};

class WENJIE :public Car
{
public:
	virtual void Drive() const
	{
		cout << "WENJIE-智能化" << endl;
	}
};

void Func(const Car& p)
{
	p.Drive();
}

int main()
{
	// 编译报错：error C2259: “Car”: 无法实例化抽象类
	// Car car;
	Func(Benz());//创建临时对象Benz 传给Func函数
	Func(BMW());
	Func(WENJIE());

	return 0;
}
