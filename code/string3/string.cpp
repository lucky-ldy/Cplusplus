#include "string.h"

namespace ldy
{

    string::string()
        : _str(new char[4]), 
        _size(0), 
        _capacity(3)//存储有效字符数，不含 \0  也就是说实际空间比 _capacity 多 1
    {
        _str[0] = '\0';
    }
    
    string::string(const char *str)
        //这样strlen了三次，效率低
        // : _str(new char[strlen(str) + 1]), 
        // _size(strlen(str)), 
        // _capacity(strlen(str))

        //这样要注意成员函数定义的顺序 不要析构的时候导致越界了
        // : _size(strlen(str)),
        // _capacity(_size),
        // _str(new char[_size + 1])
        
        //最终的解决办法就是 只让_size 用初始化列表初始化
        : _size(strlen(str))
    {
        _capacity = _size;
        _str = new char[_size + 1];
        strcpy(_str, str);
    }

    string::~string()
    {
        delete[] _str;
		_str = nullptr;
		_size = _capacity = 0;

    }
    //拷构造函数
    string::string(const string& s)
        : _str(new char[s._size + 1]), 
        _size(s._size), 
        _capacity(s._capacity)
    {
        strcpy(_str, s._str);
    }

    //C++都是异地扩容 满了就再开辟空间
    void string::reserve(size_t n)
    {
        if (n > _capacity)
        { 
    //每次开空间多开一个 因为_capacity 是有效字符数，不含 \0  也就是说实际空间比 _capacity 多 1
            char* tmp = new char[n + 1];
            strcpy(tmp, _str);
            delete[] _str;
            _str = tmp;
            _capacity = n;
        }
    }

    void string::push_back(char ch)
    {
        if (_size == _capacity) 
        {
			reserve(_capacity == 0 ? 4 : _capacity * 2 + 1);
		}
		_str[_size] = ch;
		++_size;
		_str[_size] = '\0';
    }

    void string::append(const char *str)
    {
        size_t len = strlen(str);
        // 扩容
		if (_size + len > _capacity) 
        {
			reserve(_size + len);
		}
        strcpy(_str+_size, str);
		_size += len;
    }

    //花架子 底层就是push_back 可读性更强
    string& string::operator+=(char ch) 
    {
		push_back(ch);
		return *this;
	}
    //花架子 底层就是append 可读性更强
	string& string::operator+=(const char* str) 
    {
		append(str);
		return *this;
	}

    void string::insert(size_t pos, char ch)
    {
        assert(pos <= _size);
        if(_size == _capacity)
        {
            reserve(_capacity == 0 ? 4 : _capacity * 2 + 1);
        }

        //这里pos是size_t 类型 转换为int 类型
        // int end = _size;
        // while(end >= (int)pos)
        // {
        //     _str[end+1] = _str[end];
        //     --end;
        // }

        int end = _size + 1;
        while(end > pos)
        {
            _str[end] = _str[end-1];
            --end;
        }
        _str[pos] = ch;
        ++_size;
    }   

    void string::insert(size_t pos, const char* str)
    {
        assert(pos <= _size);
        size_t len = strlen(str);
        // 扩容
		if (_size + len > _capacity) 
        {
			reserve(_size + len);
		}
        //挪动数据
        // int end = _size ;
        // while(end >= (int)pos)
        // {
        //     _str[end + len] = _str[end];
        //     --end;
        // }
        size_t end = _size + len;
        while(end > pos + len -1)
        {
            _str[end] = _str[end-len];
            --end;
        }

        for(size_t i = 0 ; i < len ; ++i)
        {
            _str[pos + i] = str[i];
        }
        _size += len;
    }
    //因为 size_t 是无符号类型，-1 会转换成它的最大值，用作特殊标记。
    size_t string::npos = -1;
    //从下标 pos 开始删除 len 个字符；不传 len，默认删除到末尾。
    void string::erase(size_t pos , size_t len)
    {
        //len大于后面的字符个数  pos以后的都要删除
        if(len == string::npos || len >= _size - pos)
        {
            _str[pos] = '\0';
            _size = pos;
        }
        //len小于后面的字符个数
        else
        {
            for(size_t i = pos + len ; i < _size ; ++i)
            {
                _str[pos ++] = _str[i];
            }
            _size -= len;
            _str[_size] = '\0';
        }
    }
    //从pos位置开始 查找 ch 字符 第一次出现的位置
    size_t string::find(char ch , size_t pos) const
    {
        assert(pos < _size);
        for(size_t i = pos ; i < _size ; i++)
        {
            if(_str[i] == ch)
            return i;
        }
        return npos;
    }
    //从pos位置开始 查找 s 字符串 第一次出现的位置
     size_t string::find(const char* s, size_t pos) const
     {
        const char* ptr = strstr(_str + pos , s);
        if(ptr == nullptr)   return npos;
        else    return ptr - _str;
     }  

     string string::substr(size_t pos , size_t len ) const
     {
        //len大于后面的字符个数  pos以后的都要取
        if(len == npos  || len >= _size - pos)
        {
            len = _size - pos;
        }
        string sub;
        sub.reserve(len);
        for(size_t i = pos ; i < len ; i++)
        {
            sub += _str[pos +i];
        }
        return sub;
     }
     //赋值运算符
     string& string::operator=(const string& s)
     {
        if(this != &s)
        {
            delete[] _str;
            _str = new char[s._capacity + 1];
            strcpy(_str, s._str);
            _size = s._size;
            _capacity = s._capacity;
        }
        return *this;
     }

     /////////////////////////////////////////////////////
    string operator+ (const string& lhs, const string& rhs)
    {
        string s = lhs;
        s += rhs.c_str();
        return s;
    }
	string operator+ (const string & lhs, const char* rhs)
    {
        string s = lhs;
        s += rhs;
        return s;
    }
	string operator+ (const char* lhs, const string& rhs)
    {
        string s = lhs;
        s += rhs.c_str();
        return s;
    }
    ostream& operator<<(ostream& out, const string& s)
    {
        for(auto ch : s)
        {
            out << ch;
        }
        return out;
    }

    bool operator== (const string& lhs, const string& rhs)
    {
        return strcmp(lhs.c_str(), rhs.c_str()) == 0;
    }

    bool operator<(const string& lhs, const string& rhs) 
    {
		return strcmp(lhs.c_str(), rhs.c_str()) < 0;
	}

	bool operator!= (const string& lhs, const string& rhs) 
    {
		return !(lhs == rhs);
	}

	bool operator>(const string& lhs, const string& rhs) 
    {
		return !(lhs <= rhs);
	}
	
	bool operator>= (const string& lhs, const string& rhs) 
    {
		return !(lhs < rhs);
	}

	bool operator<= (const string& lhs, const string& rhs) 
    {
		return lhs < rhs || lhs == rhs;
	}

    void string::swap(string& s)
    {
       std::swap(_str, s._str);
       std::swap(_size, s._size);
       std::swap(_capacity, s._capacity);
    }

    istream& operator>>(istream& in, string& s) 
    {
		char ch;
		//in >> ch;
		ch = in.get();
		while (ch != ' ' && ch != '\n') 
        {
			s += ch;
			//in >> ch;
			ch = in.get();
		}
		return in;
	}

	istream& getline(istream& in, string& s) 
    {
		char ch;
		ch = in.get();
		while (ch != '\n') 
        {
			s += ch;
			ch = in.get();
		}
		return in;
	}
}


//const 对象不能调用普通的 begin 和 end
void func(const ldy::string& s) 
{
    //这里面的内容不能修改
	for (auto& ch : s) 
    {
		cout << ch << " ";
	}
	cout << endl;

	// 迭代器
	//ldy::string::const_iterator it = s.begin();
	auto it = s.begin();
	while (it != s.end()) 
    {
		// *it = 'x';
		cout << *it << '%';
		++it;
	}
	cout << endl;
}

void swap(ldy::string& s1, ldy::string& s2) 
{
	s1.swap(s2);
}

void teststring1()
{
	std::string s3;
	cout << s3.c_str() << endl;

	ldy::string s2;
	cout << s2.c_str() << endl;

	ldy::string s1("hello world");
	cout << s1.c_str() << endl;

	// 下标+[]  最常用
	for (size_t i = 0; i < s1.size(); i++) 
    {
		s1[i]++;
		cout << s1[i] << '|';
	}
	cout << endl;

	for (auto& ch : s1) 
    {
		ch--;
        cout << ch << '|';
	}
 
	cout << endl;

	// 迭代器
	ldy::string::iterator it = s1.begin();
	while (it != s1.end()) 
    {
		cout << *it << '%';
		++it;
	}
	cout << endl;
}

void teststring2() 
{
	// std::string s1("hello");
	// s1.append("xxxxxxxxxxxx");

	// cout << s1.c_str() << endl;

	// s1 += ' ';
	// s1 += "yyyyyyyyyyyyyy";
	// cout << s1.c_str() << endl;

	string s1("string.cpp");
	string s2("aaaa");
	const char* p1 = "bb";
	cout << (s1 < s2) << endl;
	cout << (s2 < p1) << endl;
	cout << (p1 < s2) << endl;

	cout << s1 + p1 << endl;
	cout << p1 + s1 << endl;
	cout << s1 + p1 + s2 + p1 << endl;
}

void teststring3() 
{
    ldy::string s1("hello world");
    s1.insert(5, 'x');
    cout << s1.c_str() << endl;

    ldy::string s2;
    s2.insert(0, 'x');
    cout << s2.c_str() << endl;

    ldy::string s3("hello world");
    s3.insert(5, " hello");
    cout << s3.c_str() << endl;

    ldy::string s4("lucky ldy");
    s4.erase(5, 3);
    cout << s4.c_str() << endl;

    ldy::string s5("ldyluckyeveryday");
    size_t pos = s5.find("luck", 0);
    size_t pos2 = s5.find("everday", 0);
    cout << pos << endl;
    cout << pos2 << endl;

    ldy::string s6 = s5.substr(0, 5);
    cout << s6.c_str() << endl;

    //地址不一样是深拷贝
    ldy::string s7(s6);
    cout << s7.c_str() << endl;

    s7 = s6;
    //s6 = s6;//自赋值，不执行赋值运算符
    cout << s7.c_str() << endl;

}

void teststring4() 
{
    ldy::string s1("hello world");
    ldy::string s2("ldyluckyeveryday");
    const char* p1 = "bb";
    cout << s1 + s2 << endl;
    cout << s1 + p1 << endl;
    cout << p1 + s1 << endl;

    s1.swap(s2);
    cout << s1.c_str() << endl;
    cout << s2.c_str() << endl;

    swap(s1 , s2);
    cout << s1.c_str() << endl;
    cout << s2.c_str() << endl;

    ldy::string s3;
    //cin >> s3;
    getline(cin, s3);
    cout << s3.c_str() << endl;
}


int main()
{
    std::string s1;
    cout << s1.c_str() << endl; // 标准库返回合法空字符串，可正常输出

    ldy::string s2;
    cout << s2.c_str() << endl; // 当前返回 nullptr，当字符串输出可能崩溃

    ldy::string s3("hello world");
    func(s3);

    // teststring1();
    // teststring2();
    teststring3();
    teststring4();
    
    return 0;
}













