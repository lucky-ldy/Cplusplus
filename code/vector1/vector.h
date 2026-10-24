#pragma once
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
using namespace std;

namespace ldy 
{
    template<class T>
    class vector
    {
    public:
        typedef T* iterator;
		typedef const T* const_iterator;

        iterator begin()
        {
            return _start;
        }

        iterator end()
        {
            return _finish;
        }

        const_iterator begin() const
        {
            return _start;
        }

        const_iterator end() const
        {
            return _finish;
        }
        
        vector()
        : _start(nullptr), 
        _finish(nullptr), 
        _end_of_storage(nullptr)
        {

        }

        T& operator[](size_t pos)
        {
            assert(pos < size());
            return _start[pos];
        }

        const T& operator[](size_t pos) const
        {
            assert(pos < size());
            return _start[pos];
        }
        //类里面声明
        void resize(size_t n , const T& val);
        void insert(iterator pos, const T& x);
        void erase(iterator pos);
        void reserve(size_t n);
        void push_back(const T& x);
        void pop_back();
        //返回容器的容量
        size_t capacity() const
        {
            return _end_of_storage - _start;
        }
        //返回容器的大小
        size_t size() const
        {
            return _finish - _start;
        }
        //判断容器是否为空
        bool empty() const
        {
            return _start == _finish;
        }
  
    private:
		iterator _start;
		iterator _finish;
		iterator _end_of_storage;
    };

    //类外面实现
    template<class T>
    void vector<T>::reserve(size_t n)
    {
        //不考虑缩容 因为不支持释放部分空间
        if(n > capacity())
       {
            size_t old_size = size();
            T* tmp = new T[n];
            //开空间 拷贝数据 释放旧空间
            if(_start)
            {
                memcpy(tmp, _start, size()*sizeof(T));
                delete[] _start;
            }
            _start = tmp; 
            _finish = tmp + old_size;
            _end_of_storage = tmp + n;
       }
    }

    template<class T>
    void vector<T>::insert(iterator pos, const T& x)
    {
        assert(pos >= _start);
        assert(pos <= _finish);
        //扩容之后 变成新空间 pos会失效
         if(_finish == _end_of_storage)
        {
            size_t len = pos - _start;
            size_t new_capacity = capacity() == 0 ? 4 : capacity() * 2 ;
            reserve(new_capacity);
            pos = _start + len; //更新pos
        }
        //挪动数据
        memmove(pos+1 , pos , sizeof(T) * (_finish - pos));
        *pos = x;
        _finish++;
    }

    template<class T>
    void vector<T>::erase(iterator pos)
    {
        assert(pos >= _start);
        assert(pos < _finish);

        //挪动数据
        iterator it = pos + 1;
        while( it < _finish)
        {
            *(it - 1) = *it;
            ++it;
        }
        --_finish;

    }

    template<class T>
    void vector<T>::push_back(const T& x)
    {   
        if(_finish == _end_of_storage)
        {
            size_t new_capacity = capacity() == 0 ? 4 : capacity() * 2 ;
            // T* tmp = new T[new_capacity];
            // size_t old_size = size();
            // if(_start)
            // {
            //     memcpy(tmp, _start, size()*sizeof(T));
            //     delete[] _start;
            // }
            // _start = tmp; 
            // _finish = tmp + old_size;
            // _end_of_storage = tmp + new_capacity;
            reserve(new_capacity);
        }

        *_finish++ = x;
    }

    template<class T>
    void vector<T>::pop_back()
    {
        assert(!empty());
        _finish--;
    }





}
