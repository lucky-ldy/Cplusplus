#include <algorithm>
#include <iostream>
#include <map>
#include <set>
using namespace std;

//一、set容器
//set的定义是：一种存放不重复元素，并按顺序自动排列的关联容器。
//例如，插入 3、1、3 后，`set` 中保存的是 1、3。它通常用平衡二叉搜索树实现。

//set底层是?红?树实现，增删查效率是 O(logN)，迭代器遍历是走的搜索树的中序，所以是有序的。
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


//map 是 C++ 标准库中的关联容器 经典的key-value对
//用于保存“键—值”对。每个键唯一，元素会按键自动排序。
void test_map1()
{
    //pair 是 C++ 标准库中的关联容器 经典的key-value对
    map<string, string> m1;
    //明确写出 pair 类型并直接构造。
    m1.insert(pair<string, string>("sort", "排序"));
    m1.insert(pair<string, string>("insert", "插入"));
    // 直接使用key-value对初始化
    m1.insert({"add", "添加"});
    //先创建一个 pair，再赋给变量 p
    pair<string, string> p = {"delete", "删除"};
    for (auto& e: m1)
    {
        cout << e.first << ":" << e.second << endl;
    }
    cout << endl;

    map<string, string>::iterator it = m1.begin();
    while (it != m1.end())
    {
        cout << it->first << ":" << it->second << endl;
        it->second = "修改";//可以修改value
        //it->first = "修改";//修改key是不允许的
        cout << it->first << ":" << it->second << endl;
        it++;
    }
    cout << endl;
}

void test_map2() 
{
	map<string, string> dict;
	dict.insert(make_pair("sort", "排序"));
	// key不存在->插入 {"insert", string()}
	dict["insert"]; // {key, value默认构造}
	// 插入+修改value
	dict["left"] = "左边";

	// key存在->查找
	cout << dict["left"] << endl;
	// 修改value
	dict["left"] = "左边、剩余";
	cout << dict["left"] << endl;

	int i = int();
}

void test_map3()
{
    //这里统计每个水果的个数 是怎么实现的
    //不存在先插入insert<key,0> 同时返回次数value的引用 存在后进行查找+1 
    string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉" };
	map<string, int> countMap;
	for (auto& str : arr) 
    {
		/*auto it = countMap.find(str);
		if (it == countMap.end()) {
			countMap.insert({str, 1});
		}
		else {
			it->second++;
		}*/

        countMap[str]++;
	}

    for (auto& e: countMap)
    {
        cout << e.first << ":" << e.second << endl;
    }
    cout << endl;
}

void test_map4()
{
    multimap<string, int> multimap;
	map<string, int> m;
    //key可以重复 三个值
	multimap.insert({ "张三", 1 });
	multimap.insert({ "张三", 2 });
	multimap.insert({ "张三", 2 });

    //key唯一 一个值
	m.insert({ "张三", 1 });
    //value不会修改
	m.insert({ "张三", 2 });

}

#
// 复制带随机指针的链表
class Solution 
{
public:
    Node* copyRandomList(Node* head) 
    {
        // 保存“原节点地址 → 对应的新节点地址”
        map<Node*, Node*> nodeMap;

        // copyhead 指向复制链表的头，copytail 指向复制链表的尾
        Node* copyhead = nullptr;
        Node* copytail = nullptr;

        // cur 用来遍历原链表
        Node* cur = head;

        // 第一遍：复制每个节点，并连接复制节点的 next
        while (cur != nullptr) {
            if (copytail == nullptr) {
                // 第一个节点：创建复制链表的头节点
                copyhead = copytail = new Node(cur->val);
            } else {
                // 其他节点：创建新节点，接到复制链表尾部
                copytail->next = new Node(cur->val);

                // 尾指针移动到刚创建的新节点
                copytail = copytail->next;
            }

            // 记录当前原节点对应哪个复制节点
            // 例如：原节点 A 对应复制节点 A'
            nodeMap[cur] = copytail;

            // cur 沿原链表前进
            cur = cur->next;
        }

        // 第二遍：根据原节点的 random，设置复制节点的 random
        cur = head;          // 重新从原链表头开始
        Node* copy = copyhead; // 同时从复制链表头开始

        while (cur != nullptr) {
            if (cur->random == nullptr) {
                // 原节点的 random 为空，复制节点的 random 也设为空
                copy->random = nullptr;
            } else {
                // 找出原节点 random 指向的节点所对应的复制节点
                copy->random = nodeMap[cur->random];
            }

            // 两个指针分别沿各自链表前进
            cur = cur->next;
            copy = copy->next;
        }

        // 返回复制链表的头节点
        return copyhead;
    }
};

//前k个高频单词

class Solution 
{
public:
    // 排序比较规则：按 pair 中的次数从大到小排
    struct kvGreater 
    {
        bool operator()(const pair<string, int>& kv1,const pair<string, int>& kv2) const 
        {
            return kv1.second > kv2.second;
        }
    };

    vector<string> topKFrequent(vector<string>& words, int k) 
    {
        // 统计每个单词出现的次数
        map<string, int> countMap;
        for (auto& str : words) 
        {
            countMap[str]++;
        }

        // 把 map 中的“单词、次数”复制到 vector，方便排序
        vector<pair<string, int>> v(countMap.begin(), countMap.end());

        // 按出现次数从高到低排序
        // 次数相同时，stable_sort 保留原来的顺序  
        stable_sort(v.begin(), v.end(), kvGreater());

        // 取排序后的前 k 个单词
        vector<string> ret;
        for (int i = 0; i < k; i++) 
        {
            ret.push_back(v[i].first);
        }

        return ret;
    }
};



int main()
{
    //test_set1();
    //test_set2();
    //test_set3();
    // test_map1();
    // test_map2();
    // test_map3();

    test_map4();
    return 0;
}
