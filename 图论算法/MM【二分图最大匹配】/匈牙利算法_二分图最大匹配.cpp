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

//-------------------------以上为基础的建图部分------------------------//

//-------------------------以下为匈牙利算法------------------------//

bool Visited[MaxVertexNum];
// Visited represents whether this vertex is visited in this round of trying to find a augmenting path
// Visited 表示该轮增广中x是否被访问
int MatchedVertex[MaxVertexNum];
// MatchedVertex represents the serial number of vertex that are neighboring to this
// 记录对应的匹配点
bool HungaryDFS(int x)
{
    for (int vcor = VectorStart[x]; vcor; vcor = edges[vcor].next)
    {
        int vertex = edges[vcor].to;

        if (Visited[vertex])
            continue;
        Visited[vertex] = true;

        // 如果 y 未被匹配：找到增广路
        // 如果 y 已被匹配：从vertex匹配的点出发去找增广路
        if (MatchedVertex[vertex] == -1 || HungaryDFS(MatchedVertex[vertex]))
        {
            MatchedVertex[vertex] = vertex;
            return true;
        }
    }
    return false;
}
int Hungary(int n)
{
    int BiggestMatchingNum = 0;
    memset(MatchedVertex, -1, (n + 1) * sizeof(int));
    for (int nowver = 1; nowver <= n; nowver++)
    // 假设左侧点标号为 1 \to n
    // or use a array to memory the corresponding serial number of one side vertices
    {
        memset(Visited, false, (n + 1) * sizeof(bool));
        BiggestMatchingNum += HungaryDFS(nowver);
    }
    return BiggestMatchingNum;
}

int main(void)
{
    return 0;
}