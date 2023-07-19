#include <cstdio>
#include <cstring>
#include <algorithm>

const int MaxVertexNum = 1e6 + 10;
const int MaxEdgeNum = 2e6 + 10;

struct edge
{
    int x, y;
    int weight;
    // if the graph is unweighted, then just ignore it or set it to a constant
    // 边无权可以直接删去或者，将其设定为固定常数即可
    bool operator<(const edge &compare) const
    {
        return weight < compare.weight;
    }
} edges[MaxEdgeNum];
int cntEs = 0;
void GraphInit(int n)
// 初始化入口
{
    cntEs = 0;
    return;
}
void AddEdge(int x, int y, int weight)
// Add a undirected edge which is between x and y with weight of "weight"
// 图中加一条由 x 与 y 之间的权为 weight 的无向边
{
    edges[cntEs].x = x;
    edges[cntEs].y = y;
    edges[cntEs].weight = weight;
    cntEs++;
    return;
}

//-------------------------以上为基础的建图部分------------------------//
//------------------(undirected-edges-pool-version)------------------//

//---------------------以下实现了一个基础并查集-----------------------//
/*  其中注释掉的部分实现的是按权合并的启发式算法，可将运行时间进一步变快        */

const int MaxElementNum = 1e6 + 10;
int SetsPool[MaxElementNum], NumOfSets = 0;
/*      //This is for "join by ranks"
            int SetsRank[MaxElementNum];            */
void DisjointSetInit(int n)
{
    NumOfSets = n;
    for (int i = 1; i <= n; i++)
    {
        SetsPool[i] = i;
        /*  //This is for "join by ranks"
            SetsRank[i] = 1;            */
    }
    return;
}
int Find(int x)
{
    return SetsPool[x] == x ? x : (SetsPool[x] = Find(SetsPool[x]));
}
void Join(int x, int y)
{
    if (Find(x) == Find(y))
        return;
    /*  //This is for "join by ranks"
        if (SetsRank[Find(x)] > SetsRank[Find(y)])
            SetsPool[Find(y)] = Find(x);
        else                                            */
    SetsPool[Find(x)] = Find(y);
    NumOfSets--;
    return;
}

//-------------------------Kruskal-Algorithm-----------------------//
/*  必要时需要用long long型储存因为权值和大后有可能会溢出, 返回类型可以根据具体情况具体判断 */
long long KruskalMST(int VertexNum, int EdgesNum, edge *EdgesPool)
{
    long long WeightSum = 0;
    DisjointSetInit(VertexNum);
    std::sort(EdgesPool, EdgesPool + EdgesNum);

    for (int i = 0; i < EdgesNum; i++)
    {
        // 如有可能有负权边，直接将负权全部加入即可
        if (Find(EdgesPool[i].x) != Find(EdgesPool[i].y) || EdgesPool[i].weight <= 0)
        {
            Join(EdgesPool[i].x, EdgesPool[i].y);
            WeightSum += EdgesPool[i].weight;
        }
        // 在有负权边的情况下，不一定找到的便是MST，因为负权要全部加入，因此需要再加上后边的判断
        if (NumOfSets == 1 && EdgesPool[i].weight > 0)
            break;
    }

    return WeightSum;
}

int main(void)
{
    int n = 0, m = 0;
    scanf("%d %d", &n, &m);

    GraphInit(n);

    int x = 0, y = 0, weight = 0;
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &x, &y, &weight);
        AddEdge(x, y, weight);
        // we can also directly do as follows:
        //  scanf("%d %d %d", &edges[i].from, &edges[i].to, &edges[i].weight);
    }

    long long Ans = KruskalMST(n, m, edges);
    if (NumOfSets == 1)
        printf("%lld\n", Ans);
    else
        printf("There is no spanning tree for the given graph.\n");
    return 0;
}