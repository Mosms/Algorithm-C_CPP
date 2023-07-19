#include <cstdio>
#include <cstring>
#include <queue>
#include <cassert>

const int MaxVertexNum = 1e5;
const int MaxEdgeNum = 1e4;

struct edge_node
{
    int next, to;
    // int weight;
    // if the graph is unweighted, then just ignore it or set it to a constant
    // 边无权可以直接删去或者，将其设定为固定常数即可
} edges[MaxEdgeNum];
int VectorStart[MaxVertexNum], cntEs = 0;
void GraphInit(int n)
// Init the VectorStart so that we can use them to find the entrance
// 初始化入口
{
    memset(VectorStart + 1, 0, n * sizeof(int));//注意这里1为起始坐标
    return;
}
void AddEdge(int x, int y) //, int weight)
// Add a directed edge which is from x and pointed to y with weight of weight
// 图中加一条由 x 指向 y 的权为 weight 的有向边
{
    edges[++cntEs].next = VectorStart[x];
    edges[cntEs].to = y;
    // edges[cntEs].weight = weight;
    VectorStart[x] = cntEs;
}

//-------------------------以上为基础的建图部分------------------------//

int indegree[MaxVertexNum];
std::queue<int> ZeroDegreeVertices;
int TopologicalOrder[MaxVertexNum];

void Init(int n)
{
    for (int i = 0; i <= n; i++)
    {
        VectorStart[i] = 0;
        indegree[i] = 0;
    }
    return;
}
void New_AddEdge(int x, int y)
{
    AddEdge(x, y);
    indegree[y]++;
}
void TopologicalSort(int n)
{
    for (int i = 1; i <= n; ++i)
        if (indegree[i] == 0)
            ZeroDegreeVertices.push(i);

    int cnt = n;
    while (!ZeroDegreeVertices.empty())
    {
        int nowvertex = ZeroDegreeVertices.front();
        ZeroDegreeVertices.pop();

        TopologicalOrder[cnt--] = nowvertex;

        for (int i = VectorStart[nowvertex]; i; i = edges[i].next)
            if ((--indegree[edges[i].to]) == 0)
                ZeroDegreeVertices.push(edges[i].to);
    }
    assert(cnt == 0);
}
int main(void)
{
    int n = 0, m = 0;
    int one = 0, ano = 0;
    int ans = 0;
    scanf("%d %d", &n, &m);
    Init(n);
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d", &one, &ano);
        New_AddEdge(one, ano);
    }

    TopologicalSort(n);

    for (int i = 1; i <= n; i++)
        printf("%d\n", TopologicalOrder[i]);
    return 0;
}