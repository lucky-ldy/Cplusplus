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

private:

    //右单旋（RR）：P 的右子树的右边过高，以右孩子 R 为新根
    void RotateR(Node* parent)
    {
        Node* subLeft = parent->_left;
        Node* subLeftRight = subLeft->_right;
        Node* parentParent = parent->_parent;

        parent->_left = subLeftRight;
        subLeft->_right = parent;
        parent->_parent = subLeft;
        
        //如果parent是根结点，需要更新根结点为subLeft，subLeft的parent指针指向nullptr
        if(parent == _root)
        {
            _root = subLeft;
            subLeft->_parent = nullptr;
        }
        //如果parent不是根结点，需要更新parent的parent指针指向subLeft
        else
        {
            if(parent == parentParent->_left)
            {
                parentParent->_left = subLeft;
            }

            else
            {
                parentParent->_right = subLeft;
            }
            
            subLeft->_parent = parentParent;
        }
    }
    
    //左单旋
    void RotateL(Node* parent)
    {
        Node* subRight = parent->_right;
        Node* subRightLeft = subRight->_left;
        parent->_right = subRightLeft;
        subRight->_left = parent;
        parent->_parent = subRight;

        //如果parent是根结点，需要更新根结点为subRight，subRight的parent指针指向nullptr
        if(parent == _root)
        {
            _root = subRight;
            subRight->_parent = nullptr;
        }
        //如果parent不是根结点，需要更新parent的parent指针指向subRight
        else
        {
            if(parent == parentParent->_left)
            {
                parentParent->_left = subRight;
            }
            else
            {
                parentParent->_right = subRight;
            }
            subRight->_parent = parentParent;
        }
        parent->_bf = subRight->_bf = 0;
    }

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

//旋转时都要重接新子树的父结点；如果旋转的子树原来是整棵树，还要更新 _root。旋转后需更新受影响结点的父指针和平衡因子。
//四种失衡分别是：LL 用右单旋，RR 用左单旋，LR 用左右双旋，RL 用右左双旋。

//左单旋（RR）：P 的右子树的右边过高，以右孩子 R 为新根。
// 1. 暂存 R 的左子树 b，把 b 改接为 P 的右子树。
// 2. 把 P 改接为 R 的左孩子；R 接替 P 原来的位置。

//右单旋（LL）：P 的左子树的左边过高，以左孩子 L 为新根。
// 1. 暂存 L 的右子树 b，把 b 改接为 P 的左子树。
// 2. 把 P 改接为 L 的右孩子；L 接替 P 原来的位置。

//左右双旋（LR）：P 的左子树 L 的右子树 M 过高。
// 1. 先对 L 做左单旋：M 升到 L 的位置，L 成为 M 的左孩子；M 的左子树改接到 L 的右边。
// 2. 再对 P 做右单旋：M 成为这棵子树的新根，P 成为 M 的右孩子；M 的右子树改接到 P 的左边。

//右左双旋（RL）：P 的右子树 R 的左子树 M 过高。
// 1. 先对 R 做右单旋：M 升到 R 的位置，R 成为 M 的右孩子；M 的右子树改接到 R 的左边。
// 2. 再对 P 做左单旋：M 成为这棵子树的新根，P 成为 M 的左孩子；M 的左子树改接到 P 的右边。

