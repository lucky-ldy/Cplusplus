//大学是人生的暑假！！      

//vector 的底层实现

#include "vector.h"
#include <iostream>
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

int main()
{
    //test_vector1();
    //test_vector2();
    test_vector3();
    return 0;
}