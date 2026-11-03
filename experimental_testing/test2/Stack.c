#include <stdio.h>
#define MAX_SIZE 256
#define MAX_FORMULA 768
// ???

typedef struct Stack
{
    int data[MAX_SIZE];
    char formula[MAX_SIZE][MAX_FORMULA];
    int top;
} Stack;

/* 复制算式字符串 */
void CopyString(char target[], char source[])
{
    int index = 0;
    while (source[index] != '\0')
    {
        target[index] = source[index];
        index++;
    }
    target[index] = '\0';
}

void StackInit(Stack *stack)
{
    stack->top = -1;
}

/* 同时保存数值和它对应的算式 */
void StackPush(Stack *stack, int value, char formula[])
{
    stack->top++;
    stack->data[stack->top] = value;
    CopyString(stack->formula[stack->top], formula);
}

/* 同时取出数值和它对应的算式 */
int StackPop(Stack *stack, char formula[])
{
    int value = stack->data[stack->top];
    CopyString(formula, stack->formula[stack->top]);
    stack->top--;
    return value;
}

/* 将左右两个算式组合成：(左算式 运算符 右算式) */
void BuildFormula(char formula[], char left[], char right[], char op)
{
    int index = 0;
    int position = 0;
    formula[position++] = '(';
    while (left[index] != '\0')
    {
        formula[position++] = left[index++];
    }
    formula[position++] = ' ';
    formula[position++] = op;
    formula[position++] = ' ';
    index = 0;
    while (right[index] != '\0')
    {
        formula[position++] = right[index++];
    }
    formula[position++] = ')';
    formula[position] = '\0';
}

int Calculate(int left, int right, char op)
{
    switch (op)
    {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return left / right;
    }
    return 0;
}

/* 输入按题目约定是有效的后缀表达式 */
int EvaluatePostfix(char expression[], char finalFormula[])
{
    Stack stack;
    int index = 0;
    int step = 1;
    int number, sign, start, position;
    int left, right, result;
    char current;
    char numberText[MAX_FORMULA];
    char leftFormula[MAX_FORMULA];
    char rightFormula[MAX_FORMULA];
    char formula[MAX_FORMULA];

    StackInit(&stack);
    while (expression[index] != '\0')
    {
        current = expression[index];
        if (current == ',')
        {
            index++;
            continue;
        }
        if ((current >= '0' && current <= '9') ||
            (current == '-' && expression[index + 1] >= '0' &&
             expression[index + 1] <= '9'))
        {
            start = index;
            sign = 1;
            if (current == '-')
            {
                sign = -1;
                index++;
            }
            number = 0;
            while (expression[index] >= '0' &&
                   expression[index] <= '9')
            {
                number = number * 10 + expression[index] - '0';
                index++;
            }
            number = sign * number;

            /* 保存数字的文字，负数外面加括号 */
            position = 0;
            if (sign == -1)
            {
                numberText[position++] = '(';
            }
            while (start < index)
            {
                numberText[position++] = expression[start++];
            }
            if (sign == -1)
            {
                numberText[position++] = ')';
            }
            numberText[position] = '\0';
            StackPush(&stack, number, numberText);
        }
        else
        {
            /* 先取右边，再取左边，保留它们各自的算式 */
            right = StackPop(&stack, rightFormula);
            left = StackPop(&stack, leftFormula);
            result = Calculate(left, right, current);
            BuildFormula(formula, leftFormula, rightFormula, current);
            printf("第%d步：%s\n", step, formula);
            StackPush(&stack, result, formula);
            step++;
            index++;
        }
    }
    return StackPop(&stack, finalFormula);
}

int main(void)
{
    char expression[MAX_SIZE];
    char finalFormula[MAX_FORMULA];
    int result, choice;

    printf("========== 后缀表达式求值 ==========\n");
    printf("输入格式：整数和运算符之间用英文逗号分隔。\n");
    printf("支持+、-、*、/，支持多位整数和负整数。\n");
    printf("不要输入空格、括号或等号，长度不超过255个字符。\n");
    printf("示例：2,1,+,3,*  对应算式(2+1)*3。\n");
    printf("示例：4,13,5,/,+ 对应算式4+13/5。\n");
    printf("除法按整数计算，例如13/5为2。\n\n");
    printf("开始计算请输入1，退出请输入0：");
    if (scanf("%d", &choice) != 1)
    {
        return 1;
    }
    while (choice != 0)
    {
        if (choice == 1)
        {
            printf("\n请输入后缀表达式（例如2,1,+,3,*）：\n");
            if (scanf("%255s", expression) != 1)
            {
                return 1;
            }
            printf("\n输入的后缀表达式：%s\n", expression);
            printf("---------- 算式搭建过程 ----------\n");
            result = EvaluatePostfix(expression, finalFormula);
            printf("完整算式：%s\n", finalFormula);
            printf("计算结果：%d\n\n", result);
        }
        else
        {
            printf("选择有误，请输入1或0。\n");
        }
        printf("继续请输入1，退出请输入0：");
        if (scanf("%d", &choice) != 1)
        {
            return 1;
        }
    }
    printf("程序已退出。\n");
    return 0;
}
