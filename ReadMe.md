# 算法集合实现

> Written by Bo Fu. From NJU.

- 这是一个对常见高效算法集合的实现与存储库。
- 主要使用C/CPP实现。
- 尽量保证了工程规范以提高可维护性和易读性。

目前已囊括算法（简介）如下。

## 排序算法

- WTD

> 排序问题是第一个被完全解决的算法问题，排序算法是所有算法的掌上明珠。

### 冒泡排序（Bubble Sort）

### 插入排序（Insertion Sort）

### 希尔排序（Shell Sort）

### 选择排序（Selection Sort）

### 快速排序（Quick Sort）

### 归并排序（Merge Sort）

### 堆排序（Heap Sort）

### 计数排序（Counting Sort）

### 桶排序（Bucket Sort）

### 基数排序（Radix Sort）

## 搜索算法

### 线性搜索（Linear Searching）

### 二分搜索（Binar Searching）

## 高精度/单精度

针对浮点数运算精度问题与大整数运算的溢出问题，可以使用字符串来表示一个数字，相应的基本运算便需要循环算法实现，已包含的实现有：

- 加法 - 减法
- 乘法 - 除法
- 阶乘
- GCD
- $\cdots$ WTD

## 数论算法

针对数论模运算，我们可以利用数论中的一些性质对运算加速，已包含的实现有：

- 快速幂算法（qmi/FastPow）
- $\cdots$ WTD

## 图论算法

针对图论中的许多经典问题，涌现出许多对其高效解决的算法，此库中已包含的实现有：

### 建图

- 邻接表建图 - 前向星链表
- 邻接矩阵建图 - 二维数组实现
- 点边分存策略（可用于Kruskal Algorithm）

### 图上遍历

- DFS(Depth First Searching)，深度优先搜索(WTD)
- BFS(Breath First Searching)，广度优先搜索(WTD)

### 最小生成树问题

MST(Minimal Spanning Tree) Problem

- Kruskal Algorithm
- Prim Algorithm
  - WTD

### 拓扑排序算法

针对于DAG(Directed Acyclic Graphs)的拓扑排序算法实现。

### 连通分量

- WTD

主要用于无向图

- Union-Find Set 

  并查集 + BFS/DFS(直接搜边) 实现

### 强（双）连通分量

- Tarjan Algorithm

### 最短路径问题

- WTD

- SSSP（Single Source Shortest Path）

  单源最短路径问题

  - Bellman-Ford Algorithm
  - Dijkstra Algirithm

- MSSP（Multi-Source Shortest Path）

  APSPA（All Pair Shortest Path Algorithm） 

  多源最短路径问题
  
  - Floyd Algorithm

### 二分图最大匹配问题

- Hungarian algorithm

  也即常言到的*匈牙利算法*。

### 网络流问题

- WTD

## 动态规划算法

动态规划是算法设计的十分重要的思想，它的可用性立足于**最优子结构**和**重叠子问题**两个性质，主要思路是将问题视作有关特定输入序列的映射，从而根据一定顺序动态生成不同输入的结果。有许多算法都用到了动态规划思想，例如MSSP中的Floyd算法就用到了这样的思想。此板块着眼于一些经典的可以用动态规划思想解决的问题，其中最主要的有最长公共子序列问题、背包问题等。

### 斐波那契数列求解（Fibonacci Number）

- WTD

###  最长公共子序列问题（LCS - Longest Common Subsequence）

- WTD

### 背包问题（Knappack Problem）

- WTD

可见经典的《背包九讲》。

#### 01背包

#### 完全背包问题

#### 多重背包

#### 分组背包

#### 条件背包

## 贪心算法

贪心算法是基于动态规划算法做出的进一步优化，能用贪心算法解决的问题具有动态规划算法应用所需的所有前提条件，同时因为**贪心选择**性质的加入，使得最优解中一定包含当下不完全条件中做出的最优解，因此将解决算法的复杂度进一步降低。同样以上算法中已经使用了贪心算法的思想，例如Kruskal算法和Prim算法。此板块着眼于贪心算法对于一些经典问题的求解，如哈夫曼编码等。

### 哈夫曼编码（Haffman Coding）

- WTD

### Activity Selection Problem

- WTD

## WTD $\cdots$