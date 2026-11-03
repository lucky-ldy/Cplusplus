#include <stdio.h>
#include <string.h>
#define MAX_SIZE 1000
//实验三
/* ��ģʽ����next���飬�±��0��ʼ */
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

/* �ҵ�ʱ������ʼ�±꣬û���ҵ�ʱ����-1 */
int KmpSearch(char human[], char pattern[])
{
    int next[MAX_SIZE];
    int humanIndex = 0;
    int patternIndex = 0;
    int humanLength = strlen(human);
    int patternLength = strlen(pattern);
    int index;

    GetNext(pattern, next);
    printf("next���飨�±��0��ʼ����");
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
            printf("�Ƚϣ��˵ĵ�%dλ%c�������ĵ�%dλ%c��",
                   humanIndex + 1, human[humanIndex],
                   patternIndex + 1, pattern[patternIndex]);
            if (human[humanIndex] == pattern[patternIndex])
            {
                printf("��ͬ�������ȽϺ�����ַ���\n");
                humanIndex++;
                patternIndex++;
            }
            else
            {
                if (next[patternIndex] == -1)
                {
                    printf("��ͬ���˵�λ�ú��ƣ��Ӳ�����1λ���±Ƚϡ�\n");
                }
                else
                {
                    printf("��ͬ���˵�λ�ò��䣬�����ӵ�%dλ�����Ƚϡ�\n",
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

/* ����״�����Ӳ�ͬλ��չ�����ٷֱ����KMPƥ�� */
int DetectVirus(char virus[], char human[])
{
    char rotated[MAX_SIZE];
    int virusLength = strlen(virus);
    int humanLength = strlen(human);
    int start, index, position;

    if (virusLength > humanLength)
    {
        printf("�������б��˵����г�����������ƥ�䡣\n");
        return 0;
    }

    for (start = 0; start < virusLength; start++)
    {
        for (index = 0; index < virusLength; index++)
        {
            rotated[index] = virus[(start + index) % virusLength];
        }
        rotated[virusLength] = '\0';

        printf("\n��%d��չ����%s\n", start + 1, rotated);
        position = KmpSearch(human, rotated);
        if (position >= 0)
        {
            printf("ƥ��ɹ����˵ĵ�%dλ����%dλΪ%s��\n",
                   position + 1, position + virusLength, rotated);
            return 1;
        }
        printf("����δ�ҵ�����ƥ�䡣\n");
    }
    printf("����չ����ʽ��δ�ҵ�����ƥ�䡣\n");
    return 0;
}

int main(void)
{
    char virus[MAX_SIZE];
    char human[MAX_SIZE];
    int choice, infected;

    printf("========== ����DNA��Ⱦ��� ==========\n");
    printf("ÿ�����룺����DNA �˵�DNA�����������ÿո�ָ���\n");
    printf("��������ĸ��ɣ�ÿ�����в�����999���ַ���\n");
    printf("����DNA�ǻ�״���˵�DNA�����ԣ�������ĸ��Сд��\n");
    printf("ʾ��1��abbab abbabaab��Ԥ��YES��\n");
    printf("ʾ��2��baa cacdvcabacsd��Ԥ��YES��\n");
    printf("ʾ��3��abc def��Ԥ��NO��\n");
    printf("����0 0Ҳ����ֱ�ӽ�����\n\n");
    printf("��ʼ���������1���˳�������0��");
    if (scanf("%d", &choice) != 1)
    {
        return 1;
    }

    while (choice != 0)
    {
        if (choice == 1)
        {
            printf("\n�����벡��DNA���˵�DNA������abbab abbabaab����\n");
            if (scanf("%999s %999s", virus, human) != 2)
            {
                return 1;
            }
            if (strcmp(virus, "0") == 0 && strcmp(human, "0") == 0)
            {
                break;
            }

            printf("����DNA��%s\n�˵�DNA��%s\n", virus, human);
            printf("---------- չ����ƥ����� ----------\n");
            infected = DetectVirus(virus, human);
            printf("\n�������YES��ʾ��Ⱦ��NO��ʾδ��Ⱦ����\n");
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
