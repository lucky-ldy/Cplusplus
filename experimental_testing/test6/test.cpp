#include <stdio.h>
#include <stdlib.h>
//实验六    

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} Node;

// 创建一个结点，并初始化左右孩子指针。
Node *createNode(int key)
{
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL)
    {
        return NULL;
    }

    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 插入关键字：较小值放左子树，较大值放右子树。
Node *insertBST(Node *root, int key)
{
    if (root == NULL)
    {
        return createNode(key);
    }

    if (key < root->key)
    {
        root->left = insertBST(root->left, key);
    }
    else if (key > root->key)
    {
        root->right = insertBST(root->right, key);
    }
    // 本程序不插入重复关键字。

    return root;
}

// 检查每个结点是否满足整棵子树的取值范围。
int isBSTRange(Node *root, long long minValue, long long maxValue)
{
    if (root == NULL)
    {
        return 1;
    }

    if (root->key <= minValue || root->key >= maxValue)
    {
        return 0;
    }

    return isBSTRange(root->left, minValue, root->key) &&
           isBSTRange(root->right, root->key, maxValue);
}

int isBST(Node *root)
{
    return isBSTRange(root, -2147483649LL, 2147483648LL);
}

// 查找关键字，并依次输出访问到的结点作为查找路径。
int searchPath(Node *root, int key)
{
    Node *current = root;
    int first = 1;

    while (current != NULL)
    {
        if (!first)
        {
            printf(" -> ");
        }
        printf("%d", current->key);
        first = 0;

        if (key == current->key)
        {
            return 1;
        }
        else if (key < current->key)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    return 0;
}

// 查找子树中的最小结点，也就是最左侧结点。
Node *minimumNode(Node *root)
{
    while (root != NULL && root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

// 删除关键字，并重新连接删除后剩下的结点。
Node *deleteNode(Node *root, int key)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (key < root->key)
    {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->key)
    {
        root->right = deleteNode(root->right, key);
    }
    else
    {
        // 情况一或二：没有左孩子，用右孩子接替当前结点。
        if (root->left == NULL)
        {
            Node *child = root->right;
            free(root);
            return child;
        }
        // 情况二：没有右孩子，用左孩子接替当前结点。
        else if (root->right == NULL)
        {
            Node *child = root->left;
            free(root);
            return child;
        }

        // 情况三：有两个孩子，用右子树最小结点的关键字替换。
        Node *successor = minimumNode(root->right);
        root->key = successor->key;
        root->right = deleteNode(root->right, successor->key);
    }

    return root;
}

// 按从小到大的顺序输出关键字。
void printInorder(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    printInorder(root->left);
    printf("%d ", root->key);
    printInorder(root->right);
}

// 释放整棵树的所有结点，避免内存泄漏。
void freeTree(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void)
{
    int keys[] = {4, 9, 0, 1, 8, 6, 3, 5, 2, 7};
    int count = (int)(sizeof(keys) / sizeof(keys[0]));
    Node *root = NULL;

    // 按题目给出的关键字序列建立二叉排序树。
    for (int i = 0; i < count; i++)
    {
        root = insertBST(root, keys[i]);
        if (root == NULL)
        {
            printf("Memory allocation failed.\n");
            return 1;
        }
    }

    printf("BST before deletion: %s\n", isBST(root) ? "valid" : "invalid");
    printf("Search path for 6: ");
    if (!searchPath(root, 6))
    {
        printf(" (not found)");
    }
    printf("\n");

    printf("Inorder before deleting 5: ");
    printInorder(root);
    printf("\n");

    root = deleteNode(root, 5);

    printf("Inorder after deleting 5: ");
    printInorder(root);
    printf("\n");
    printf("BST after deletion: %s\n", isBST(root) ? "valid" : "invalid");

    freeTree(root);
    return 0;
}

