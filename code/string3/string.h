#pragma once

#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
using namespace std;

namespace ldy
{
    class string
    {
    public:
        typedef char* iterator;
        typedef const char* const_iterator;

        iterator begin()
        {
            return _str;
        }

        iterator end()
        {
            return _str + _size;
        }

         const_iterator begin() const
        {
            return _str;
        }

        const_iterator end() const
        {
            return _str + _size;
        }


        string(); // 无参构造

        string(const char *str); // 带参构造

        ~string(); // 析构：释放空间
        
        void reserve(size_t n);
        void push_back(char ch);
        void append(const char *str);
        string& operator+=(char ch);//单个字符
        string& operator+=(const char* str);//字符串

        // 返回内部指针：前面的 const 限制修改字符，后面的 const 限制修改对象
        const char* c_str() const
        {
            return _str;
        }

        size_t size() const
        {
            return _size;
        }
        //可读可写
        char& operator[](size_t pos)
        {
            assert(pos < _size);
            return _str[pos];
        }
        //只读
        const char& operator[](size_t pos) const
        {
            assert(pos < _size);
            return _str[pos];
        }

    private:
        char *_str; // 指向字符存储空间的首地址
        size_t _size; // 已存的有效字符数，不含 '\0'
        size_t _capacity; // 最多能存的有效字符数，需额外留一位放 '\0'
        // 例：存 "hello" 且容量为 10，则 _size = 5，需分配 11 个字符位置
    
    };
}
