#include <cstdio>
#include <cstring>
#include <vector>

const int MaxVertexNum = 1e5;
const int MaxEdgeNum = 1e4;

std::vector<std::pair<int, int>> adjWeighted[MaxVertexNum];
std::vector<int> adj[MaxVertexNum];
int adjTop[MaxVertexNum];

void GraphInit(int n)
// Init the VectorStart so that we can use them to find the entrance
// 初始化入口
{
    memset(adjTop, 0, n * sizeof(int));
    return;
}
void AddEdge(int x, int y, int weight)
// Add a directed edge which is from x and pointed to y with weight of weight
// 图中加一条由 x 指向 y 的权为 weight 的有向边
{
    adjWeighted[x][adjTop[x]++] = std::make_pair(y, weight);
    return;
}
void AddEdge(int x, int y)
// Add a directed edge which is from x and pointed to y, without weight
// 图中加一条由 x 指向 y 的无权有向边
{
    adj[x][adjTop[x]++] = y;
    return;
}

int main(void)
{
    return 0;
}
