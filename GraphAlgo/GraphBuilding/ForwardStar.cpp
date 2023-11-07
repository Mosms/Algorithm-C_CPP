#include <cstdio>
#include <cstring>

const int MaxVertexNum = 1e5;
const int MaxEdgeNum = 1e4;

struct edge_node
{
    int next, to;
    int weight;
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
void AddEdge(int x, int y, int weight)
// Add a directed edge which is from x and pointed to y with weight of weight
// 图中加一条由 x 指向 y 的权为 weight 的有向边
{
    edges[++cntEs].next = VectorStart[x];
    edges[cntEs].to = y;
    edges[cntEs].weight = weight;
    VectorStart[x] = cntEs;
}

int main(void)
{
    return 0;
}
