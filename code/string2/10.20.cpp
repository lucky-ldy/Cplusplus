//一、迭代器的一些应用 以及 一些修改字符串内容的成员函数

#include<iostream>
#include<string.h>//strcpy、strlen、strcmp
#include<string>//std::string类
#include<list>//std::list 双向链表
#include<map>//std::map 键值对容器
#include <algorithm> //
using namespace std;


void test_string6() 
{
    // 范围 for：自动依次访问每个元素。
    string s1("12345");
	// ch 是 char 类型的副本；用 auto& 才能修改原字符。
	for (auto ch : s1) 
    {
		cout << ch << '%';
	}
	cout << endl; // 输出：1%2%3%4%5%

	// auto 推导出迭代器类型，以下两种声明等价。
	string::iterator lit = s1.begin();

	// auto lit = s1.begin();

	// begin() 指向首元素；end() 是尾后位置，不能解引用。
	while (lit != s1.end()) 
    {
		cout << *lit << '%'; // lit 是位置，*lit 是数据。
		++lit; // 移到下一个元素。
	}
	cout << endl; // 输出 10 次 0%。
    //如果要对数据进行修改
    //1.用迭代器 *lit
    while (lit != s1.end()) 
    {
		(*lit)++;
		cout << *lit << '%';
		++lit;
	}
    //2.用auto&
    for(auto& x : s1) //x是数据的引用
    {
        x++;
        cout << x << '.';
    }
    
    // auto 根据初始值推导类型，确定后不再改变。
    auto x1 = 1;   // int
	auto x2 = 0.1; // double
	int x3 = 1;    // 与 x1 类型相同。

    // map 的键和值都是 string，需要包含 <map>。
    std::map<std::string, std::string> m;
	// auto 简化迭代器声明。
	//std::map<std::string, std::string>::iterator mit = m.begin();
	auto mit = m.begin(); //这种情况下不能简单确认类型的时候用auto能直接识别

    int a = 1;
    auto p1 = &a;
    auto* p2 = &a; 
//    auto* p3 = a; //报错 auto*代表必须hi指针初始化
    auto& r1= a; //r1是a的引用
    const auto& r2 = a; //r2是a的const引用
//    auto array[3] = {4 , 5, 6}; //auto 不能推数组

    // C++11 也支持数组这样修改
	int array[] = { 1, 2, 3, 4, 5 };
	for (auto& e : array) // 要修改需要加 &
		e *= 2;

	// for (auto e : array)
	for (const auto& e : array) // 推荐
		cout << e << " " << endl;

}

void test_string7() 
{
    //普通迭代器
    string s1("12345");
	// 遍历容器时，可读可写
	string::iterator it1 = s1.begin(); 
	while (it1 != s1.end()) 
    {
		//(*it1)++;
		cout << *it1 << '%';
		++it1;
	}
	cout << endl;

    //反向迭代器 反向遍历 要用配套的rbegin rend
    string::reverse_iterator rit = s1.rbegin();
    while (rit != s1.rend()) 
    {
        //(*it)++; const迭代器不能修改数据
        cout << *rit << '%';
        ++rit;  
    }
    cout << endl;
}

void test_string8() 
{
	string s1("12345");
    //反转逆置 reverse 脱离泛型 脱离具体存储结构 访问数据通过迭代器
	reverse(s1.begin(), s1.end());
    
    list<int> lt = {1 , 2 , 3 , 4 ,5};
    reverse(lt.begin(),lt.end());
    
    //追加一个字符push_back
    string s2("hello");
    s2.push_back(' ');
    s2.push_back('w');
    cout << s2 << endl;
    //追加多个字符append
    s2.append(" world");
    cout << s2 << endl;

    //实际上这些接口用的极少
    s2.append(s1.begin() , s1.end());
    cout << s2 << endl;

    s2.append(++s1.begin() , --s1.end());
    cout << s2 << endl;

    //用的最多的接口operator+= 实用性高
    //有了这个前面的push_back 和 append就显得不那么好用了
    string s3("hello");
    s3 += "world";
    cout << s3 << endl;

    s3 += s3;
    cout << s3 << endl;

    s3.assign("xxxxxxx");
    //等价于 s3 = "xxxxxx";
    cout << s3 << endl;

}

void test_string9()
{
    string s1("12345");
    cout << s1 << endl;
    //insert插入
    //在下标0的位置插入
    s1.insert(0 , "xxxx");

    //在下标0的位置插入一个字符
    s1.insert(0 , 1 , 'y');
    //迭代器版本 头插
    s1.insert(s1.begin(), 'y');
    cout << s1 << endl;

    s1.insert(s1.begin() + 5, 'm');
    cout << s1 << endl;

    //erase删除
    string s2("12345678");
    cout << s2 << endl;
    s2.erase(0,1);//从0位置删除一个 头删
    cout << s2 << endl;
    //中间删除
    s2.erase(4,2);
    cout << s2 << endl;

    s2.erase(4);//给定位置删除到结尾
    cout << s2 << endl;

    //repalce替代
    string s3("12345678");
    cout << s3 << endl;
    s3.replace(3 , 3 ,"abc");
    cout << s3 << endl;
    //谨慎使用 多替换少 少替换多 都涉及挪动数据 效率低
    s3.replace(3 , 5 ,"abc");
    cout << s3 << endl;

    //swap
    //C++ 11 之前 s1.swap(s3)效率更好 之后swap(s1 , s3)被优化了 他们效率都很好 
    s1.swap(s3);//string里的
    //swap(s1 , s3);//C++标准库的
    cout << s1 << endl;
    cout << s3 << endl;

    //把s4的空格换成%%
    string s4("hello world hello world");
    string s5;
    s5.reserve(s4.size());//保留储备s4需要的空间 提高运行效率
    for(auto ch : s4)
    {
        if(ch != ' ')   s5 += ch;
        else    s5 += "%%";
    }
    cout << s5 << endl;
    s4.swap(s5);
    cout << s4 << endl;

    string s6;
    size_t begin1 = clock();
    int n = 1000000;
    for(size_t i = 0 ; i < n ; i++)
    {
        s6 += 'x';//不断地扩容
    }
    size_t end1 = clock();
    cout << end1 - begin1 << endl;

    //对比性能差距 有reserve的能提高效率
    string s7; 
    size_t begin2 = clock();
    int n1 = 100000;
    s7.reserve(n);
    for(size_t i = 0 ; i < n1 ; i++)
    {
        s7 += 'x';
    }
    size_t end2 = clock();
    cout << end2 - begin2 << endl;
} 

void func(const string& s) 
{
    //const迭代器
    //遍历容器时，可读不可写
    //const_iterator是让指向的内容不能修改
    string::const_iterator it = s.begin();
    while (it != s.end()) 
    {
          //(*it)++; const迭代器不能修改数据
        cout << *it << '$';
        ++it;  
    }
    cout << endl;

    //const反向遍历
    string::const_reverse_iterator nit = s.rbegin();
    while (nit != s.rend()) 
    {
          //(*it)++; const迭代器不能修改数据
        cout << *nit << '$';
        ++nit;  
    }
    cout << endl;

}


int main()
{
    string s2("12345");
    // for 写在函数体等执行环境中，不能直接写在全局作用域或类体中。
    //test_string6();
    test_string7();
    test_string8();
    test_string9();
    //func(s2);
      
}


//二、验证回文串 移除所有非字母数字字符之后 短语正反读都一样
// 输入: s = "A man, a plan, a canal: Panama"
// 输出：true
// 解释："amanaplanacanalpanama" 是回文串。

class Solution 
{
public:
    bool isLetterOrNumber(char ch)
    {
        return (ch >= '0' && ch <= '9')
        || (ch >= 'a' && ch <= 'z')
        || (ch >= 'A' && ch <= 'Z');
    }

    bool isPalindrome(string s) 
    {
        // 先小写字母转换成大写，再进行判断
        for(auto& ch : s)
        {
            if(ch >= 'a' && ch <= 'z')
            ch -= 32;
        }

        int begin = 0, end = s.size()-1;
        while(begin < end)
        {
            while(begin < end && !isLetterOrNumber(s[begin]))
            ++begin;
            while(begin < end && !isLetterOrNumber(s[end]))
            --end;
            if(s[begin] != s[end])
            {
                return false;
            }
            else
            {
                ++begin;
                --end;
            }
        }

        return true;
    }
};


//三、字符串相加
class Solution1 
{
public:
    string addStrings(string num1, string num2) 
    {
        string retstr;
        //从后往前加 
        retstr.reserve(max(num1.size() , num2.size()) + 1);//提前开空间防止反复扩容 提高效率
        int end1 = num1.size()-1 , end2 = num2.size()-1;
        int next = 0;//进位
        while(end1 >= 0 || end2 >= 0)
        {
            int val1 = end1 >= 0 ? num1[end1--] - '0' : 0;
            int val2 = end2 >= 0 ? num2[end2--] - '0' : 0;
            int ret = val1 + val2 + next;
            next = ret /10 ; //进位
            ret = ret % 10;
            
            //头插 从后往前加的 所以先是个位 然后十位 百位
            // retstr.insert(0 , 1 , '0' + ret);
            retstr += ('0' + ret);//尾插
        }
        if(next ==1)
        {
            //retstr.insert(0 , 1, '1'); 头插
            retstr += '1';    //尾插
        }

        //return retstr; //头插
        //尾插之后反转一下变成正确字符串
        reverse(retstr.begin() , retstr.end());
        return retstr;
    }
  
};