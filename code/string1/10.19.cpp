//一、标准库中的string类
// #include<iostream>

// int main() 
// {
// 	char arr1[] = "abcd01";//7个字节
// 	char arr2[] = "开心abcd01";//13个字节 1个中文字符占3个字节
// 	arr2[2]++;
// 	arr2[2]++;
// 	arr2[2]++;
// 	arr2[2]++;

// 	arr2[5]--;
// 	arr2[5]--;
// 	arr2[5]--;

// 	return 0;
// }

#include<iostream>
#include<string.h>//strcpy、strlen、strcmp
#include<string>//std::string类
#include<list>

using namespace std;


// string类对象的常见构造
//1. string() （重点）构造空的string类对象，即空字符串
//2. string(const char* s) （重点） 用C-string来构造string类对象
//3. string(size_t n, char c) （重点） string类对象中包含n个字符c
//4. string(const string&s) （重点） 拷贝构造函数
void test_string1()
{
    string s1;//创建空字符串，内容是 ""，长度为 0。
    string s2("hello world");//拷贝初始化 11
    string s4 = s2;//拷贝构造函数
	string s5 = "开心abcd01";//拷贝初始化 6 + 6 = 12 
    //size()方法返回string类对象中包含的字符个数
    cout << s2.size() << endl;
	cout << s5.size() << endl;
	cin >> s1;
	cout << s1 << endl;

    //配合list使用
    list<string> lt; // 模板一个string类型的list容器
	string s6("张三");//先构造
	lt.push_back(s6);//再传

    //等价于
	lt.push_back("李四");//隐式类型转换 优化
	lt.push_back("李四xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
    // 数据和方法是分离的
	char arr1[] = "开心abcd01";
	char arr2[128]; // malloc
	strcpy(arr2, arr1);
}

void test_string2() 
{
	string q1("hello worldxxxxxxxxxxxxxx");
	string q2(q1, 6, 3); //拷贝q1 从下标6开始的三个字符 
	cout << q2 << endl;
	//string q3(q1, 6, q1.size()-6);
	//string q3(q1, 6, 1000);//超过了长度 也默认拷贝到末尾
	string q3(q1, 6);//不给要求的长度 默认拷贝到末尾
	cout << q3 << endl;

    //取前n个字符构造q4
    string q4("hello worldxxxxxxxxxxxxxx", 7);
	cout << q4 << endl;

    //用10个*号构造q5
	string q5(10,'*');
	cout << q5 << endl;

    //把q5的内容赋值给已经存在的q4
	q4 = q5;
	cout << q4 << endl;
    
    //拷贝赋值 不是拷贝构造
    q4 = "##################";
	cout << q4 << endl;

	q4 = "!";
	cout << q4 << endl;

}

//size 和 [] 结合使用非常遍历和高效
// 编译器：检查官+翻译器
void test_string3() 
{
	string m1("12345");//拷贝初始化

    //因为 string 类重载了 [] 运算符，所以它也支持像数组一样的下标写法。
	m1[0]++; // 调用m1.operator[](0) 修改1 1+1=2
	m1[2] = '4';//修改 3 变成 4
	//cout << m1[30] << endl; // 越界报错
	cout << m1[3] << endl;
	cout << m1 << endl;

	char arr[] = "12345";
	arr[0]++; // *(arr+0) 
	//cout << arr[30] << endl; // 越界不报错

    //数组不能实现追加
	m1 += "xxxxxx"; //把右边的字符追加到末尾
	cout << m1 << endl;
}
 

//length()：字符串的“长度”。
//建议:size()：与 vector、list 等容器的命名保持一致。（更合理一点 后续都用size())
void test_string4() 
{
    string n1("12345");
	cout << n1 << endl;
	cout << n1.max_size() << endl;//返回string类对象中可以容纳的最大字符个数
	cout << n1.size() << endl;//5
	cout << n1.capacity() << endl << endl;//返回string类对象中当前可以容纳的最大字符个数 15
	
	n1 += "11111111111";//追加11个字符 5+11=16
	cout << n1.size() << endl;//16
	cout << n1.capacity() << endl << endl;//返回string类对象中当前可以容纳的最大字符个数 31

	n1.clear();//清空字符串内容 变成空字符串
	cout << n1.size() << endl;//0
	cout << n1.capacity() << endl << endl;//空间大小不变 30

	for (size_t i = 0; i < n1.size(); i++) 
    {
		n1[i] += 1;
	}
	cout << n1 << endl;

	for (size_t i = 0; i < n1.length(); i++) 
    {
		cout << n1[i] << '|';
	}
}

//两种访问字符串的方式
void test_string5()
{
	string s1("12345");

	// 1.下标+[] 遍历字符串 只有string 和 vector可以使用下标访问
	for (size_t i = 0; i < s1.length(); i++) 
	{
		cout << s1[i] << '|';
	}
		cout << endl;

	// 2.迭代器遍历字符串 更广泛
	//迭代器是一个类对象 里面重载了*运算符和++运算符 可以看作指针
	string::iterator it = s1.begin(); //第一个字符的位置
	while (it != s1.end()) 
	{
		cout << *it << '%';
		it++;
	}
	cout << endl;

	//3.范围for循环(自动判断开始和结束位置 自动迭代) 最便利
	//底层就是被替代为迭代器
	for (auto ch : s1) 
	{
		cout << ch << '&';
	}
	cout << endl;

	list<int> lt(10, 0);
	list<int>::iterator lit = lt.begin();
	while (lit != lt.end()) 
	{
		cout << *lit << '#';
		++lit; // lit.operator++()
	}
	cout << endl;

	//所有容器都可以使用
	for (auto m : lt) 
	{
		cout << m << '*';
	}
	cout << endl;

}


//二、仅仅反转字母
// 输入：s = "ab-cd"
// 输出："dc-ba"
class Solution 
{
public:
	bool isLetter(char ch)
	{
		if(ch >= 'a' && ch <= 'z')
			return true;
		if(ch >= 'A' && ch <= 'Z')
			return true;
		
		return false;
	}

    string reverseOnlyLetters(string s) 
	{
		int left = 0, right = s.size() - 1;
		while (left < right)
		{
			while (left < right && !isLetter(s[left]))
				left++;

			while (left < right && !isLetter(s[right]))
				right--;

			swap(s[left], s[right]);
			left++;
			right--;
		}
		return s;
        
    }
};

//三、找出字符串中的第一个唯一字符
// 输入: s = "leetcode"			
// 输出: 0						
class Solution1 
{
public:
    int firstUniqChar(string s)
	{
        int count[26] = {0};
		//for(auto ch : s)
		// {
		// 	count[ch - 'a']++;//把字母转换成数组下标 进行计算次数
		// }
		for (int i = 0; i < s.size(); i++)
		{
			count[s[i] - 'a']++;//把字母转换成数组下标 进行计算次数
		}

		for (int i = 0; i < s.size(); i++)
		{
			if (count[s[i] - 'a'] == 1)
			{
				return i;
			}
		}

		return -1;
    }

};


int main()
{
    test_string1();
    test_string2();
    test_string3();
    test_string4();
	test_string5();



}



















