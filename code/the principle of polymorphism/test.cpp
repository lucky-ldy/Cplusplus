#include<iostream>
using namespace std;

//多态的原理
//通过基类指针或引用调用虚函数时，
//程序会根据对象的实际类型，在运行时决定调用哪个版本。
class Base
{
public:
	virtual void Func1()
	{
		cout << "Func1()" << endl;
	}

	virtual void Func2()
	{
		cout << "Func2()" << endl;
	}

	void Func3()
	{
		cout << "Func3()" << endl;
	}

protected:
	int _b = 1;
	char _ch = 'x';
};

class Person 
{
public:
	virtual void BuyTicket() 
    { 
        cout << "买票-全价" << endl; 
    }

	virtual void Func1()
	{
		cout << "Func1()" << endl;
	}

	virtual void Func2()
	{
		cout << "Func2()" << endl;
	}

private:
	string _name;
};

class Student : public Person 
{
public:
//某种程度上来说 派生类是先拷贝 基类的虚函数 再重写虚函数 改变地址
	virtual void BuyTicket() //派生类重写虚函数 虚函数的地址会改变
    {
        cout << "买票-打折" << endl; 
    }

	virtual void Func1()
	{
		cout << "Func1()" << endl;
	}

	virtual void Func3()
	{
		cout << "Func3()" << endl;
	}

private:
	string _id;
};

void Func(Person& ptr)
{
	// 这里可以看到虽然都是Person指针Ptr在调用BuyTicket
	// 但是跟ptr没关系，而是由ptr指向的对象决定的。
	ptr.BuyTicket();
}
// Person 声明了虚函数，编译器为它建立虚函数表；Student 也有自己的虚函数表。
// 对象里会有一个隐藏指针 _vfptr，指向对应的虚函数表。
// 执行 ptr->BuyTicket() 时，程序沿着对象的 _vfptr 找到 BuyTicket 对应的函数地址，再调用它。
// 所以 Fun(&s) 传进去的虽然是 Person*，它指向的仍是 Student 对象，最终会通过 Student 的虚表找到 Student::BuyTicket()
// int main()
// {
//     Base b;
//     Person p;
//     Student s;

//     // 动态绑定 
//     // 
//     Person p1;
//     Person p2;
//     Fun(&s);
//     Fun(&p);

// }


//动态绑定与静态绑定
//动态绑定：在运行时根据对象的实际类型调用虚函数
//静态绑定：在编译时根据对象的类型调用虚函数
// 当执行 Fun(&s) 时：
// 1. ptr 是 Person*，但它指向 Student 对象 s。
// 2. BuyTicket() 是虚函数。
// 3. 所以运行时看见实际对象是 Student，调用 Student::BuyTicket()，输出“买票-打折”。
// 这就是动态绑定：实际对象是 Student → 调 Student 的函数。

// 你的 Base::Func3() 不是虚函数。调用 b.Func3() 时，编译器就确定调用 Base::Func3()，不需要运行时再看对象类型。这就是静态绑定。

// 记住这一句就行：虚函数会根据实际对象选择，非虚函数在编译时就选定。



int main() 
{
	Base b;
	Person p;
	//Person p2;

	Student s;

	Func(p);
	Func(s);

	int i = 0;
	static int j = 1;
	int* p1 = new int;
	const char* p2 = "xxxxxxxx";
	printf("栈:%p\n", &i);
	printf("静态区:%p\n", &j);
	printf("堆:%p\n", p1);
	printf("常量区:%p\n", p2);

	Person* ptr1 = &p;
	printf("虚表地址:%p\n", *((long long*)ptr1));
	return 0;
}

// 虚函数表（vtable）里通常保存多个虚函数入口，不是每个虚函数各有一张虚表。
// 含虚函数的对象通常保存虚表指针（vptr）；这是常见实现方式，C++标准不规定具体布局。
class Base1 
{
public:
	virtual void func1() 
    { 
        cout << "Base::func1" << endl; 
    }
    
	virtual void func2() 
    { 
        cout << "Base::func2" << endl; 
    }
	void func5() 
    { 
        cout << "Base::func5" << endl; 
    }

protected:
	int a = 1;
};

// Base1 和 Base2 是两个独立基类；它们声明了同名、同参数的虚函数。
class Base2 
{
public:
	virtual void func1() 
    { 
        cout << "Base::func1" << endl; 
    }

	virtual void func2() 
    {
        cout << "Base::func2" << endl; 
    }

	void func5() 
    { 
        cout << "Base::func5" << endl; 
    }

protected:
	int a = 1;
};

// Derive 对象包含 Base1 和 Base2 两个基类子对象。
// 常见实现会让这两个多态基类子对象各有虚表指针；调试器中可能看到两个 vptr。
// 虚表指针的数量和布局属于编译器实现细节，不能当作 C++ 语言标准保证。
// 两个基类都声明了成员 a，因此 Derive 中若要访问它们，需写 Base1::a 或 Base2::a。
class Derive : public Base1, public Base2
{
public:
	// 两个基类都有同签名的虚函数 func1；这一个函数同时重写两边的虚函数。
	virtual void func1() 
    {
        cout << "Derive::func1" << endl; 
    }

	// 同理，这一个函数同时重写 Base1::func2 和 Base2::func2。
	virtual void func2() 
    {
        cout << "Derive::func2" << endl; 
    }

	// 新增的普通成员函数，不是对基类虚函数的重写。
	void func4() 
    {
        cout << "Derive::func4" << endl; 
    }
protected:
	int b = 2;
};

int main() 
{
	// 这里只构造对象，没有调用函数，因此不会看到多态调用结果。
	// 可分别用 Base1* 和 Base2* 指向 d，再调用 func1/func2，观察到的都是 Derive 的实现。
	// func5 是非虚函数；两个基类都定义了它，直接写 d.func5() 会有歧义。
	Derive d;

	return 0;
}