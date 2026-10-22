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
        string(const string& s); // 拷构造函数
        ~string(); // 析构：释放空间
        //预分配空间
        void reserve(size_t n);
        //添加字符
        void push_back(char ch);
        //添加字符串
        void append(const char *str);
        //+=
        string& operator+=(char ch);//单个字符
        string& operator+=(const char* str);//字符串
        //插入
        void insert(size_t pos, char ch);
        void insert(size_t pos, const char* str);
        //删除
        void erase(size_t pos = 0 , size_t len = string::npos);
        // 返回内部指针：前面的 const 限制修改字符，后面的 const 限制修改对象
        //查找
        size_t find(char ch , size_t pos = 0) const;
        size_t find(const char* str, size_t pos = 0) const;
        //子字符串
        string substr(size_t pos = 0, size_t len = string::npos) const;
        // 赋值运算符
        string& operator=(const string& s); 
        //交换
        void swap(string& s);
        
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

        static size_t npos;

    private:
        char *_str; // 指向字符存储空间的首地址
        size_t _size; // 已存的有效字符数，不含 '\0'
        size_t _capacity; // 最多能存的有效字符数，需额外留一位放 '\0'
        // 例：存 "hello" 且容量为 10，则 _size = 5，需分配 11 个字符位置
    
    };

    string operator+ (const string& lhs, const string& rhs);
	string operator+ (const string & lhs, const char* rhs);
	string operator+ (const char* lhs, const string& rhs);

    bool operator== (const string& lhs, const string& rhs);
	bool operator!= (const string& lhs, const string& rhs);
	bool operator>(const string& lhs, const string& rhs);
	bool operator<(const string& lhs, const string& rhs);
	bool operator>= (const string& lhs, const string& rhs);
	bool operator<= (const string& lhs, const string& rhs);

    ostream& operator<<(ostream& out, const string& s);
    istream& operator>>(istream& in, string& s);
	istream& getline(istream& in, string& s);
    istream& operator>>(istream& in, string& s);
	istream& getline(istream& in, string& s);
}
    void swap(ldy::string& s1, ldy::string& s2);


