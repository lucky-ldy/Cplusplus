//一、内存管理
//1.1 C/C++内存分布

#include<iostream>
#include<stdlib.h>

using namespace std;


int globalVar = 1;
static int staticGlobalVar = 1;

// int main()
// {
// 	static int staticVar = 1;
// 	int localVar = 1;
// 	int num1[10] = { 1, 2, 3, 4 };
// 	char char2[] = "abcd";
// 	const char* pChar3 = "abcd";
// 	int* ptr1 = (int*)malloc(sizeof(int) * 4);
// 	int* ptr2 = (int*)calloc(4, sizeof(int));
// 	int* ptr3 = (int*)realloc(ptr2, sizeof(int) * 4);
// 	free(ptr1);
// 	free(ptr3);
//     return 0 ;
// }

//   选项: A.栈  B.堆  C.数据段(静态区)  D.代码段(常量区)
//    globalVar在哪里？__C__   
//    staticGlobalVar在哪里？__C__
//    staticVar在哪里？__C__   
//    localVar在哪里？__A__
//    num1 在哪里？__A__

//栈：
// char2  → 数组本体 ['a']['b']['c']['d']['\0']

// pChar3 → 指针变量，保存一个地址
//              │
//              ▼
// 常量区：    "abcd"
//    
//    char2在哪里？__A__        
//    *char2在哪里？__A__     char2是数组首元素地址 *char2 = a  a在栈上
//    pChar3在哪里？__A__     局部的指针变量在栈上
//    *pChar3在哪里？__D__    *pChar3 = abcd\0 常量区
//    ptr1在哪里？__A__         
//    *ptr1在哪里？__B__



//1.2 C语言中动态内存管理方式：malloc/calloc/realloc/free

void Test ()
{
    // 1.malloc/calloc/realloc的区别是什么？
    // malloc 直接申请空间 calloc 申请空间并且初始化为0  realloc 是扩容
    int* p2 = (int*)calloc(4, sizeof (int));
    int* p3 = (int*)realloc(p2, sizeof(int)*10);
    // 这里需要free(p2)吗？
    //要看realloc 是否成功 成功后原空间可能原地扩大  也可能搬到新地址 之后只能用p3
    //扩容失败 p3 ==nullptr 原来的p2也有效 需要free(p2) 此时free(p3)什么也不做

    free(p3);
}


//1.3 C++内存管理方式(new和delete)
// C语言内存管理方式在C++中可以继续使用，但有些地方就无能为力，而且使用起来比较麻烦，因
// 此C++又提出了自己的内存管理方式：通过new和delete操作符进行动态内存管理

//内置类型 malloc和new没什么区别
// int main()
// {
// 	// 动态申请一个int类型的空间
// 	int* ptr4 = new int;
// 	// 动态申请一个int类型的空间并初始化为10
// 	int* ptr5 = new int(10);
// 	// 动态申请10个int类型的空间
// 	int* ptr6 = new int[10];

// 	// 动态申请10个int类型的空间,并初始化，后面给位置初始化成0
// 	int* ptr7 = new int[10] {1,2,3};

//     //释放
// 	delete ptr4;
// 	delete ptr5;  
// 	delete[] ptr6;
// 	delete[] ptr7;

//     return 0;
// }


//自定义类型 malloc和new很大区别
// C++里面尽量用new/delete,不要用malloc/free
class A
{
public:
	A(int a = 0)
		: _a(a)
	{
		cout << "A():" << this << endl;
	}

	~A()
	{
		cout << "~A():" << this << endl;
	}
private:
	int _a;
};

struct Node 
{
	Node* _next;
	int _val;

	Node(int val = 0)
		:_val(val)
		,_next(nullptr) 
        {

	    }
};

// int main()
// {
// 	// new/delete 和 malloc/free最大区别是 
//     //new/delete对于【自定义类型】除了开空间还会调用构造函数和析构函数
// 	// 动态开空间
// 	A* p1 = (A*)malloc(sizeof(A));
// 	// p1->_a = 1; 不能直接访问_a成员 是私有的

// 	// 动态开空间 + 1次构造
// 	A* p2 = new A(1);
// 	free(p1);
// 	// 1次析构+释放动态空间
// 	delete p2;

//     //只动态开空间
// 	A* p5 = (A*)malloc(sizeof(A) * 10);

// 	// 动态开空间+10次构造
// 	A* p6 = new A[10]; 
// 	free(p5);

// 	// 10次析构+释放动态空间
// 	delete[] p6;

// 	// 语法逻辑要自洽
//     //默认构造很重要
// 	//A* p7 = new A[10]{A(1), A(2), A(3)}; //匿名对象
// 	A* p7 = new A[10]{ 1,2,3};//类型转换
// 	// 10次析构+释放动态空间
// 	delete[] p7;

//     Node* n1 = new Node(1);
// 	Node* n2 = new Node(2);
// 	Node* n3 = new Node(3);
// 	Node* n4 = new Node(4);
// 	n1->_next = n2;
// 	n2->_next = n3;
// 	n3->_next = n4;

// //	return 0;
// }


//1.4 operator new与operator delete函数
//new和delete是用户进行动态内存申请和释放的操作符，operator new 和operator delete是系统提供的全局函数，
//new在底层调用operator new全局函数来申请空间，
//delete在底层通过operator delete全局函数来释放空间。
//因为malloc失败是返回空 不符合C++处理的机制 C++失败是要抛异常 所以就调用operator new 和 operator delete

void func()
{
	for (int i = 0; i < 10000; i++) 
    {
        //空语句不能断住 调试的时候可以在里面初始化一个变量就能在想要的位置断住
		if (i == 5119) {
			int x = 0;
		}

		int* p1 = new int[1024 * 100]; // 400KB
		cout << i << ":" << p1 << endl;
	}
}

// int main()
// {
//     //捕获异常
// 	try 
//     {
// 		func();
// 	}

// 	catch (const exception& e) {
// 		cout << e.what() << endl;
// 	}

// 	return 0;
// }


class A1
{
public:
	A1(int a = 0)
		: _a(a)
	{
		cout << "A1():" << this << endl;
	}
	~A1()
	{
		cout << "~A1():" << this << endl;
	}
private:
	int _a;
};


int main() 
{
	// 开空间(operator new -> malloc+失败抛异常) + 调构造函数
	A1* p2 = new A1(1);
	delete p2;

	return 0;
}