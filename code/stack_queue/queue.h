//队列
#include <deque>
#include <list>
#include <vector>
#include <iostream>

namespace ldy
{
    //deque 实现队列的模板类
    template<class T , class Container = std::deque<T>>
    class MyQueue
    {
    public:
        // 入队
        void push(const T& x)
        {
            _c.push_back(x);
        }
        // 出队
        void pop()
        {
            _c.pop_front(); 
        }
        // 元素个数
        size_t size()
        {
            return _c.size();
        }
        // 查看队列是否为空
        bool empty()
        {
            return _c.empty();
        }
        // 查看队头元素
        T& front()
        {
            return _c.front();
        }
        // 查看队尾元素
        T& back() 
        {
            return _c.back();
        }
    private:
        Container _c;
    };
}