#include <algorithm>
#include <iostream>
#include <map>
#include <set>
using namespace std;

//一、set容器
//set的定义是：一种存放不重复元素，并按顺序自动排列的关联容器。
//例如，插入 3、1、3 后，`set` 中保存的是 1、3。它通常用平衡二叉搜索树实现。

//set底层是⽤红⿊树实现，增删查效率是 O(logN)，迭代器遍历是走的搜索树的中序，所以是有序的。
void test_set1()
{
    std::set<int> s1;
    s1.insert(1);
    s1.insert(2);
    s1.insert(3);
    s1.insert(4);
    s1.insert(5);

    for (auto e: s1)
    {
        cout << e << " ";
    }
    cout << endl;

    int x;
    cin >> x;
    s1.find(x);
    // auto it = s1.find(x);
    // if (it != s1.end())
    // {
    //     s1.erase(it);
    // }
    //等价于
    s1.erase(x);

    for (auto e: s1)
    {
        cout << e << " ";
    }
    cout << endl;

    set<int>::iterator it = s1.begin();
    while (it != s1.end())
    {
        //*it += 1; //不支持修改
        cout << *it << " ";
        it++;
    }
    cout << endl;

    if(s1.count(5))
    {
        cout << "5在set中" << endl;
    }

}

void test_set2()
{
    std::set<int> s2;
    s2.insert(1);
    s2.insert(2);
    s2.insert(3);
    s2.insert(4);
    s2.insert(5);
    s2.insert(6);
    s2.insert(9);
    s2.insert(10);
    for (auto e: s2)
    {
        cout << e << " ";
    }
    cout << endl;

    //删除[2,8]之间的元素
    //lower_bound()返回第一个大于等于x的元素的迭代器 左闭
    //upper_bound()返回第一个大于x的元素的迭代器 右开
    s2.erase(s2.lower_bound(2), s2.upper_bound(8));
    for (auto e: s2)
    {
        cout << e << " ";
    }
    cout << endl;

    //去重 排序
    set<int> s3 = { 3,4,2,4,2,1 };
	for (auto e : s3) {
		cout << e << " ";
	}
	cout << endl;

	set<string> strset = { "sort", "insert", "add" };
	// 遍历string比较ascll码大小顺序遍历的
	for (auto& e : strset)
	{
		cout << e << " ";
	}
	cout << endl;

    auto pos1 = std::find(s2.begin(), s2.end(), 5);//O(N)
    auto pos2 = s2.find(5);//O(logN)

}

//multiset和set的差异

void test_set3()
{
    // 相比set不同的是，multiset是排序，但是不去重
	multiset<int> s = { 2,2,7,2,4,8,4,2,4,9 };
	auto it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

    // 相比set不同的是，x可能会存在多个，find查找中序的第一个
	int x;
	cin >> x;
	auto pos = s.find(x);
	while (pos != s.end() && *pos == x)
	{
		cout << *pos << " ";
		++pos;
	}
	cout << endl;

    // 相比set不同的是，count会返回x的实际个数
	cout << s.count(x) << endl;

	// 相比set不同的是，erase给值时会删除所有的x
	s.erase(x);
	for (auto e : s)
	{
		cout << e << " ";
	}
	cout << endl;


}



int main()
{
    //test_set1();
    //test_set2();
    test_set3();




    return 0;
}
