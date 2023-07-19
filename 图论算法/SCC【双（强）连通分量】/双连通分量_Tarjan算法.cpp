#include <cstdio>
#include <cstring>
#include <stack>

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

//-------------------------以下为Tarjan算法------------------------//
int dfn[MaxVertexNum], low[MaxVertexNum], total = 0;
bool vis[MaxVertexNum];
std::stack<int> tarMem;

void CleanVis(int n)
{
    memset(vis, false, n * sizeof(bool));
    return;
}
void Tarjan_Init(int n)
{
    memset(dfn + 1, 0, n * sizeof(int));//1表示起始坐标
    memset(low + 1, 0, n * sizeof(int));//1表示起始坐标
    CleanVis(n);
    return;
}

void TarjanOn(int x)
{
    dfn[x] = low[x] = ++total;
    tarMem.push(x);
    vis[x] = true;
    for (int i = VectorStart[x]; i; i = edges[i].next)
    {
        int vto = edges[i].to;
        if (dfn[vto] == 0) {// unvisited 
            TarjanOn(vto);
            low[x] = std::min(low[x], low[vto]);
        }
        else if (vis[vto]) {
            low[x] = std::min(low[x], dfn[vto]);
        }
    }
    if (low[x] == dfn[x]) // isroot
    {
        //int cyclenum = 0; // the number of nodes in a cycle
        //  the nodes in the cycle are from x to tarMem.top()
        //  从 x 到 tarMem.top() 为一个强连通分量
        //  you can do whatever you want to the nodes in the cycle
        while (x != tarMem.top()) {
            //cyclenum++;
            vis[tarMem.top()] = false;
            low[tarMem.top()] = low[x];
            tarMem.pop();
        }
        vis[tarMem.top()] = false;
        tarMem.pop(); // pop x
    }
    return;
}
void Tarjan(int n)
{
    Tarjan_Init(n);
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0)
            TarjanOn(i);
    return;
}


int main(void)
{
    return 0;
}
