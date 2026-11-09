#pragma once
#include <iostream>
using namespace std;


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
    // 给外部调用中序函数的接口 进行中序遍历函数的调用
    void InOrder()
    {
        _InOrder(_root);
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
