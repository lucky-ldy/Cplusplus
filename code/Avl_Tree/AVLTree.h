//AVL树是最先发明的⾃平衡⼆叉查找树，AVL是⼀颗空树，或者具备下列性质的⼆叉搜索树
//它的左右⼦树都是AVL树，且左右⼦树的⾼度差的绝对值不超过1。
//|右子树高度 - 左子树高度| <= 1 

//更新规则：
//平衡因⼦ = 右⼦树⾼度-左⼦树⾼度
//只有⼦树⾼度变化才会影响当前结点平衡因⼦。

//插⼊结点，会增加⾼度
//所以新增结点在parent的右⼦树，parent的平衡因⼦++，
//  新增结点在parent的左⼦树，parent平衡因⼦--
 

//更新停止条件

//更新后parent的平衡因⼦等于0，更新中parent的平衡因⼦变化为-1->0 或者 1->0，
//说明更新前parent⼦树⼀边⾼⼀边低，不会影响parent的平衡因⼦。

//更新后parent的平衡因⼦等于1 或 -1，更新前更新中parent的平衡因⼦变化为0->1 或者 0->-1，
//说明更新前parent⼦树两边⼀样⾼

//更新后parent的平衡因⼦等于2 或 -2，更新前更新中parent的平衡因⼦变化为1->2 或者 -1->-2，
//说明更新前parent⼦树⼀边⾼⼀边低 需要通过旋转来调整平衡因⼦。


#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

template<class K, class V>
struct AVLTreeNode 
{
	// 需要parent指针，后续更新平衡因子可以看到
	pair<K, V> _kv;
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	int _bf; // balance factor 平衡因子

	AVLTreeNode(const pair<K, V>& kv)
		:_kv(kv)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _bf(0)
	{}
};

template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;

public:
    AVLTree()
    {
        _root = nullptr;
    }

    bool Insert(const pair<K, V>& kv);
    {   
        if (_root == nullptr)
        {
            _root = new Node(kv);
            return true;
        }

        Node* parent = nullptr; 
        Node* cur = _root;
        while (cur != nullptr)
        {
            if (key < cur->_key)
            {
                parent = cur;
                cur = cur->_left;
            }

            else if (key > cur->_key)
            {
                parent = cur;
                cur = cur->_right;
            }
            else
            {
                return false;
            }

            cur = new TreeNode(key, value);
            if(parent->_key > key)
            {
                parent->_left = cur;
            }
            else
            {
                parent->_right = cur;
            }

            cur->_parent = parent;

            //更新平衡因子
            while(cur)
            {
                if(cur == parent -> _left)
                {
                    parent -> _bf --;
                }
                else
                {   
                    parent -> _bf ++;
                }

                if(parent -> _bf == 0)
                {
                    break;
                }

                else if(parent -> _bf == 1 || parent -> _bf == -1)
                {
                    //继续往上更新平衡因子
                    cur = parent;
                    parent = parent -> _parent;
                }

                else if(parent -> _bf == 2 || parent -> _bf == -2)
                {
                    //需要通过旋转来调整平衡因子
                    break;
                }
                
                else
                {
                    assert(false);
                    break;
                }
            }

        }
            return true;
    }


private:
    Node* _root = nullptr;

};