#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <errno.h>
//实验四
#define MAX_SIZE 1001

typedef struct TreeNode
{
    char op;                  // '#'��ʾ���֣�����Ϊ�����
    double value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct Stack
{
    TreeNode *nodes[MAX_SIZE]; // �����Ѿ�����������
    char operators[MAX_SIZE]; // ������δ�����������
    int nodeTop;
    int operatorTop;
} Stack;

TreeNode *CreateNode(char op, double value)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    if (node == NULL)
    {
        printf("�ڴ�����ʧ�ܡ�\n");
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

// �ȳ�ջ���������������ջ����������
int MergeTree(Stack *stack)
{
    if (stack->nodeTop < 1)
        return 0;
    char op = stack->operators[stack->operatorTop--];
    TreeNode *root = CreateNode(op, 0);
    root->right = stack->nodes[stack->nodeTop--];
    root->left = stack->nodes[stack->nodeTop--];
    stack->nodes[++stack->nodeTop] = root;
    printf("�������� %c Ϊ������������������\n", op);
    return 1;
}

TreeNode *BuildTree(char expression[], int *finished)
{
    Stack stack;
    stack.nodeTop = -1;
    stack.operatorTop = -1;
    int index = 0;
    int needNumber = 1; // 1��ʾ��ǰӦ�����ֻ�������
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
                // strtod��ȡһ��������ֵ������endָ����������ַ�
                char *end;
                errno = 0;
                double number = strtod(expression + index, &end);
                if (end == expression + index || errno == ERANGE ||
                    !isfinite(number))
                    goto error;
                index = (int)(end - expression);
                stack.nodes[++stack.nodeTop] = CreateNode('#', number);
                printf("���������� %.10g ��ΪҶ�ӽ�㡣\n", number);
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
            stack.operatorTop--; // ��������������Ե�������
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
            *finished = 1; // ��������Ⱥţ�����ĿҪ�����
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
    printf("���������������֡�����������ź�ĩβ�ĵȺš�\n");
    while (stack.nodeTop >= 0)
        FreeTree(stack.nodes[stack.nodeTop--]);
    return NULL;
}

// �������ʱ�������ţ���ʾ����ʽ����Ӧ�������ϵ
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

// ������ֵ������������������������������������
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
                printf("����ʧ�ܣ���������Ϊ0��\n");
                *ok = 0;
                return 0;
            }
            result = left / right;
            break;
    }
    if (!isfinite(result))
    {
        printf("����ʧ�ܣ���������ɱ�ʾ��Χ��\n");
        *ok = 0;
        return 0;
    }
    printf("��%d����%.10g %c %.10g = %.10g\n",
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
    printf("========== ���ڶ������ı���ʽ��ֵ ==========\n");
    printf("֧��+��-��*��/�����š���λ����С���ʹ����ŵ���ֵ��\n");
    printf("����ʽ��=��β�����1000���ַ��������ո�\n");
    printf("ʾ����2*(2+5)=�����Ϊ14��1+2=�����Ϊ3��\n");
    printf("����д��-2��(-2)������������ȡ����д��0-(...)��\n");
    printf("��������=Ҳ���Խ�������ʼ������1���˳�������0��");
    while (scanf("%d", &choice) == 1)
    {
        ClearLine();
        if (choice == 0)
            break;
        if (choice == 1)
        {
            printf("\n���������ʽ��\n");
            if (fgets(expression, sizeof(expression), stdin) == NULL)
                break;
            size_t length = strcspn(expression, "\r\n");
            if (length > 1000 ||
                (expression[length] == '\0' && !feof(stdin)))
            {
                ClearLine();
                printf("����������������1000���ַ����ڡ�\n");
            }
            else
            {
                expression[length] = '\0';
                int finished;
                printf("---------- ����ʽ���������� ----------\n");
                TreeNode *root = BuildTree(expression, &finished);
                if (finished)
                    break;
                if (root != NULL)
                {
                    printf("�������ʽ��");
                    PrintExpression(root);
                    printf("\n���������");
                    PostOrder(root);
                    printf("\n---------- ���������� ----------\n");
                    int ok = 1, step = 1;
                    double result = EvaluateTree(root, &ok, &step);
                    if (ok)
                        printf("��������%.10g\n", result);
                    FreeTree(root);
                }
            }
        }
        else
            printf("ѡ������������1��0��\n");
        printf("\n����������1���˳�������0��");
    }
    printf("�������˳���\n");
    return 0;
}
