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
			reserve(_capacity * 2);
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
	std::string s1("hello");
	s1.append("xxxxxxxxxxxx");

	cout << s1.c_str() << endl;

	s1 += ' ';
	s1 += "yyyyyyyyyyyyyy";
	cout << s1.c_str() << endl;

	string s1("string.cpp");
	string s2("aaaa");
	const char* p1 = "bb";
	//cout << (s1 < s2) << endl;
	//cout << (s2 < p1) << endl;
	//cout << (p1 < s2) << endl;

	cout << s1 + p1 << endl;
	cout << p1 + s1 << endl;
	cout << s1 + p1 + s2 + p1 << endl;
}


int main()
{
    std::string s1;
    cout << s1.c_str() << endl; // 标准库返回合法空字符串，可正常输出

    ldy::string s2;
    cout << s2.c_str() << endl; // 当前返回 nullptr，当字符串输出可能崩溃

    ldy::string s3("hello world");
    func(s3);

    teststring1();
    teststring2();
    return 0;
}













