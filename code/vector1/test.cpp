//大学是人生的暑假！！      

//vector 的底层实现

#include "vector.h"
#include <iostream>
#include <string>
using namespace std;
#include <vector>

void test_vector1()
{
    ldy::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    for(auto& x : v)
    {
        cout << x << " ";
    }
    cout << endl;

    for(size_t i = 0; i < v.size(); i++)
    {
        v[i]++;
        cout << v[i] << " ";
    }
    cout << endl;
    
    v.pop_back();
    v.pop_back();
    for(auto& x : v)
    {
        cout << x << " ";
    }
    cout << endl;
    // cout << v.size() << endl;
    // cout << v.capacity() << endl;   
}

void test_vector2()
{
    ldy::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    for(auto& x : v)
    {
        cout << x << " ";
    }
    cout << endl;

    v.insert(v.begin(), 0);
    v.insert(v.begin() + 2, 8);

    for(auto& x : v)
    {
        cout << x << " ";
    }
    cout << endl;
}

void test_vector3()
{
    ldy::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    for(auto& x : v)
    {
        cout << x << " ";
    }
    cout << endl;

    v.erase(v.begin());
    v.erase(v.begin() + 2);

    for(auto& x : v)
    {
        cout << x << " ";
    }
    cout << endl;

    ldy::vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(2);
    v1.push_back(4);
    v1.push_back(5);
    v1.push_back(6);
    v1.push_back(7);
    v1.push_back(8);
    for(auto& x : v1)
    {
        cout << x << " ";
    }
    cout << endl;
    //删除所有偶数
    ldy::vector<int>::iterator it = v1.begin();
    while(it != v1.end())
    {
        if(*it % 2 == 0)    
        {
            v1.erase(it);
            //it = v1.erase(it); 在标准库 erase之后it就失效了 所以要更新it 为下一个位置
        }
        else
        {
            it++;
        }
    }

    for(auto& x : v1)
    {
        cout << x << " ";
    }
    cout << endl;

}

void test_vector4()
{
    ldy::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);

    cout << v.size() << endl;
    cout << v.capacity() << endl;
    //保留前五个
    v.resize(5 , 1);

    for(auto& x : v)
    {
        cout << x << " ";
    }
    cout << endl;
    cout << v.size() << endl;
    cout << v.capacity() << endl;

    v.resize(10 , 1);

    for(auto& x : v)
    {
        cout << x << " ";
    }
    cout << endl;
    cout << v.size() << endl;
    cout << v.capacity() << endl;
}

void test_vector5()
{
    //这会匹配到迭代器区间构造 因为都是传两个参数 类型匹配错误了
    ldy::vector<int> v(5, 1);
    for(auto& x : v)
    {
        cout << x << " ";
    }
    cout << endl;

    //std::vector<int> v2{1, 2, 3, 4, 5};
    std::vector<int> v2 = {1,2,3,4,5};
    for (auto i : v2)
    {
        cout << i << " ";
    }
    cout << endl;

    //写了vector initializer_list 构造函数
    ldy::vector<int> v3{2, 2, 3, 3, 5};
    for (auto i : v3)
    {
        cout << i << " ";
    }
    cout << endl;

    //迭代器区间的插入
    ldy::vector<int> v4(v3.begin()+1, v3.end()-1);
    for (auto i : v4)
    {
        cout << i << " ";
    }
    cout << endl;
    //拷贝构造
    ldy::vector<int> v5(v);
    print(v5);
    //赋值运算
    ldy::vector<int> v6 = v3;
    print(v6);
    
}

void test_vector6()
{
    //这样拷贝发现输出是错误的 因为原来的逻辑是memcpy是浅拷贝 所以会导致野指针
    //改成深拷贝对于 string 类型 就各自的空间了 不会共享内存
    ldy::vector<std::string> v;
    v.push_back("11111111111111");
    v.push_back("111111111111");
    v.push_back("111111111111111");
    v.push_back("111111111111111");
    print(v);
}


int main()
{
    //test_vector1();
    //test_vector2();
    //test_vector3();
    //test_vector4();
    //test_vector5();
    test_vector6();

    //内置类型也有构造
    int i = int();
    int j = int(1);
    return 0;
}
