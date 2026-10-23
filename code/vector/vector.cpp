//一、vector 介绍
//vector 是 C++ 标准库提供的动态数组，用来存放一组相同类型的数据。
//普通数组的长度确定后不能改变，vector 可以随着元素的添加自动扩容。
//例如：保存学生成绩时，人数不确定，就可以用 vector<int> 存储。
//string 主要用来存字符，vector 可以存 int、double、string、自定义类等类型的对象。

//基本特点：
//1. 元素连续存储，可以像数组一样通过下标访问，下标从 0 开始。
//2. 尾部添加、删除元素比较方便；在中间插入、删除通常需要移动后面的元素。
//3. 容量不够时会申请更大的空间，将原有元素搬过去，再释放旧空间。
//4. 自动管理存储空间，不需要自己手动 new 和 delete。

//使用时需要包含头文件：#include <vector>
//例如：std::vector<int> v; 表示创建一个空的整型动态数组。
//v.push_back(10); 向末尾添加元素 10，此时 v[0] 是 10。
//v.size() 表示当前元素个数，v.capacity() 表示当前容量能容纳多少个元素。

#include <iostream>
#include <vector>
using namespace std;

void test_vector1()
{
    vector<int> v2(10 , 1);//创建一个10个元素的动态数组 每个元素都是1
    vector<int> v3(v2);//拷贝构造函数
    vector<char> v4;//string s4 结尾有\0 接口跟串相关的函数

    for(size_t i = 0; i < v2.size(); i++)
    {
        cout << v2[i] << " ";
    }
    cout << endl;

    //迭代器遍历vector
    vector<int>::iterator it = v2.begin();
    while(it != v2.end())
    {

        cout << *it << " ";
        it++;

    }
    cout << endl;

    //范围for遍历vector
    for(auto x : v2)
    {
        cout << x << " ";
    }

    cout << endl;

    //insert插入
    v2.insert(v2.begin() , 0);//头插
    for (auto x : v2)
    {
        cout << x << " ";
    }
    cout << endl;

    v2.insert(v2.begin() + 5 , 0 );//在第5个元素位置插入0
    for(auto x : v2)
    {
        cout << x << " ";
    }
    cout << endl;

    //erase删除
    v2.erase(v2.begin());//头删
    for(auto x : v2)
    {
        cout << x << " ";
    }
    cout << endl;

    v2.erase(v2.begin() , v2.begin() + 5);//删除0 - 4位置
    for(auto x : v2)
    {
        cout << x << " ";
    }
    cout << endl;

    vector<int> v1;
    // v1.reserve(3); 错误的 因为size 还是 0  这只是给capacity 申请了3个元素的空间
    v1.resize(3);//给v1 申请3个元素的空间
    //输入数据
    for(size_t i = 0; i < 3; i++)
    {
        cin >> v1[i];
    }
    cout << endl;

    for(auto x : v1)
    {
        cout << x << " ";
    }
    cout << endl;

}

void test_vector2()
{
    vector<string> v1;
    v1.push_back("hello");
    v1.push_back("world");
    //拷贝遍历vector
    for(const auto& x : v1)
    {
        cout << x << " ";
    }
    cout << endl;

    v1[0] = "ldy";//修改第一个元素
    v1[1][0] = 'q';//修改第二个元素的第一个字符
    //等价于 v1.operator[](1).operator[](0);
    
    for(const auto& x : v1)
    {
        cout << x << " ";
    }
    cout << endl;
}

void test_vector3()
{
    //二维vector
    //例如：存储一个矩阵
    vector<vector<int>> v1(3);
        //3 x 5 数组 一个大数组 里面套着3个小数组 每个小数组有5个元素 每个元素都是1
        //或者对每个小数组进行初始化
        v1[0].resize(5 , 1);
        v1[1].resize(5 , 2);
        v1[2].resize(5 , 3);
        cout << v1[0][1] << " ";
        cout << v1.operator[](0).operator[](1) << endl;
        // cout << v1[0] << endl;
        // cout << v1[1] << endl;
        // cout << v1[2] << endl;
        
        for(auto& x : v1)
        {
            cout << x[1] << endl; // 输出每一行的第二个元素，即第二列
        }
        cout << endl;
        //遍历二维vector
        for(size_t i = 0; i < v1.size(); i++)
        {
            for(size_t j = 0; j < v1[i].size(); j++)
            {
                cout << v1[i][j] << " ";
            }
            cout << endl;
        }

}


int main()
{
    // test_vector1();
    test_vector2();
    test_vector3();
    return 0;


}

//二、杨辉三角OJ(体现C++中vector的应用场景)
// 输入: numRows = 5
// 输出: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]

class Solution 
{
public:
    vector<vector<int>> generate(int numRows) 
    {
        vector<vector<int>> res(numRows);  
        for(size_t i = 0; i < numRows; i++)
        {
            res[i].resize(i + 1 , 1);
        }
        //第一行第二行都是1
        for(size_t i = 2; i < res.size(); i++)
        {
            //每一行的第一个和最后一个都是1
            for(size_t j = 1; j < res[i].size() - 1; j++)
            {
                res[i][j] = res[i - 1][j - 1] + res[i - 1][j];

            }

        }
        return res;
    }
};
