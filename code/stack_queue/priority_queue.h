#include <vector>
#include <iostream>
using namespace std;


//解耦设计 不会互相依赖 各司其职 bug容易处理 不会连锁反应
namespace ldy
{
    template <class T , class Container = vector<T>, class Compare = less<T>>
    class priority_queue
    {
    public:
        void adjust_up(int child)
        {
            int parent = (child - 1) / 2;   
            while(child > 0 )
            {
                if(_con[child] > _con[parent])
                {
                    swap(_con[child], _con[parent]);
                    child = parent;
                    parent = (child - 1) / 2;
                }
                else
                {
                    break;
                }
            }
        }

        void adjust_down(int parent)
        {
           int child = parent * 2 + 1;  
           while(child < _con.size())
           {
                if(child + 1 < _con.size() && _con[child + 1] > _con[child])
                {
                    child++;
                }

                if(_con[parent] < _con[child])
                {
                    swap(_con[parent], _con[child]);
                    parent = child;
                    child = parent * 2 + 1;
                }
                else
                {
                    break;
                }

           }
        }
        
        void push(const T& x)
        {
            _con.push_back(x);
            adjust_up(_con.size() - 1);
        }

        void pop()
        {
            swap(_con[0], _con[_con.size() - 1]);
            _con.pop_back();
            adjust_down(0);
        }

        const T& top() 
        {
            return _con[0];
        }

        bool empty()
        {
            return _con.empty();
        }







    private:
        Container _con;
        Compare comp;
    };
}


 