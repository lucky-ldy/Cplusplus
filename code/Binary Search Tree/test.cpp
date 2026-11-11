// 一. 二叉搜索树的概念
// 二叉搜索树又称二叉排序树，它或者是一棵空树，或者是具有以下性质的二叉树:
// ? 若它的左子树不为空，则左子树上所有结点的值都小于等于根结点的值
// ? 若它的右子树不为空，则右子树上所有结点的值都大于等于根结点的值
// ? 它的左右子树也分别为二叉搜索树



// 二. 二叉搜索树的性能分析
// 最优情况下，二叉搜索树为完全二叉树(或者接近完全二叉树)，其高度为： log2 N
// 最差情况下，二叉搜索树退化为单支树(或者类似单支)，其高度为： N
// 所以综合而言二叉搜索树增删查改时间复杂度为： O(N)


// 三、二叉搜索树的插入
// 1. 树为空，则直接新增结点，赋值给root指针
// 2. 树不空，按二叉搜索树性质，插入值比当前结点大往右走，
// 插入值比当前结点小往左走，找到空位置，插入新结点。
// 3. 如果支持插入相等的值，插入值跟当前结点相等的值
// 可以往右走，也可以往左走，找到空位置，插入新结点。

#include"BinarySearchTree.h"


int main()
{
//key 场景

    // key::BinarySearchTree<int> t;
	// int a[] = { 8, 3, 1, 10, 1, 6, 4, 7, 14, 13 };
	// for(auto e : a)
    // {
    //     t.Insert(e);
    // }
    // t.InOrder();
    
    // //左右都不为空的场景
    // t.Erase(3);
    // t.InOrder();

    // t.Erase(8);
    // t.InOrder();

    // //左子树不为空右子树为空的场景
    // t.Erase(14);
    // t.InOrder();

    // //右子树不为空左子树为空的场景
    // t.Erase(6);
    // t.InOrder();

    // for(auto e : a)
    // {
    //     t.Erase(e);
    // }
    // t.InOrder();
     

//  keyvalue 场景
//  1.中英文 互译查找

    keyvalue::BinarySearchTree<string, string> dict;
    //BinarySearchTreeNode<string, string> copy = dict;
    dict.Insert("left", "左边");
    dict.Insert("right", "右边");
    dict.Insert("insert", "插入");
    dict.Insert("string", "字符串");

    //输入单词进行查找
    string str;
    while (cin >> str)//cin >> 可以一直输入 用ctrl Z + 换行结束
    {
        auto ret = dict.Find(str);
        
        if (ret)
        {
            cout << "->" << ret->_value << endl;//找到了返回单词对应的中文
        }

        else
        {
            cout << "无此单词，请重新输入" << endl;
        }
}

//  2. 水果查找

    string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉" };
    keyvalue::BinarySearchTree<string, int> countTree; //key 为 string  value 为 int
    for (const auto& str : arr)
    {
        // 先查找?果在不在搜索树中
        // 1、不在，说明?果第?次出现，则插?<?果, 1>
        // 2、在，则查找到的结点中?果对应的次数++
        //BSTreeNode<string, int>* ret = countTree.Find(str);
        auto ret = countTree.Find(str);
        if (ret == NULL)
        {
            countTree.Insert(str, 1); // 插?<?果, 1>
        }

        else
        {
            ret->_value++;
        }

    }

     countTree.InOrder();

    return 0;

}
