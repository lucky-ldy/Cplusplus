//迭代器功能分类角度
//均支持：* != ==
//单向迭代器：支持++    (forward list)
//双向迭代器：支持++ --  （list)
//随机迭代器：支持+ - ，++ -- （vector string)
#include "List.h"
#include<iostream>
#include<list>
#include<algorithm>
#include<forward_list>

using namespace std;

void print_list(list<int> lt1)
{
    for(auto &x : lt1)
    {
        cout << x << " ";
    }
    cout << endl;
}

void test_list1()
{  
    list<int> lt1(5, 1);
    list<int> lt2(5, 2);
    lt2.push_back(3);
    lt2.push_front(0);
    //会在指定位置之前创建一个元素
    lt2.emplace(lt2.begin(), 100);

    list<int>::iterator it1 = lt2.begin();
    while(it1 != lt2.end())
    {
        cout << *it1 << " ";
        it1++;
    }
    cout << endl;

    for(auto &x : lt1)
    {
        cout << x << " ";
    }
    cout << endl;

    list<int> lt3(lt1);
    for(auto &x : lt3)
    {
        cout << x << " ";
    }
    cout << endl;

    list<int> lt4 = {1 , 2 , 3 , 4 ,5};
    for(auto &x : lt4)
    {
        cout << x << " ";
    }
    cout << endl;
}

void test_list2()
{
    list<int> lt1;
    lt1.push_back(3);
    lt1.push_back(3);  
    lt1.push_back(0);  
    lt1.push_back(4);
    lt1.push_back(6);    
    for(auto &x : lt1)
    {
        cout << x << " ";
    }
    cout << endl;
    
    //list的迭代器不支持加法运算
    //lt1.insert(lt1.begin() + 3, 100);
    lt1.insert(lt1.begin()++, 100);
    for(auto &x : lt1)
    {
        cout << x << " ";
    }
    cout << endl;

    //那如果我们想要在n位置上插入一个元素 我们需要先找到n位置的迭代器 然后再插入元素
    auto it = lt1.begin();
    int n = 3;
    while(n--)
    {
        it++;
    }
    lt1.insert(it, 15);
    for(auto &x : lt1)
    {
        cout << x << " ";
    }
    cout << endl;
    //要包含头文件algorithm
    lt1.reverse();
    for(auto &x : lt1)  
    {
        cout << x << " ";
    }
    cout << endl;
    
    //单向迭代器不支持逆置操作
    //forward_list<int> flt = {1, 2, 3, 4, 5};
    // reverse(flt.begin(), flt.end());//不支持单向迭代器
    // sort(flt.begin(), flt.end());//不支持随机迭代器

    auto it2 = find(lt1.begin(), lt1.end(), 3);
    if(it2 != lt1.end())
    {
        cout << "找到" << endl;
        cout << *it2 << endl;
        lt1.erase(it2);
    }
    else
    {
        cout << "未找到" << endl;
    }
}

bool single_digit(const int& value)
{
    return (value %2 == 0); //remove_if 删除所有满足条件的结点
}

void test_list3()
{
    list<int> lt1;
    lt1.push_back(1);
    lt1.push_back(2);  
    lt1.push_back(3);  
    lt1.push_back(4);
    lt1.push_back(5);    
    
    print_list(lt1);

    //把4结点转移到头部
    auto it2 = find(lt1.begin(), lt1.end(), 4);
    if(it2 != lt1.end())
    {
        cout << *it2 << endl;
        //第一个参数是目标位置 第二个参数是源列表 第三个参数是要转移的结点
        lt1.splice(lt1.begin(), lt1, it2);
        print_list(lt1);
    }
    else
    {
        cout << "未找到" << endl;
    }
    //删除所有值为3的结点
    lt1.remove(3);
    //设置条件进行删除
    lt1.remove_if(single_digit);
    print_list(lt1);
}

void test_list4()
{
    list<int> lt1 = {1 , 2 , 3 , 3 ,  4 , 5 , 6 };
    //去重 前提是有序的 会删除所有重复的结点
    lt1.unique();
    print_list(lt1);

    list<int> lt2 = {1 , 4 , 3 , 3 , 5 , 8 , 7 , 4 , 5 , 6 };
    lt2.sort();//排序
    print_list(lt2);
    //去重 前提是有序的 会删除所有重复的结点
    lt2.unique();
    print_list(lt2);

}

void test_ldylist1()
{
    ldy::list<int> lt1;
    lt1.push_back(1);
    lt1.push_back(2);  
    lt1.push_back(3);  
    lt1.push_back(4);
    lt1.push_back(5);    
  
    ldy::list_iterator<int> it1 = lt1.begin();
    while(it1 != lt1.end()) 
    {
        cout << *it1 << " ";
        it1++;
    }
    cout << endl;

}


void test_ldylist2()
{
    ldy::list<int> lt1;
    lt1.push_back(1);
    lt1.push_back(2);  
    lt1.push_back(3);  
    lt1.push_back(4);
    lt1.push_back(5);  

    lt1.push_front(0); 
    lt1.push_front(-1);
    lt1.print_ldylist(lt1);
}

void test_ldylist3()
{
    ldy::list<int> lt1;
    lt1.push_back(1);
    lt1.push_back(2);  
    lt1.push_back(3);  
    lt1.push_back(4);
    lt1.push_back(5);  
    lt1.print_ldylist(lt1);

    ldy::list<int> lt2(lt1);
    lt2.print_ldylist(lt2);

    //要用initializer_list初始化
    ldy::list<int> lt3 = {10 , 20 , 30 , 40 , 50};
    ldy::list<int>::iterator it1 = lt3.begin();
    lt3.print_ldylist(lt3);
    //浅拷贝 析构的时候崩溃了 要改成深拷贝
    lt2 = lt3;
    lt2.print_ldylist(lt2);

    const ldy::list<int> lt4 = {10 , 20 , 30 , 40 , 50};
    ldy::list<int>::const_iterator it2 = lt4.begin();
    while(it2 != lt4.end())
    {
        cout << *it2 << " ";
        ++it2;
    }
    cout << endl;

}

int main()
{
    //test_list1();
    //test_list2();
    //test_list3();
    //test_list4();
    //test_ldylist1();
    //test_ldylist2();
    test_ldylist3();




}
