#include <vector>
#include <iostream>
using namespace std;


//解耦设计 不会互相依赖 各司其职 bug容易处理 不会连锁反应
namespace ldy
{
    // 库里的 less<T>   template <class T , class Container = vector<T>, class Compare = less<T>>
    //template <class T ,LessDate//自己定义的Less<T>
    template <class T , class Container = vector<T>, class Compare = Less<T>>   

    class priority_queue
    {
    public:
        priority_queue()
        {

        }

        //建堆
        template <class InputIterator>
        priority_queue(InputIterator first , InputIterator last)
        :_con(first , last)
        {
            for(int i = (_con.size() - 1 - 1) /2 ; i >= 0 ; i--)
            {
                adjust_down(i);
            }
        }


        //向上调整
        void adjust_up(int child)
        {
            int parent = (child - 1) / 2;   
            while(child > 0 )
            {
                Compare com;
                if(com(_con[parent] , _con[child]))
                //if(_con[child] > _con[parent])
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

        //向下调整
        void adjust_down(int parent)
        {
           int child = parent * 2 + 1;  
           while(child < _con.size())
           {
                Compare com;
                if(com(child + 1 , _con.size()) && com(_con[child] , _con[child + 1]))
                {
                    child++;
                }
                
                if(com(_con[parent] , _con[child]))
               // if(_con[parent] < _con[child])
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
        //Compare _com;
    };
}


      
