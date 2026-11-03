#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <errno.h>

#define MAX_SIZE 1001

typedef struct TreeNode
{
    char op;                  // '#'表示数字，其余为运算符
    double value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct Stack
{
    TreeNode *nodes[MAX_SIZE]; // 保存已经建立的子树
    char operators[MAX_SIZE]; // 保存尚未处理的运算符
    int nodeTop;
    int operatorTop;
} Stack;

TreeNode *CreateNode(char op, double value)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    if (node == NULL)
    {
        printf("内存申请失败。\n");
        exit(EXIT_FAILURE);
    }
    node->op = op;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void FreeTree(TreeNode *root)
{
    if (root == NULL)
        return;
    FreeTree(root->left);
    FreeTree(root->right);
    free(root);
}

int Priority(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

// 先出栈的是右子树，后出栈的是左子树
int MergeTree(Stack *stack)
{
    if (stack->nodeTop < 1)
        return 0;
    char op = stack->operators[stack->operatorTop--];
    TreeNode *root = CreateNode(op, 0);
    root->right = stack->nodes[stack->nodeTop--];
    root->left = stack->nodes[stack->nodeTop--];
    stack->nodes[++stack->nodeTop] = root;
    printf("建树：以 %c 为根，连接左、右子树。\n", op);
    return 1;
}

TreeNode *BuildTree(char expression[], int *finished)
{
    Stack stack;
    stack.nodeTop = -1;
    stack.operatorTop = -1;
    int index = 0;
    int needNumber = 1; // 1表示当前应读数字或左括号
    *finished = 0;

    while (expression[index] != '\0')
    {
        char current = expression[index];
        if (isspace((unsigned char)current))
        {
            index++;
            continue;
        }
        if (current == '=')
            break;
        if (needNumber)
        {
            if (current == '(')
            {
                stack.operators[++stack.operatorTop] = current;
                index++;
            }
            else if (isdigit((unsigned char)current) ||
                     current == '.' || current == '+' || current == '-')
            {
                // strtod读取一个完整数值，并让end指向它后面的字符
                char *end;
                errno = 0;
                double number = strtod(expression + index, &end);
                if (end == expression + index || errno == ERANGE ||
                    !isfinite(number))
                    goto error;
                index = (int)(end - expression);
                stack.nodes[++stack.nodeTop] = CreateNode('#', number);
                printf("建树：数字 %.10g 作为叶子结点。\n", number);
                needNumber = 0;
            }
            else
                goto error;
        }
        else if (Priority(current) > 0)
        {
            while (stack.operatorTop >= 0 &&
                   stack.operators[stack.operatorTop] != '(' &&
                   Priority(stack.operators[stack.operatorTop]) >=
                   Priority(current))
            {
                if (!MergeTree(&stack))
                    goto error;
            }
            stack.operators[++stack.operatorTop] = current;
            index++;
            needNumber = 1;
        }
        else if (current == ')')
        {
            while (stack.operatorTop >= 0 &&
                   stack.operators[stack.operatorTop] != '(')
            {
                if (!MergeTree(&stack))
                    goto error;
            }
            if (stack.operatorTop < 0)
                goto error;
            stack.operatorTop--; // 丢弃与右括号配对的左括号
            index++;
        }
        else
            goto error;
    }

    if (expression[index] != '=')
        goto error;
    index++;
    while (isspace((unsigned char)expression[index]))
        index++;
    if (expression[index] != '\0')
        goto error;

    if (needNumber)
    {
        if (stack.nodeTop == -1 && stack.operatorTop == -1)
        {
            *finished = 1; // 单独输入等号，按题目要求结束
            return NULL;
        }
        goto error;
    }
    while (stack.operatorTop >= 0)
    {
        if (stack.operators[stack.operatorTop] == '(' ||
            !MergeTree(&stack))
            goto error;
    }
    if (stack.nodeTop != 0)
        goto error;
    return stack.nodes[0];

error:
    printf("输入有误：请检查数字、运算符、括号和末尾的等号。\n");
    while (stack.nodeTop >= 0)
        FreeTree(stack.nodes[stack.nodeTop--]);
    return NULL;
}

// 中序遍历时加上括号，显示表达式树对应的运算关系
void PrintExpression(TreeNode *root)
{
    if (root->op == '#')
    {
        printf("%.10g", root->value);
        return;
    }
    printf("(");
    PrintExpression(root->left);
    printf(" %c ", root->op);
    PrintExpression(root->right);
    printf(")");
}

void PostOrder(TreeNode *root)
{
    if (root == NULL)
        return;
    PostOrder(root->left);
    PostOrder(root->right);
    if (root->op == '#')
        printf("%.10g ", root->value);
    else
        printf("%c ", root->op);
}

// 后序求值：先算左子树，再算右子树，最后处理根结点
double EvaluateTree(TreeNode *root, int *ok, int *step)
{
    if (root->op == '#')
        return root->value;
    double left = EvaluateTree(root->left, ok, step);
    if (!*ok)
        return 0;
    double right = EvaluateTree(root->right, ok, step);
    if (!*ok)
        return 0;

    double result = 0;
    switch (root->op)
    {
        case '+': result = left + right; break;
        case '-': result = left - right; break;
        case '*': result = left * right; break;
        case '/':
            if (right == 0)
            {
                printf("计算失败：除数不能为0。\n");
                *ok = 0;
                return 0;
            }
            result = left / right;
            break;
    }
    if (!isfinite(result))
    {
        printf("计算失败：结果超出可表示范围。\n");
        *ok = 0;
        return 0;
    }
    printf("第%d步：%.10g %c %.10g = %.10g\n",
           (*step)++, left, root->op, right, result);
    return result;
}

void ClearLine(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

int main(void)
{
    char expression[MAX_SIZE + 1];
    int choice;
    printf("========== 基于二叉树的表达式求值 ==========\n");
    printf("支持+、-、*、/、括号、多位数、小数和带符号的数值。\n");
    printf("表达式以=结尾，最多1000个字符，允许空格。\n");
    printf("示例：2*(2+5)=，结果为14；1+2=，结果为3。\n");
    printf("负数写成-2或(-2)，对整个括号取负请写成0-(...)。\n");
    printf("单独输入=也可以结束。开始请输入1，退出请输入0：");
    while (scanf("%d", &choice) == 1)
    {
        ClearLine();
        if (choice == 0)
            break;
        if (choice == 1)
        {
            printf("\n请输入表达式：\n");
            if (fgets(expression, sizeof(expression), stdin) == NULL)
                break;
            size_t length = strcspn(expression, "\r\n");
            if (length > 1000 ||
                (expression[length] == '\0' && !feof(stdin)))
            {
                ClearLine();
                printf("输入过长，请控制在1000个字符以内。\n");
            }
            else
            {
                expression[length] = '\0';
                int finished;
                printf("---------- 表达式树建立过程 ----------\n");
                TreeNode *root = BuildTree(expression, &finished);
                if (finished)
                    break;
                if (root != NULL)
                {
                    printf("中序表达式：");
                    PrintExpression(root);
                    printf("\n后序遍历：");
                    PostOrder(root);
                    printf("\n---------- 后序计算过程 ----------\n");
                    int ok = 1, step = 1;
                    double result = EvaluateTree(root, &ok, &step);
                    if (ok)
                        printf("计算结果：%.10g\n", result);
                    FreeTree(root);
                }
            }
        }
        else
            printf("选择有误，请输入1或0。\n");
        printf("\n继续请输入1，退出请输入0：");
    }
    printf("程序已退出。\n");
    return 0;
}
