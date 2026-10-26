//迭代器设立厉害的地方：
//1.统一的方式访问修改容器 不用关系容器的底层结构 本质都是一种封装
//2.算法和容器很好的融合 实现泛型的算法
#include<iostream>
#include<cstddef>
#include<initializer_list>
#include<list>
#include<algorithm>
#include<forward_list>
#include<assert.h>

namespace ldy
{
    template<class T> class list_node;
    template<class T> class list_iterator;
    template<class T> class list_const_iterator;
    template<class T> class list;
    
    //节点类
    template<class T>
    class list_node
    {
        friend class list_iterator<T>;
        friend class list_const_iterator<T>;
        friend class list<T>;
        list_node<T>* _next;
        list_node<T>* _prev;
        T _val;

        list_node(const T& val = T())
        :_next(nullptr)
        ,_prev(nullptr)
        ,_val(val)
        {
            
        }
    };

    //两层迭代器类 就能实现一个类模板 实现两种迭代器的功能
    // template<class T,class Ref>
    // struct list_iterator
    // {
    //     typedef list_node<T> Node;
    //     typedef list_iterator<T,Ref> Self;
    //     Node* _node; 
    //     list_iterator(Node* node)
    //     :_node(node)
    //     {
            
    //     }
            //这里的Ref 可以是T& 也可以是const T&
    //     Ref operator*()
    //     {
    //         return _node->_val;
    //     }
    // }
 

    //普通迭代器类 用类来封装指针，实现迭代器的功能
    template<class T>
    class list_iterator
    {       
        friend class list<T>;

        typedef list_node<T> Node;
        Node* _node;
    public:
        list_iterator(Node* node)
        :_node(node)
        {
            
        }

        T& operator*()
        {
            return _node->_val;
        }

        list_iterator<T>& operator++()
        {
            _node = _node->_next;
            return *this;
        }

        list_iterator<T> operator++(int)
        {
            list_iterator<T> old(*this);
            _node = _node->_next;
            return old;
        }

        list_iterator<T>& operator--()
        {
            _node = _node->_prev;
            return *this;
        }

        bool operator!=(const list_iterator<T>& it)
        {
            return _node != it._node;
        }
    };

    //const迭代器类 访问可读不可写
    template<class T>
    class list_const_iterator
    {
        friend class list<T>;

        typedef list_node<T> Node;
        Node* _node;
    public:
        list_const_iterator(Node* node)
        :_node(node)
        {
            
        }

        const T& operator*() const
        {
            return _node->_val;
        }

        list_const_iterator<T>& operator++()
        {
            _node = _node->_next;
            return *this;
        }

        list_const_iterator<T> operator++(int)
        {
            list_const_iterator<T> old(*this);
            _node = _node->_next;
            return old;
        }

        list_const_iterator<T>& operator--()
        {
            _node = _node->_prev;
            return *this;
        }

        bool operator!=(const list_const_iterator<T>& it) const
        {
            return _node != it._node;
        }
    };


    //链表类
    template<class T>
    class list
    {
        typedef list_node<T> Node;
    public:
    //typedef Node* iterator;不支持迭代器功能
    //普通节点指针可以 ++，但链表节点不保证在内存中连续，++ 只会移动到下一个内存地址，不会跳到下一个节点。
    //要让 iterator 真正支持链表遍历，通常要写一个迭代器类，让它的 ++ 操作沿着节点的 _next 前进。
        typedef list_iterator<T> iterator;
        typedef list_const_iterator<T> const_iterator;

        //更好的写法
        // typedef list_iterator<T ,T&> iterator;  
        // typedef list_const_iterator<T ,const T&> const_iterator;

        iterator begin()
        {
            return iterator(_head->_next);
        }

        iterator end()
        {
            return iterator(_head);
        }
         
        const_iterator begin() const
        {
            return const_iterator(_head->_next);
        }

        const_iterator end() const
        {
            return const_iterator(_head);
        }
        
        void empty_init()
        {
            _head = new Node;
            _head->_next = _head;
            _head->_prev = _head;
            _size = 0;
        }

        list() 
        {   
            empty_init();
        }

        ~list()
        {
            clear();
            delete _head;
            _head = nullptr;
        }

        //花括号初始化构造lt = {10 , 20 , 30 , 40 , 50};
        list(std::initializer_list<T> lt)
        {
            empty_init();
            for(auto &x : lt)
            {
                push_back(x);
            } 

        }
        //拷贝构造函数 lt(lt1) 
        list(list<T>& lt)
        {
            empty_init();
            for(auto &x : lt)
            {
                push_back(x);
            } 
        }

        //赋值运算符 lt2 = lt3;
        list<T>& operator=(list<T>& lt)
        {
            // if(this != &lt)
            // {
            //     clear();
            //     for(auto &x : lt)
            //     {
            //         push_back(x);
            //     } 
            // }
            // return *this;
            swap(lt);
            return *this;

        }

        void swap(list<T>& lt)
        {
            std::swap(_head, lt._head);
            std::swap(_size, lt._size);
        }
        
        void clear()
        {
            iterator it = begin();
            while(it != end())
            {
                //erase 执行后会失效 it就会失效 所以要先保存it的下一个位置
                // iterator next = it;
                // ++next;
                // erase(it);
                // it = next;
                //最简单的方式
                //erase以后it 失效 erase返回删除位置下一个位置的迭代器
                it = erase(it);
            }
        }

        void push_back(const T& val)
        {
            // Node* tail = _head->_prev;
            // Node* newnode = new Node(val);

            // tail->_next = newnode;
            // newnode->_prev = tail;
            // newnode->_next = _head;
            // _head->_prev = newnode;
            // ++_size;
            insert(end(), val);
        }

        void push_front(const T& val)
        {
            insert(begin(), val);
        }

        void pop_back()
        {
            erase(--end());
        }

        void pop_front()
        {
            erase(begin());
        }
        
        void print_ldylist(list<T>& lt)
        {
            Node* cur = lt._head->_next;
            while(cur != lt._head)
            {
                std::cout << cur->_val << " ";
                cur = cur->_next;
            }
            std::cout << std::endl;
        }

        void insert(iterator pos, const T& val)
        {
            Node* cur = pos._node;  
            Node* prev = cur->_prev;
            Node* newnode = new Node(val);
            //prev -> newnode -> cur
            prev->_next = newnode;
            newnode->_prev = prev;
            newnode->_next = cur;
            cur->_prev = newnode;
            ++_size;
        }

        iterator erase(iterator pos)
        {
            assert(pos != end());
            Node* cur = pos._node;
            Node* prev = cur->_prev;
            Node* next = cur->_next;
            prev->_next = next;
            next->_prev = prev;
            delete cur;
            --_size;

            return iterator(next);
        }


    private:
        Node* _head;
        std::size_t _size;
   

};
}
