
// ???
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

// 读取城市、有向道路和查询起终点；0 0表示结束
int ReadGraph(Graph *graph, int *start, int *end)
{
    printf("请输入城市个数n和道路条数m（0 0结束）：\n");
    if (scanf("%d%d", &graph->n, &graph->m) != 2)
        return 0;
    if (graph->n == 0 && graph->m == 0)
        return 0;
    if (graph->n < 1 || graph->n > MAX_SIZE || graph->m < 0)
    {
        printf("输入有误：城市个数应为1~100，道路条数不能为负。\n");
        return 0;
    }
    printf("请输入%d个不同的单字符城市名，用空格分隔：\n", graph->n);
    for (int i = 0; i < graph->n; i++)
    {
        if (scanf(" %c", &graph->city[i]) != 1)
            return 0;
        for (int j = 0; j < i; j++)
            if (graph->city[j] == graph->city[i])
            {
                printf("输入有误：城市名不能重复。\n");
                return 0;
            }
    }
    for (int i = 0; i < graph->n; i++)
        for (int j = 0; j < graph->n; j++)
            graph->edge[i][j] = (i == j) ? 0 : INF;

    printf("请逐行输入%d条有向道路：起点 终点 长度。\n", graph->m);
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
            printf("输入有误：城市须已列出，长度须为0~1000000000。\n");
            return 0;
        }
        // 同方向的重复道路只保留较短的一条；不添加反向边
        if (length < graph->edge[u][v])
            graph->edge[u][v] = length;
    }
    char from, to;
    printf("请输入待查询的起点和终点：\n");
    if (scanf(" %c %c", &from, &to) != 2)
        return 0;
    *start = FindCity(graph, from);
    *end = FindCity(graph, to);
    if (*start == -1 || *end == -1)
    {
        printf("输入有误：查询城市不在城市列表中。\n");
        return 0;
    }
    return 1;
}

void PrintGraph(Graph *graph)
{
    printf("\n邻接矩阵（行表示出发城市，列表示到达城市）：\n");
    printf("INF表示没有直接道路，对角线为0。\n%12s", "");
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
    printf("当前距离：");
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
    // 从终点沿前驱回溯，再倒序输出
    for (int current = end; current != -1; current = previous[current])
        path[count++] = current;
    printf("最短路径：");
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
    printf("\n---------- Dijkstra计算过程 ----------\n");
    PrintDistance(graph, distance);
    for (int step = 1; step <= graph->n; step++)
    {
        int u = -1;
        // 从未确定的城市中选择当前距离最小的一个
        for (int i = 0; i < graph->n; i++)
            if (!visited[i] && distance[i] < INF &&
                (u == -1 || distance[i] < distance[u]))
                u = i;
        if (u == -1)
            break; // 剩下的城市均不可达
        visited[u] = 1;
        printf("第%d轮：确认城市%c，最短距离为%lld。\n",
               step, graph->city[u], distance[u]);
        if (u == end)
            break; // 终点的最短距离已经确定
        for (int v = 0; v < graph->n; v++)
        {
            if (visited[v] || graph->edge[u][v] == INF)
                continue;
            long long candidate = distance[u] + graph->edge[u][v];
            if (candidate < distance[v])
            {
                printf("更新%c：%lld + %lld = %lld，原距离",
                       graph->city[v], distance[u], graph->edge[u][v], candidate);
                if (distance[v] == INF)
                    printf("INF");
                else
                    printf("%lld", distance[v]);
                printf("，前驱改为%c。\n", graph->city[u]);
                distance[v] = candidate;
                previous[v] = u;
            }
        }
        PrintDistance(graph, distance);
    }
    printf("---------- 查询结果 ----------\n");
    if (distance[end] == INF)
    {
        printf("城市%c无法到达城市%c。\n", graph->city[start], graph->city[end]);
        printf("最短路径：不存在\n");
    }
    else
    {
        printf("最短路径长度：%lld\n", distance[end]);
        PrintPath(graph, previous, end);
    }
}

int main(void)
{
    Graph graph;
    int choice, start, end;
    printf("========== 最短路径求解 ==========\n");
    printf("采用有向图和Dijkstra算法，道路长度不能为负。\n");
    printf("输入顺序：n m、n个城市名、m条道路、查询起点和终点。\n");
    printf("城市名用单个英文字母或其他单字节非空白字符，区分大小写。\n");
    printf("例如：3 3 / A B C / A B 1 / B C 1 / C A 3 / A C\n");
    printf("上例中的斜线表示换行，不需要输入。\n");
    printf("开始请输入1，退出请输入0：");
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
            printf("选择有误，请输入1或0。\n");
        printf("\n继续请输入1，退出请输入0：");
    }
    printf("程序已退出。\n");
    return 0;
}
