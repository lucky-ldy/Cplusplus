//一、红黑树的概念
//红⿊树是⼀棵⼆叉搜索树，
//他的每个结点增加⼀个存储位来表⽰结点的颜⾊，可以是红⾊或者⿊⾊。

//二、红黑树的规则
// 1. 每个结点不是红⾊就是⿊⾊
// 2. 根结点是⿊⾊的
// 3. 如果⼀个结点是红⾊的，则它的两个孩⼦结点必须是⿊⾊的，
// 也就是说任意⼀条路径不会有连续的 红⾊结点。
// 4. 对于任意⼀个结点，从该结点到其所有NULL结点的简单路径上，均包含相同数量的⿊⾊结点 

//三、红黑树最长路径不会超过最短路径的2倍

//由规则4可知，从根到NULL结点的每条路径都有相同数量的⿊⾊结点，
//所以极端场景下，最短路径就就是全是⿊⾊结点的路径，假设最短路径⻓度为bh(black height)

//由规则2和规则3可知，任意⼀条路径不会有连续的红⾊结点，
//所以极端场景下，最⻓的路径就是⼀⿊⼀红间隔组成，那么最⻓路径的⻓度为2*bh

//所以红黑树 假设任意⼀条从根到NULL结点路径的⻓度为x，那么bh <= h <= 2*bh。

//四、红黑树的效率
//假设N是红黑树的结点数 h最短路径的⻓度，那么 2^h - 1 <= N <= 2^(h+1) - 1
//由此推出 h <= log2(N+1)
//意味着红⿊树增删查改最坏也就是⾛最⻓路径 2*logN ，那么时间复杂度还是O(logN)


//五、红黑树的插入

//情况1：变色
//c（现在插入）为红，p（父亲）为红，g（祖父）为⿊，u（叔叔）存在且为红，则将p（父亲）和u（叔叔）变⿊，g（祖父）变红。
//在把g（祖父）当做新的c（现在插入）后，插入完成，不需要往上更新。


//情况2：单旋 + 变色
// c（现在插入）为红，p（父亲）为红，g（祖父）为黑，u（叔叔）不存在或者u存在且为黑。
// ① u不存在 → c一定是新增结点。
// ② u存在且为黑 → c一定不是新增结点：c之前是黑色的，是在c的子树中插入后，
//    子树里先符合情况1，变色把子树的根从黑色变成红色，再往上更新到c这里来的。
//    （如果c是新增的红结点，插入前p的c侧是NULL，黑高为1；而u侧有黑结点u，黑高至少为2，
//      两边黑高本来就不相等，矛盾，所以c只能是情况1更新上来的。）
//
// 此时p和c在同一侧，是一条直线：
// 2.1 LL型：p是g的左孩子，c是p的左孩子 → 对g右单旋。
//     旋转后p升到g原来的位置，然后p变黑、g变红，c保持红。
// 2.2 RR型：p是g的右孩子，c是p的右孩子 → 对g左单旋。
//     旋转后p升到g原来的位置，然后p变黑、g变红，c保持红。
//
// 为什么这样变色：
// p顶替了原来g的位置，g原来是黑的，为了让这条路径上的黑结点数量不变，p必须变黑；
// c是红结点，要求父亲是黑，p变黑后红红冲突就解决了，所以c保持红；
// g被压到下面后变红，它的两个孩子（p原来的另一棵子树和u）一定都是黑的，不会红红相连。
// 旋转 + 变色后，这棵子树的新根p是黑色的，上面不会再有红红冲突，不用继续往上更新，插入结束。
//
// 如果p和c不在同一侧（折线型：LR或RL），单旋解决不了，要先转成直线型再单旋，即情况3的双旋。


//情况3：双旋 + 变色
// c（现在插入）为红，p（父亲）为红，g（祖父）为黑，u（叔叔）不存在或者u存在且为黑。
// u的判断和原因与情况2完全相同，这里不重复。
//
// 此时p和c不在同一侧，是折线形：
// 3.1 LR型：p是g的左孩子，c是p的右孩子 → 先对p左单旋，再对g右单旋。
// 3.2 RL型：p是g的右孩子，c是p的左孩子 → 先对p右单旋，再对g左单旋。
//
// 双旋之后，c升到原来g的位置：把c变黑、g变红，p保持红。
// （p保持红是安全的：p的两个孩子、g的两个孩子都是黑结点，不会出现红红相连。）
//
// 为什么必须双旋，不能像情况2那样只旋一次：
// 折线型直接对g单旋，红红虽然会消失，但黑高会变得一边多一边少，违反规则4。
// 所以第一次单旋不是对g做，而是对p做，作用是"把折线摆直"：
//   LR型对p左单旋后，c升到p的位置，p变成c的孩子，g-c-p连成一条直线；
//   此时的问题形状和情况2完全一样（只是"p、c"的角色换成了c、p），按情况2处理即可。
// 第二次旋转就是情况2的做法：对g旋转，让升到g位置的结点变黑，g变红。
//
// 一句记忆：谁最后坐上g的位置，谁就变黑，g被压下去一律变红。
// 情况2坐上g位置的是p，所以p变黑；情况3坐上g位置的是c，所以c变黑。
// 双旋后子树的新根c是黑色的，上面不会再有红红冲突，不用继续往上更新，插入结束。


#pragma once
#include<iostream>
#include<utility>
using namespace std;

// 枚举值表示颜色
enum Colour 
{
	RED,
	BLACK
};

// Red Black
// 这里我们默认按key/value结构实现

template<class K, class V>
struct RBTreeNode
{
	// 这里更新控制平衡也要加入parent指针
	pair<K, V> _kv;
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	Colour _col;
	RBTreeNode(const pair<K, V>& kv)
		:_kv(kv)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
	{}
};

template<class K, class V>
class RBTree
{
    typedef RBTreeNode<K, V> Node;

private:
     //右单旋（RR）：P 的右子树的右边过高，以右孩子 R 为新根
    void RotateR(Node* parent)
    {
        Node* subLeft = parent->_left;
        Node* subLeftRight = subLeft->_right;
        Node* parentParent = parent->_parent;

        parent->_left = subLeftRight;
        if(subLeftRight)
        {
            subLeftRight->_parent = parent;
        }
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
        Node* parentParent = parent->_parent;

        parent->_right = subRightLeft;
        if(subRightLeft)
        {
            subRightLeft->_parent = parent;
        }
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
    }

    //中序遍历 递归实现
    void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_kv.first << " ";
		_InOrder(root->_right);
	}
    //计算树的高度
    int _Height(Node* root)
	{
		if (root == nullptr)
			return 0;
		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);
		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
	}

    //计算树的结点数
   	int _Size(Node* root)
	{
		if (root == nullptr)
			return 0;

		return _Size(root->_left) + _Size(root->_right) + 1;
	}

    //红黑树性质检测：根黑、无连续红结点、各路径黑结点数相等
    bool _CheckRBTree(Node* root, int blackNum, int& refBlackNum)
    {
        if (root == nullptr)
        {
            //第一条到达空结点的路径，记录它的黑结点数作为基准
            if (refBlackNum == -1)
            {
                refBlackNum = blackNum;
                return true;
            }
            //规则4：每条路径的黑结点数量必须相等
            if (blackNum != refBlackNum)
            {
                cout << "路径黑结点数量不相等" << endl;
                return false;
            }
            return true;
        }

        //规则3：红结点的孩子必须是黑色
        if (root->_col == RED && root->_parent && root->_parent->_col == RED)
        {
            cout << root->_kv.first << "出现连续红结点" << endl;
            return false;
        }

        if (root->_col == BLACK)
        {
            ++blackNum;
        }

        return _CheckRBTree(root->_left, blackNum, refBlackNum)
            && _CheckRBTree(root->_right, blackNum, refBlackNum);
    }

public:
    //外部调用函数接口

    void InOrder()
    {
        _InOrder(_root);
        cout << endl;
    }

    size_t Height() 
    {
		return _Height(_root);
	}

	size_t Size() 
    {
		return _Size(_root);
	}

    //检测是否为红黑树
    //红黑树的验证
    //1.根结点必须是黑色
    //2.反过来检查⽗亲的颜⾊ 是否有连续的红色结点
    //3.检查每条路径的黑结点数量是否相等
    bool IsBalanceTree() 
    {
        //规则2：根结点必须是黑色
        if (_root && _root->_col == RED)
        {
            cout << "根结点不是黑色" << endl;
            return false;
        }

        int refBlackNum = -1;
        return _CheckRBTree(_root, 0, refBlackNum);
    }
    
    bool Insert(const pair<K, V>& kv)
    {   
        if (_root == nullptr)
        {
            _root = new Node(kv);
            _root->_col = BLACK;
            return true;
        }

        Node* parent = nullptr; 
        Node* cur = _root;
        while (cur != nullptr)
        {
            if (kv.first < cur->_kv.first)
            {
                parent = cur;
                cur = cur->_left;
            }

            else if (kv.first > cur->_kv.first)
            {
                parent = cur;
                cur = cur->_right;
            }
            else
            {
                return false;
            }
        }

        cur = new Node(kv);
        cur->_col = RED;
        if(parent->_kv.first > kv.first)
        {
            parent->_left = cur;
        }
        else
        {
            parent->_right = cur;
        }

        cur->_parent = parent;
        
        //只有父亲为红色时才需要向上更新
        while(parent && parent->_col == RED)
        {
            Node* grandfather = parent->_parent;
            //父亲是祖父的左子树
            if(parent == grandfather->_left)
            {
                Node* uncle = grandfather->_right;
                //叔叔存在且为红色
                if(uncle && uncle->_col == RED)
                {
                    //情况1：变色 继续向上更新
                    //父亲和叔叔变黑 爷爷变红 然后继续向上处理
                    uncle->_col = BLACK;
                    parent->_col = BLACK;
                    grandfather->_col = RED;
                    cur = grandfather;
                    parent = cur->_parent;
                }
                //叔叔不存在 或 叔叔存在且为黑色
                else
                {
                    if(cur == parent->_left)
                    {
                        //情况2：单旋 + 变色
                        //祖父结点右单旋 父亲结点变黑
                        RotateR(grandfather);
                        parent->_col = BLACK;
                        grandfather->_col = RED;
                    }
                    else
                    {
                        //情况3：双旋 + 变色
                        //先对父亲左单旋 再对祖父结点右单旋
                        RotateL(parent);
                        RotateR(grandfather);
                        cur->_col = BLACK;
                        grandfather->_col = RED;
                    }
                    //旋转后新根为黑色，红红冲突已消除，结束
                    break;
                }
            }
            //父亲是祖父的右子树
            else
            {
                Node* uncle = grandfather->_left;
                //叔叔存在且为红，变色即可
                if(uncle && uncle->_col == RED)
                {
                    parent->_col = uncle->_col = BLACK;
                    grandfather->_col = RED;
                    //继续往上处理
                    cur = grandfather;
                    parent = cur->_parent;
                }
                else //叔叔不存在，或者存在且为黑
                {
                    if(cur == parent->_right)
                    {
                        //情况2：单旋 + 变色
                        RotateL(grandfather);
                        parent->_col = BLACK;
                        grandfather->_col = RED;
                    }
                    else
                    {
                        //情况3：双旋 + 变色
                        RotateR(parent);
                        RotateL(grandfather);
                        cur->_col = BLACK;
                        grandfather->_col = RED;
                    }
                    break;
                }
            }
        }

        //规则2：根结点永远是黑色（情况1可能把根结点改成红色）
        _root->_col = BLACK;
        return true;
    }

    Node* Find(const K& key) 
    {
		Node* cur = _root;
		while (cur) 
        {
			if (cur->_kv.first < key) 
            {
				cur = cur->_right;
			}
			else if (cur->_kv.first > key) 
            {
				cur = cur->_left;
			}
			else 
            {
				return cur;
			}
		}

		return nullptr;
	}

private:
    Node* _root = nullptr;

};