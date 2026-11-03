#include <stdio.h>
#include <string.h>
#define MAX_SIZE 1000
// ???

/* 求模式串的next数组，下标从0开始 */
void GetNext(char pattern[], int next[])
{
    int index = 0;
    int prefix = -1;
    int length = strlen(pattern);

    next[0] = -1;
    while (index < length - 1)
    {
        if (prefix == -1 || pattern[index] == pattern[prefix])
        {
            index++;
            prefix++;
            next[index] = prefix;
        }
        else
        {
            prefix = next[prefix];
        }
    }
}

/* 找到时返回起始下标，没有找到时返回-1 */
int KmpSearch(char human[], char pattern[])
{
    int next[MAX_SIZE];
    int humanIndex = 0;
    int patternIndex = 0;
    int humanLength = strlen(human);
    int patternLength = strlen(pattern);
    int index;

    GetNext(pattern, next);
    printf("next数组（下标从0开始）：");
    for (index = 0; index < patternLength; index++)
    {
        printf("%d ", next[index]);
    }
    printf("\n");

    while (humanIndex < humanLength && patternIndex < patternLength)
    {
        if (patternIndex == -1)
        {
            humanIndex++;
            patternIndex = 0;
        }
        else
        {
            printf("比较：人的第%d位%c，病毒的第%d位%c。",
                   humanIndex + 1, human[humanIndex],
                   patternIndex + 1, pattern[patternIndex]);
            if (human[humanIndex] == pattern[patternIndex])
            {
                printf("相同，继续比较后面的字符。\n");
                humanIndex++;
                patternIndex++;
            }
            else
            {
                if (next[patternIndex] == -1)
                {
                    printf("不同，人的位置后移，从病毒第1位重新比较。\n");
                }
                else
                {
                    printf("不同，人的位置不变，病毒从第%d位继续比较。\n",
                           next[patternIndex] + 1);
                }
                patternIndex = next[patternIndex];
            }
        }
    }

    if (patternIndex == patternLength)
    {
        return humanIndex - patternLength;
    }
    return -1;
}

/* 将环状病毒从不同位置展开，再分别进行KMP匹配 */
int DetectVirus(char virus[], char human[])
{
    char rotated[MAX_SIZE];
    int virusLength = strlen(virus);
    int humanLength = strlen(human);
    int start, index, position;

    if (virusLength > humanLength)
    {
        printf("病毒序列比人的序列长，不能完整匹配。\n");
        return 0;
    }

    for (start = 0; start < virusLength; start++)
    {
        for (index = 0; index < virusLength; index++)
        {
            rotated[index] = virus[(start + index) % virusLength];
        }
        rotated[virusLength] = '\0';

        printf("\n第%d次展开：%s\n", start + 1, rotated);
        position = KmpSearch(human, rotated);
        if (position >= 0)
        {
            printf("匹配成功：人的第%d位到第%d位为%s。\n",
                   position + 1, position + virusLength, rotated);
            return 1;
        }
        printf("本次未找到完整匹配。\n");
    }
    printf("所有展开方式都未找到完整匹配。\n");
    return 0;
}

int main(void)
{
    char virus[MAX_SIZE];
    char human[MAX_SIZE];
    int choice, infected;

    printf("========== 病毒DNA感染检测 ==========\n");
    printf("每组输入：病毒DNA 人的DNA，两个序列用空格分隔。\n");
    printf("序列由字母组成，每个序列不超过999个字符。\n");
    printf("病毒DNA是环状，人的DNA是线性，区分字母大小写。\n");
    printf("示例1：abbab abbabaab，预期YES。\n");
    printf("示例2：baa cacdvcabacsd，预期YES。\n");
    printf("示例3：abc def，预期NO。\n");
    printf("输入0 0也可以直接结束。\n\n");
    printf("开始检测请输入1，退出请输入0：");
    if (scanf("%d", &choice) != 1)
    {
        return 1;
    }

    while (choice != 0)
    {
        if (choice == 1)
        {
            printf("\n请输入病毒DNA和人的DNA（例如abbab abbabaab）：\n");
            if (scanf("%999s %999s", virus, human) != 2)
            {
                return 1;
            }
            if (strcmp(virus, "0") == 0 && strcmp(human, "0") == 0)
            {
                break;
            }

            printf("病毒DNA：%s\n人的DNA：%s\n", virus, human);
            printf("---------- 展开与匹配过程 ----------\n");
            infected = DetectVirus(virus, human);
            printf("\n检测结果（YES表示感染，NO表示未感染）：\n");
            if (infected == 1)
            {
                printf("YES\n\n");
            }
            else
            {
                printf("NO\n\n");
            }
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
