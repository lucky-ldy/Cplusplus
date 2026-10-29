//  用栈实现队列
// void push(int x) 将元素 x 推到队列的末尾
// int pop() 从队列的开头移除并返回元素
// int peek() 返回队列开头的元素
// boolean empty() 如果队列为空，返回 true ；否则，返回 false

#include <stack>
#include <queue>
using namespace std;

class MyQueue 
{
public:
    MyQueue() 
    {

    }

    // 入队：新元素先放进 _pushst。
    void push(int x) 
    {
        _pushst.push(x);
    }

    // 出队：先取得队头，再从 _popst 中移除它。
    int pop() 
    {
        int front = peek();
        _popst.pop();
        return front;
    }

    // 查看队头；只有 _popst 为空时才把 _pushst 中的元素倒过来。
    int peek() 
    {
        if (_popst.empty()) 
        {
            // 倒入后，最早入队的元素会位于 _popst 栈顶。
            while (!_pushst.empty()) 
            {
                _popst.push(_pushst.top());
                _pushst.pop();
            }
        }

        return _popst.top();
    }

    // 两个栈都为空，整个队列才为空。
    bool empty() 
    {
        return _popst.empty() && _pushst.empty();
    }

private:
    // _pushst 接收新元素；_popst 提供队头元素。
    stack<int> _pushst;
    stack<int> _popst;
};


//用队列实现栈
// 实现 MyStack 类：

// void push(int x) 将元素 x 压入栈顶。
// int pop() 移除并返回栈顶元素。
// int top() 返回栈顶元素。
// boolean empty() 如果栈是空的，返回 true ；否则，返回 false 。
class MyStack 
{
public:
    MyStack() 
    {

    }
    // 入栈：把新元素放进当前非空队列；两个队列都空时放入 _q1。
    void push(int x) 
    {
        if (!_q1.empty())
        {
            _q1.push(x);
        }
        else
        {
            _q2.push(x);
        }
    }
    
    // 出栈：把队列前面的元素逐个转移，最后一个就是栈顶。
    int pop() 
    {
        // 统一让有元素的队列成为 _q1，_q2 作为接收队列。
        if (!_q2.empty())
        {
            _q1.swap(_q2);
        }

        // 留下最后一个元素，其余元素转移到 _q2。
        while (_q1.size() > 1)
        {
            _q2.push(_q1.front());
            _q1.pop();
        }

        int value = _q1.front();
        _q1.pop();
        return value;
    }
    
    // 查看栈顶：取出栈顶后马上放回，恢复原来的栈内容。
    int top() 
    {
        int value = pop();
        _q2.push(value);
        return value;
    }
    
    // 两个队列都为空时，栈为空。
    bool empty() 
    {
        return _q1.empty() && _q2.empty();
    }

private:
    queue<int> _q1;
    queue<int> _q2;
};

template<class T>
class Less
{
public:
    bool operator()(const T& x , const T& y)
    {
        return x < y;
    }

};

template<class T>
class Greater
{
public:
    bool operator()(const T& x , const T& y)
    {
        return x > y;
    }

};


#include "stack.h"
#include "queue.h"
#include "priority_queue.h"
using namespace std;





void TestPriorityQueue1()
{
    // priority_queue<元素类型, 底层容器类型, 比较规则类型>
    //priority_queue<int, vector<int>, greater<int>> q2; //建立小堆
    //priority_queue<int, vector<int>, less<int>> q1; //建立大堆 默认无参是大堆
    // 默认情况下，创建的是大堆，其底层按照小于号比较
     vector<int> v{3,2,7,6,0,4,1,9,8,5};
    // priority_queue<int> q1; //priority_queue在 queue头文件里面
    // for (auto& e : v)
    //     q1.push(e);

    //迭代器初始化
    //priority_queue<int> q1(v.begin(), v.end());//建立大堆
    priority_queue<int, vector<int>, greater<int>> q1(v.begin(), v.end());//建立小堆

    //取最大的前k个
    int k ;
    cin >> k ;
    while(k-- > 0 && !q1.empty())
    {
        cout << q1.top() << " ";
        q1.pop();
    }
    cout << endl;

}

void TestPriorityQueue2()
{
    vector<int> v{3,2,7,6,0,4,1,9,8,5};
    ldy::priority_queue<int> q1; 
    for (auto& e : v)
    q1.push(e);
    int k ;
    cin >> k ;
    while(k-- > 0 && !q1.empty())
    {
        cout << q1.top() << " ";
        q1.pop();
    }
     cout << endl;

}

void TestPriorityQueue3()
{
    vector<int> v{3,2,7,6,0,4,1,9,8,5};
    ldy::priority_queue<int, vector<int>, Less<int>> q3;
     for (auto& e : v)
    q3.push(e);
    int k ;
    cin >> k ;
    while(k-- > 0 && !q3.empty())
    {
        cout << q3.top() << " ";
        q3.pop();
    }  
     cout << endl;

//     ldy::priority_queue<int, vector<int>, Greater<int>> q2;
//     for (auto& e : v)
//     q2.push(e);
//     int m ;
//     cin >> m ;
//     while(m--)
//     {
//         cout << q2.top() << " ";
//         q2.pop();
//     }
//      cout << endl;
 }

// 仿函数/ 函数对象
// class Less
// {
// public:
//     bool operator()(int x ,  int y)
//     {
//         return x < y;
//     }
// };

template<class T>
class LessDate;

class Date
{
public:
    Date(int year , int month , int day)
    :_year(year) 
    , _month(month) 
    , _day(day)
    {

    }

    //友元函数
    friend ostream& operator<<(ostream& _cout , const Date& d);
    template<class T>
    friend class LessDate;


private:
    int _year;
    int _month;
    int _day;
};

ostream& operator<<(ostream& _cout , const Date& d)
{
    _cout << d._year << "-" << d._month << "-" << d._day;
    return _cout;
}

template<class T>
class LessDate
{
public:
    bool operator()(const Date& x , const Date& y)  
    {
        return (x._year < y._year) || 
            (x._year == y._year && x._month < y._month) ||
            (x._year == y._year && x._month == y._month && x._day < y._day);
            //return x < y;     
    }   
};

void TestPriorityQueue4()
{
    //大堆
    priority_queue<Date , vector<Date>, LessDate<Date>> q4;
    q4.push(Date(2023,1,1));
    q4.push(Date(2023,2,1));
    q4.push(Date(2023,3,1));
    q4.push(Date(2023,4,1));

    int k;
    cin >> k ;
    while(k-- && !q4.empty())
    {
        cout << q4.top() << " ";
        q4.pop();
    }
    cout << endl;
}


int main()
{
    //ldy::MyStack<int> st;
    //ldy::MyStack<int , vector<int>> st; 顺序栈
    //ldy::MyStack<int , list<int>> st;   链式栈
    // st.push(1);
    // st.push(2);
    // st.push(3);
    // st.push(4);
    // while(!st.empty())
    // {
    //     cout << st.top() << " ";
    //     st.pop();
    // }
    // cout << endl;

    // cout << st.top() << endl;
    // st.pop();
    // cout << st.top() << endl;

    //ldy::MyQueue<int> q;
    //ldy::MyQueue<int , vector<int>> q; 不能用vector实现 vector不支持头删
    // ldy::MyQueue<int , list<int>> q;   // 链式队列
    // q.push(1);
    // q.push(2);
    // q.push(3);
    // q.push(4);
    // while(!q.empty())
    // {
    //     cout << q.front() << " ";
    //     q.pop();
    // }
    // cout << endl;
    //TestPriorityQueue1();

    // Less lessFunc;
    // //看起来就像是调用函数一样
    // cout << lessFunc(1,2) << endl;
    // //本质是调用operator()(1,2)
    // cout << lessFunc.operator()(1,2) << endl;
    // TestPriorityQueue2();
    
    // //写成模板形式
    // Less<int> lessFunc;
    // cout << lessFunc(1,2) << endl;
    // Greater<int> greaterFunc;
    // cout << greaterFunc(1,2) << endl;
    //TestPriorityQueue3();
    TestPriorityQueue4();
}      





