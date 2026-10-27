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



#include "stack.h"
#include "queue.h"
using namespace std;

int main()
{
    ldy::MyStack<int> st;
    //ldy::MyStack<int , vector<int>> st; 顺序栈
    //ldy::MyStack<int , list<int>> st;   链式栈
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    while(!st.empty())
    {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;

    // cout << st.top() << endl;
    // st.pop();
    // cout << st.top() << endl;

    //ldy::MyQueue<int> q;
    //ldy::MyQueue<int , vector<int>> q; 不能用vector实现 vector不支持头删
    ldy::MyQueue<int , list<int>> q;   // 链式队列
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    while(!q.empty())
    {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}
  