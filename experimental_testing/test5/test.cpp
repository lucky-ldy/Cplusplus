
//实验五
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define INF 1000000000000LL

typedef struct Graph
{
    int n, m;
    char city[MAX_SIZE];
    long long edge[MAX_SIZE][MAX_SIZE];
} Graph;

int FindCity(Graph *graph, char name)
{
    for (int i = 0; i < graph->n; i++)
        if (graph->city[i] == name)
            return i;
    return -1;
}

// ��ȡ���С������·�Ͳ�ѯ���յ㣻0 0��ʾ����
int ReadGraph(Graph *graph, int *start, int *end)
{
    printf("��������и���n�͵�·����m��0 0��������\n");
    if (scanf("%d%d", &graph->n, &graph->m) != 2)
        return 0;
    if (graph->n == 0 && graph->m == 0)
        return 0;
    if (graph->n < 1 || graph->n > MAX_SIZE || graph->m < 0)
    {
        printf("�������󣺳��и���ӦΪ1~100����·��������Ϊ����\n");
        return 0;
    }
    printf("������%d����ͬ�ĵ��ַ����������ÿո�ָ���\n", graph->n);
    for (int i = 0; i < graph->n; i++)
    {
        if (scanf(" %c", &graph->city[i]) != 1)
            return 0;
        for (int j = 0; j < i; j++)
            if (graph->city[j] == graph->city[i])
            {
                printf("�������󣺳����������ظ���\n");
                return 0;
            }
    }
    for (int i = 0; i < graph->n; i++)
        for (int j = 0; j < graph->n; j++)
            graph->edge[i][j] = (i == j) ? 0 : INF;

    printf("����������%d�������·����� �յ� ���ȡ�\n", graph->m);
    for (int i = 0; i < graph->m; i++)
    {
        char from, to;
        long long length;
        if (scanf(" %c %c %lld", &from, &to, &length) != 3)
            return 0;
        int u = FindCity(graph, from);
        int v = FindCity(graph, to);
        if (u == -1 || v == -1 || length < 0 || length > 1000000000LL)
        {
            printf("�������󣺳��������г���������Ϊ0~1000000000��\n");
            return 0;
        }
        // ͬ������ظ���·ֻ�����϶̵�һ���������ӷ����
        if (length < graph->edge[u][v])
            graph->edge[u][v] = length;
    }
    char from, to;
    printf("���������ѯ�������յ㣺\n");
    if (scanf(" %c %c", &from, &to) != 2)
        return 0;
    *start = FindCity(graph, from);
    *end = FindCity(graph, to);
    if (*start == -1 || *end == -1)
    {
        printf("�������󣺲�ѯ���в��ڳ����б��С�\n");
        return 0;
    }
    return 1;
}

void PrintGraph(Graph *graph)
{
    printf("\n�ڽӾ����б�ʾ�������У��б�ʾ������У���\n");
    printf("INF��ʾû��ֱ�ӵ�·���Խ���Ϊ0��\n%12s", "");
    for (int i = 0; i < graph->n; i++)
        printf("%12c", graph->city[i]);
    printf("\n");
    for (int i = 0; i < graph->n; i++)
    {
        printf("%12c", graph->city[i]);
        for (int j = 0; j < graph->n; j++)
            if (graph->edge[i][j] == INF)
                printf("%12s", "INF");
            else
                printf("%12lld", graph->edge[i][j]);
        printf("\n");
    }
}

void PrintDistance(Graph *graph, long long distance[])
{
    printf("��ǰ���룺");
    for (int i = 0; i < graph->n; i++)
        if (distance[i] == INF)
            printf("%c=INF  ", graph->city[i]);
        else
            printf("%c=%lld  ", graph->city[i], distance[i]);
    printf("\n");
}

void PrintPath(Graph *graph, int previous[], int end)
{
    int path[MAX_SIZE];
    int count = 0;
    // ���յ���ǰ�����ݣ��ٵ������
    for (int current = end; current != -1; current = previous[current])
        path[count++] = current;
    printf("���·����");
    for (int i = count - 1; i >= 0; i--)
        printf("%c%s", graph->city[path[i]], i == 0 ? "\n" : " ");
}

void Dijkstra(Graph *graph, int start, int end)
{
    long long distance[MAX_SIZE];
    int visited[MAX_SIZE];
    int previous[MAX_SIZE];
    for (int i = 0; i < graph->n; i++)
    {
        distance[i] = INF;
        visited[i] = 0;
        previous[i] = -1;
    }
    distance[start] = 0;
    printf("\n---------- Dijkstra������� ----------\n");
    PrintDistance(graph, distance);
    for (int step = 1; step <= graph->n; step++)
    {
        int u = -1;
        // ��δȷ���ĳ�����ѡ��ǰ������С��һ��
        for (int i = 0; i < graph->n; i++)
            if (!visited[i] && distance[i] < INF &&
                (u == -1 || distance[i] < distance[u]))
                u = i;
        if (u == -1)
            break; // ʣ�µĳ��о����ɴ�
        visited[u] = 1;
        printf("��%d�֣�ȷ�ϳ���%c����̾���Ϊ%lld��\n",
               step, graph->city[u], distance[u]);
        if (u == end)
            break; // �յ����̾����Ѿ�ȷ��
        for (int v = 0; v < graph->n; v++)
        {
            if (visited[v] || graph->edge[u][v] == INF)
                continue;
            long long candidate = distance[u] + graph->edge[u][v];
            if (candidate < distance[v])
            {
                printf("����%c��%lld + %lld = %lld��ԭ����",
                       graph->city[v], distance[u], graph->edge[u][v], candidate);
                if (distance[v] == INF)
                    printf("INF");
                else
                    printf("%lld", distance[v]);
                printf("��ǰ����Ϊ%c��\n", graph->city[u]);
                distance[v] = candidate;
                previous[v] = u;
            }
        }
        PrintDistance(graph, distance);
    }
    printf("---------- ��ѯ��� ----------\n");
    if (distance[end] == INF)
    {
        printf("����%c�޷��������%c��\n", graph->city[start], graph->city[end]);
        printf("���·����������\n");
    }
    else
    {
        printf("���·�����ȣ�%lld\n", distance[end]);
        PrintPath(graph, previous, end);
    }
}

int main(void)
{
    Graph graph;
    int choice, start, end;
    printf("========== ���·����� ==========\n");
    printf("��������ͼ��Dijkstra�㷨����·���Ȳ���Ϊ����\n");
    printf("����˳��n m��n����������m����·����ѯ�����յ㡣\n");
    printf("�������õ���Ӣ����ĸ���������ֽڷǿհ��ַ������ִ�Сд��\n");
    printf("���磺3 3 / A B C / A B 1 / B C 1 / C A 3 / A C\n");
    printf("�����е�б�߱�ʾ���У�����Ҫ���롣\n");
    printf("��ʼ������1���˳�������0��");
    while (scanf("%d", &choice) == 1)
    {
        if (choice == 0)
            break;
        if (choice == 1)
        {
            if (!ReadGraph(&graph, &start, &end))
                break;
            PrintGraph(&graph);
            Dijkstra(&graph, start, end);
        }
        else
            printf("ѡ������������1��0��\n");
        printf("\n����������1���˳�������0��");
    }
    printf("�������˳���\n");
    return 0;
}
