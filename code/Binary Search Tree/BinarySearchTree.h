#pragma once
#include <iostream>
using namespace std;


//key二叉搜索树
namespace key
{
template<class K>

struct BinarySearchTreeNode
{
    K _key;
    BinarySearchTreeNode<K>* _left;
    BinarySearchTreeNode<K>* _right;

    BinarySearchTreeNode(const K& key)
        : _key(key)
        , _left(nullptr)
        , _right(nullptr)
    {

    }
};

template<class K>
class BinarySearchTree
{
    typedef BinarySearchTreeNode<K> TreeNode;
public:
    //二叉搜索树的插入
    bool Insert(const K& key)
    {
		if (_root == nullptr)
        {
			_root = new TreeNode(key);
			return true;
		}


        TreeNode* parent = nullptr;
        TreeNode* cur = _root;
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
        }

        cur = new TreeNode(key);
        if(parent->_key > key)
        {
            parent->_left = cur;
        }
        else
        {
            parent->_right = cur;
        }
        return true;
    }

    //递归实现插入
    //插入的接口
    bool InsertR(const K& key)
    {
        return _InsertR(_root, key);
    }

    //这里加&是为了在递归中更新_root的值 不用再创建一个父亲结点链接插入的root
    bool _InsertR(TreeNode*& _root, const K& key)
    {
        if (_root == nullptr)
        { 
            _root = new TreeNode(key);
            return true;
        }
        else if (_root->_key == key)
        {
            return false;
        }
        else if (_root->_key < key)
        {
            return _InsertR(_root->_right, key);
        }
        else
        {
            return _InsertR(_root->_left, key);
        }
    }


    //二叉搜索树的查找
    bool Find(const K& key) 
    {
		TreeNode* cur = _root;
		while (cur) 
        {
			if (cur->_key < key) 
            {
				cur = cur->_right;
			}

			else if (cur->_key > key) 
            {
				cur = cur->_left;
			}

			else 
            {
				return true;
			}
		}

		return false;
	}

    //递归实现查找
    //查找的接口
    bool FindR(const K& key)
    {
        return _FindR(_root, key);
    }

    bool _FindR(TreeNode* _root, const K& key)
    {
        if (_root == nullptr)
        {
            return false;
        }
        else if (_root->_key == key)
        {
            return true;
        }
        else if (_root->_key < key)
        {
            return _FindR(_root->_right, key);
        }
        else
        {
            return _FindR(_root->_left, key);
        }
    }

    //二叉搜索树不支持修改
    //二叉搜索树的删除
    //一种特殊情况: ⽆法直接删除N结点，因为N的两个孩⼦⽆处安放，只能⽤替换法删除。
    //找N左⼦树的值最⼤结点R(最右结点) 或者 N右⼦树的值最⼩结点R(最左结点)替代N
    bool Erase(const K& key)
    {
        TreeNode* parent = nullptr;
        TreeNode* cur = _root;
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
                //找到值了 进行删除
                if(cur->_left == nullptr) //左子树为空
                {
                    //删除的是根结点
                    if(cur == _root)
                    {
                        _root = cur->_right;
                    }

                    else
                    {
                        //判断是左子树还是右子树
                        if(cur == parent->_left)
                        {
                            parent->_left = cur->_right;
                        }
                        else
                        {
                            parent->_right = cur->_right;
                        }
                    }

                    delete cur;
                 
                }

                else if(cur->_right == nullptr) //右子树为空
                {
                    //删除的是根结点
                    if(cur == _root)
                    {
                        _root = cur->_left;
                    }

                    else
                    {
                        //判断是左子树还是右子树
                        if(cur == parent->_left)
                        {
                            parent->_left = cur->_left;
                        }
                        else
                        {
                            parent->_right = cur->_left;
                        }
                    }

                    delete cur;
                 
                }

                else //左右子树都不为空
                {
                    //记录下右子树的最小结点的父结点
                    TreeNode* replaceParent = cur;
                    //选择用右子树的最小结点 也就是右子树的最左结点
                    TreeNode* replace = cur->_right;

                    while(replace->_left != nullptr)
                    {
                        replaceParent = replace;
                        replace = replace->_left;
                    }

                    //用右子树的最小结点替代N
                    //交换要删除的结点和右子树的最小结点的值
                    std::swap(cur->_key, replace->_key);

                    //再删除右子树的最小结点 （一定是左为空 直接让parent指向 repalce right即可）
                    if(replace == replaceParent->_right)
                    {
                        replaceParent->_right = replace->_right;
                    }
                    else
                    {
                        replaceParent->_left = replace->_right;
                    }

                    delete replace;
                }


                return true;
            }
        }
        return false;
    }

    // 给外部调用中序函数的接口 进行中序遍历函数的调用
    void InOrder()
    {
        _InOrder(_root);
        cout << endl;
    }

    void _InOrder(TreeNode* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}


private:
    TreeNode* _root = nullptr;



};

}

//key/value⼆叉搜索树
//只有插入的逻辑需要改动 删除和查找不需要改动
namespace keyvalue
{
    template<class K, class V>
    struct BinarySearchTreeNode
    {
        BinarySearchTreeNode<K, V>* _left;
        BinarySearchTreeNode<K, V>* _right;
        K _key;
        V _value;

         
        BinarySearchTreeNode(const K& key, const V& value)
            : _key(key)
            , _value(value)
            , _left(nullptr)
            , _right(nullptr)
        {

        }

    };

    template<class K, class V>
    class BinarySearchTree
    {
        typedef BinarySearchTreeNode<K, V> TreeNode;
    public:
        BinarySearchTree()
        {
        }

        BinarySearchTree(const BinarySearchTree& tree)
        {
            _root = _Copy(tree._root);
        }

        BinarySearchTree& operator=(const BinarySearchTree& tree)
        {
            TreeNode* copy = _Copy(tree._root);
            _Destroy(_root);
            _root = copy;
            return *this;
        }

        ~BinarySearchTree()
        {
            _Destroy(_root);
        }
        
        //二叉搜索树的插入
        bool Insert(const K& key, const V& value)
        {
            if (_root == nullptr)
            {
                _root = new TreeNode(key, value);
                return true;
            }


            TreeNode* parent = nullptr;
            TreeNode* cur = _root;
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
            return true;
        }

        //递归实现插入
        //插入的接口
        bool InsertR(const K& key, const V& value)
        {
            return _InsertR(_root, key, value);
        }

        //这里加&是为了在递归中更新_root的值 不用再创建一个父亲结点链接插入的root
        bool _InsertR(TreeNode*& _root, const K& key, const V& value)
        {
            if (_root == nullptr)
            { 
                _root = new TreeNode(key, value);
                return true;
            }
            else if (_root->_key == key)
            {
                return false;
            }
            else if (_root->_key < key)
            {
                return _InsertR(_root->_right, key, value);
            }
            else
            {
                return _InsertR(_root->_left, key, value);
            }
        }


        //二叉搜索树的查找
        TreeNode* Find(const K& key) 
        {
            TreeNode* cur = _root;
            while (cur) 
            {
                if (cur->_key < key) 
                {
                    cur = cur->_right;
                }

                else if (cur->_key > key) 
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
        
        //递归实现查找
        //查找的接口
        TreeNode* FindR(const K& key)
        {
            return _FindR(_root, key);
        }

        TreeNode* _FindR(TreeNode* _root, const K& key)
        {
            if (_root == nullptr)
            {
                return nullptr;
            }
            else if (_root->_key == key)
            {
                return _root;
            }
            else if (_root->_key < key)
            {
                return _FindR(_root->_right, key);
            }
            else
            {
                return _FindR(_root->_left, key);
            }
        }

        //二叉搜索树不支持修改
        //二叉搜索树的删除
        //一种特殊情况: ⽆法直接删除N结点，因为N的两个孩⼦⽆处安放，只能⽤替换法删除。
        //找N左⼦树的值最⼤结点R(最右结点) 或者 N右⼦树的值最⼩结点R(最左结点)替代N
        bool Erase(const K& key)
        {
            TreeNode* parent = nullptr;
            TreeNode* cur = _root;
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
                    //找到值了 进行删除
                    if(cur->_left == nullptr) //左子树为空
                    {
                        //删除的是根结点
                        if(cur == _root)
                        {
                            _root = cur->_right;
                        }

                        else
                        {
                            //判断是左子树还是右子树
                            if(cur == parent->_left)
                            {
                                parent->_left = cur->_right;
                            }
                            else
                            {
                                parent->_right = cur->_right;
                            }
                        }

                        delete cur;
                    
                    }

                    else if(cur->_right == nullptr) //右子树为空
                    {
                        //删除的是根结点
                        if(cur == _root)
                        {
                            _root = cur->_left;
                        }

                        else
                        {
                            //判断是左子树还是右子树
                            if(cur == parent->_left)
                            {
                                parent->_left = cur->_left;
                            }
                            else
                            {
                                parent->_right = cur->_left;
                            }
                        }

                        delete cur;
                    
                    }

                    else //左右子树都不为空
                    {
                        //记录下右子树的最小结点的父结点
                        TreeNode* replaceParent = cur;
                        //选择用右子树的最小结点 也就是右子树的最左结点
                        TreeNode* replace = cur->_right;

                        while(replace->_left != nullptr)
                        {
                            replaceParent = replace;
                            replace = replace->_left;
                        }

                        //用右子树的最小结点替代N
                        //交换要删除的结点和右子树的最小结点的值
                        std::swap(cur->_key, replace->_key);

                        //再删除右子树的最小结点 （一定是左为空 直接让parent指向 repalce right即可）
                        if(replace == replaceParent->_right)
                        {
                            replaceParent->_right = replace->_right;
                        }
                        else
                        {
                            replaceParent->_left = replace->_right;
                        }

                        delete replace;
                    }


                    return true;
                }
            }
            return false;
        }

        // 给外部调用中序函数的接口 进行中序遍历函数的调用
        void InOrder()
        {
            _InOrder(_root);
            cout << endl;
        }

        void _InOrder(TreeNode* root)
        {
            if (root == nullptr)
            {
                return;
            }
            _InOrder(root->_left);
            cout << root->_key << ":" << root->_value << " ";
            cout << endl;
            _InOrder(root->_right);
        }

    private:
        void _Destroy(TreeNode* root)
        {
            if (root == nullptr)
            {
                return;
            }

            _Destroy(root->_left);
            _Destroy(root->_right);
            delete root;
        }

        TreeNode* _Copy(TreeNode* root)
        {
            if (root == nullptr)
            {
                return nullptr;
            }

            TreeNode* copy = new TreeNode(root->_key, root->_value);
            copy->_left = _Copy(root->_left);
            copy->_right = _Copy(root->_right);

            return copy;
        }

    private:
        TreeNode* _root = nullptr;


    };
}


