#include <deque>
#include <list>
#include <vector>
#include <iostream>
//stack<int , vector<int>> 顺序栈
//stack<int , list<int>> 链式栈
//deque 是双端队列 可以在头尾两端进行插入和删除操作
//deque 在功能上是 vector 和 list的复合体
namespace ldy
{
    //deque 实现栈的模板类
    //为什么不用deque实现栈 
    //1. 中间插入删除是很大的灾难
    //2. []的效率不够极致 相比vector和list效率低    
    //3. deque 不支持随机访问
    //优点是：头尾插入删除效率不错 缓存命中也不错
    //所以作为stack和queue的默认适配容器就很合适
    template<class T , class Container = std::deque<T>>
    class MyStack
    {
    public:
        // 入栈
        void push(const T& x)
        {
            _c.push_back(x);
        }
        // 出栈
        void pop()
        {
            _c.pop_back();
        }
        // 元素个数
        size_t size()
        {
            return _c.size();
        }
        // 查看栈是否为空
        bool empty()
        {
            return _c.empty();
        }
        // 查看栈顶元素
        T& top()
        {
            return _c.back();
        }

    private:
        Container _c;
    }; 
}
