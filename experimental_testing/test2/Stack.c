#include <stdio.h>
#define MAX_SIZE 256
#define MAX_FORMULA 768
//实验二
typedef struct Stack
{
    int data[MAX_SIZE];
    char formula[MAX_SIZE][MAX_FORMULA];
    int top;
} Stack;

/* ������ʽ�ַ��� */
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

/* ͬʱ������ֵ������Ӧ����ʽ */
void StackPush(Stack *stack, int value, char formula[])
{
    stack->top++;
    stack->data[stack->top] = value;
    CopyString(stack->formula[stack->top], formula);
}

/* ͬʱȡ����ֵ������Ӧ����ʽ */
int StackPop(Stack *stack, char formula[])
{
    int value = stack->data[stack->top];
    CopyString(formula, stack->formula[stack->top]);
    stack->top--;
    return value;
}

/* ������������ʽ��ϳɣ�(����ʽ ����� ����ʽ) */
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

/* ���밴��ĿԼ������Ч�ĺ�׺����ʽ */
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

            /* �������ֵ����֣�������������� */
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
            /* ��ȡ�ұߣ���ȡ��ߣ��������Ǹ��Ե���ʽ */
            right = StackPop(&stack, rightFormula);
            left = StackPop(&stack, leftFormula);
            result = Calculate(left, right, current);
            BuildFormula(formula, leftFormula, rightFormula, current);
            printf("��%d����%s\n", step, formula);
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

    printf("========== ��׺����ʽ��ֵ ==========\n");
    printf("�����ʽ�������������֮����Ӣ�Ķ��ŷָ���\n");
    printf("֧��+��-��*��/��֧�ֶ�λ�����͸�������\n");
    printf("��Ҫ����ո����Ż�Ⱥţ����Ȳ�����255���ַ���\n");
    printf("ʾ����2,1,+,3,*  ��Ӧ��ʽ(2+1)*3��\n");
    printf("ʾ����4,13,5,/,+ ��Ӧ��ʽ4+13/5��\n");
    printf("�������������㣬����13/5Ϊ2��\n\n");
    printf("��ʼ����������1���˳�������0��");
    if (scanf("%d", &choice) != 1)
    {
        return 1;
    }
    while (choice != 0)
    {
        if (choice == 1)
        {
            printf("\n�������׺����ʽ������2,1,+,3,*����\n");
            if (scanf("%255s", expression) != 1)
            {
                return 1;
            }
            printf("\n����ĺ�׺����ʽ��%s\n", expression);
            printf("---------- ��ʽ����� ----------\n");
            result = EvaluatePostfix(expression, finalFormula);
            printf("������ʽ��%s\n", finalFormula);
            printf("��������%d\n\n", result);
        }
        else
        {
            printf("ѡ������������1��0��\n");
        }
        printf("����������1���˳�������0��");
        if (scanf("%d", &choice) != 1)
        {
            return 1;
        }
    }
    printf("�������˳���\n");
    return 0;
}
