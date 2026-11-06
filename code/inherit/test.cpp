//继承
#include <iostream>
using namespace std;
#include <string>
#include <vector>
// class Student
// {

// public:
//     // 进⼊校园/图书馆/实验室刷⼆维码等⾝份认证
//     void identity()
//     {
//     // ...
//     }
//     // 学习
//     void study()
//     {
//     // ...
//     }

// protected:

//     string _name = "peter"; // 姓名
//     string _address; // 地址
//     string _tel; // 电话
//     int _age = 18; // 年龄
//     int _stuid; // 学号
// };

// class Teacher
// {

// public:
//  // 进⼊校园/图书馆/实验室刷⼆维码等⾝份认证
//     void identity()
//     {
//     // ...
//     }
//     // 授课
//     void teaching()
//     {
//     //...
//     }

// protected:
//     string _name = "张三"; // 姓名
//     int _age = 18; // 年龄
//     string _address; // 地址
//     string _tel; // 电话
//     string _title; // 职称
// };

//一、继承方式有三种 public private protected
//public 继承方式
//private 继承方式
//protected 继承方式
//1.基类private成员在派⽣类中⽆论以什么⽅式继承都是不可⻅的。
//2.基类的其他成员在派⽣类的访问⽅式 == Min(成员在基类的访问限定符，继承⽅式)，public > protected > private。
//3.使⽤关键字class时默认的继承⽅式是private，使⽤struct时默认的继承⽅式是public
class Person
{
public:
    // 进⼊校园/图书馆/实验室刷⼆维码等⾝份认证
    void identity()
    {
        cout << "void identity()" <<_name<< endl;
    }

protected:// 保护成员可以在类的内部访问，也可以被派生类访问
    string _name = "张三"; // 姓名
    string _address; // 地址
    string _tel; // 电话

private: // 私有成员只能在类的内部访问，不能被派生类访问
    int _age = 18; // 年龄
};

// 学生类
//Student 是派生类 public是继承方式 Person是基类
class Student : public Person // 继承Person类
{
public:
    // 学习
    void study()
    {
    // ...
    }

protected:
    int _stuid; // 学号
};

// 教师类
class Teacher : public Person // 继承Person类
{
public:
    // 授课
    void teaching()
    {
    //...
    }
protected:
    string _title; // 职称
};



// int main()
// {
//     Student s;
//     Teacher t;
//     s.identity();
//     t.identity();
//     return 0;
// }

//二、继承类模板

namespace ldy
{
 //template<class T>
 //class vector
 //{};
 // stack和vector的关系，既符合is-a，也符合has-a
 template<class T>
 //要继承类模板，指定类域std::vector<T>，
 class stack : public std::vector<T>
 {
 public:
    void push(const T& x)
    {
    // 基类是类模板时，需要指定⼀下类域，
    // 否则编译报错:error C3861: “push_back”: 找不到标识符
    // 因为stack<int>实例化时，也实例化vector<int>了
    // 但是模版是按需实例化，push_back等成员函数未实例化，所以找不到
    vector<T>::push_back(x);
    //push_back(x);
    }

    void pop()
    {
    vector<T>::pop_back();
    }

    const T& top()
    {
    return vector<T>::back();
    }

    bool empty()
    {
    return vector<T>::empty();
    }
 };
}

// int main()
// {
//     ldy::stack<int> st;
//     st.push(1);
//     st.push(2);
//     st.push(3);
//     while (!st.empty())
//     {
//         cout << st.top() << " ";
//         st.pop();
//     }

//  return 0;
// }

//三、派生类和基类之间的转换

class Person2
{
protected :
    string _name; // 姓名
    string _sex; // 性别
    int _age; // 年龄
};

class Student2 : public Person2
{
public :
     int _No ; // 学号
};


// int main()
// {
//     Student2 sobj ;
//     // 1.派生类对象可以赋值给基类的指针/引⽤
//     Person2* pp = &sobj;
//     Person2& rp = sobj;

//     // 派生类对象可以赋值给基类的对象是通过调用后面会讲解的基类的拷贝构造完成的
//     Person2 pobj = sobj;

//     //2.基类对象不能赋值给派生类对象，这里会编译报错
//     //sobj = pobj;

//  return 0;
// }

 //四、继承中的作用域
//隐藏规则
//1.在继承体系中基类和派⽣类都有独⽴的作⽤域。
//2. 派⽣类和基类中有同名成员，派⽣类成员将屏蔽基类对同名成员的直接访问，这种情况叫隐藏


// Student的_num和Person的_num构成隐藏关系，可以看出这样代码虽然能跑，但是⾮常容易混淆
// class Person
// {
// protected :
//     string _name = "⼩李⼦"; // 姓名
//     int _num = 111; // ⾝份证号
// };

// class Student : public Person
// {
// public:
//     void Print()
//     {
//         cout<<" 姓名:"<< _name << endl;
//         cout<<" ⾝份证号:"<< Person::_num << endl;
//         cout<<" 学号:"<< _num <<endl;
//     }

// protected:
//     int _num = 999; // 学号
// };

// int main()
// {
//     Student s1;
//     s1.Print();

//     return 0;
// };

//五、派⽣类的默认成员函数
//4个常⻅默认成员函数
//1.派⽣类的构造函数必须调⽤基类的构造函数初始化基类的那⼀部分成员
//2.派⽣类的拷⻉构造函数必须调⽤基类的拷⻉构造完成基类的拷⻉初始化
//3.派⽣类的operator=必须要调⽤基类的operator=完成基类的复制
//4.派⽣类的析构函数必须调⽤基类的析构函数，否则会内存泄漏

class Person1
{
public :

    Person1(const char* name = "peter")
    : _name(name )
    {
        cout<<"Person1()" <<endl;
    }

    Person1(const Person1& p)
    : _name(p._name)
    {
        cout<<"Person1(const Person1& p)" <<endl;
    }

    Person1& operator=(const Person1& p )
    {
        cout<<"Person1 operator=(const Person1& p)"<< endl;
        if (this != &p)
        _name = p ._name;

        return *this ;
    }

    ~Person1()
    {
        cout<<"~Person1()" <<endl;
    }

protected :
 string _name ; // 姓名
};

class Student1 : public Person1
{

public :
    //构造函数先构造基类，再构造派生类
    Student1(const char* name, int num)
    : Person1(name)
    , _num(num)
    {
        cout<<"Student1()" <<endl;
    }
    //拷贝构造函数先拷贝基类，再拷贝派生类
    Student1(const Student1& s)
    : Person1(s)
    , _num(s ._num)
    {
        cout<<"Student1(const Student1& s)" <<endl ;
    }
    //赋值运算符重载函数先赋值基类，再赋值派生类
    Student1& operator = (const Student1& s )
    {
        cout<<"Student1& operator= (const Student1& s)"<< endl;
        if (this != &s)
        {
            // 构成隐藏，所以需要显示调用
            Person1::operator =(s);
            _num = s ._num;
        }
        return *this ;
    }
    //析构函数先析构派生类，再析构基类
    ~Student1()
    {
        cout<<"~Student1()" <<endl;
    }
protected :
    int _num ; //学号
};

int main()
{
    Student1 s1 ("jack", 18);
    Student1 s2 (s1);
    Student1 s3 ("rose", 17);
    s1 = s3 ;

    return 0;
}


//实现⼀个不能被继承的类: 传统做法就是将构造函数私有化

//继承与友元
//友元关系不能继承，也就是说基类友元不能访问派⽣类私有和保护成员 。

//继承与静态成员
//基类定义了static静态成员，则整个继承体系⾥⾯只有⼀个这样的成员
