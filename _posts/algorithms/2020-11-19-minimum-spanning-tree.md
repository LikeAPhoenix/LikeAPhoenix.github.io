---
layout:     post
title:      "最小生成树"
subtitle:   "Prim算法 Kruskal算法"
date:       2020-11-19 21:04:53
author:     "XDong"
header-img: "img/post-bg-wlop-2880x1800.jpg"
tags:
    - 算法
    - 最小生成树
---


# 最小生成树

我们定义无向连通图的 **最小生成树** （Minimum Spanning Tree，MST）为边权和最小的生成树。

注意：只有连通图才有生成树，而对于非连通图，只存在生成森林。

## Kruskal 算法

Kruskal 算法是一种常见并且好写的最小生成树算法，由 Kruskal 发明。该算法的基本思想是从小到大加入边，是个贪心算法。

![Kruskal算法](/img/algorithms/mst-2.jpg)

算法虽简单，但需要相应的数据结构来支持……具体来说，维护一个森林，查询两个结点是否在同一棵树中，连接两棵树。

抽象一点地说，维护一堆 集合，查询两个元素是否属于同一集合，合并两个集合。

其中，查询两点是否连通和连接两点可以使用并查集维护。

如果使用优化后的排序算法，并且使用优化后的并查集，就可以得到时间复杂度为 ***O(ElogE)*** 的 Kruskal 算法。

模板

```cpp
void Kruskal() {
  for (int i = 1; i <= M; i++) {
    if (cnt == N - 1) break;
    int fx = find(ed[i].x);
    int fy = find(ed[i].y);
    if (fx != fy) {
      merge(fx, fy);
      sum += ed[i].w;
      cnt++;
    }
  }
}
```

## Prim 算法

Prim 算法是另一种常见并且好写的最小生成树算法。该算法的基本思想是从一个结点开始，不断加点（而不是 Kruskal 算法的加边）。

![Prim算法](/img/algorithms/mst-1.jpg)

具体来说，每次要选择距离最小的一个结点，以及用新的边更新其他结点的距离。

其实跟 Dijkstra 算法一样，每次找到距离最小的一个点，可以暴力找也可以用堆维护。

堆优化的方式类似 Dijkstra 的堆优化，但如果使用二叉堆等不支持 ***O(1)*** decrease-key 的堆，复杂度就不优于 Kruskal，常数也比 Kruskal 大。所以，一般情况下都使用 Kruskal 算法，在稠密图尤其是完全图上，暴力 Prim 的复杂度比 Kruskal 优，但 **不一定** 实际跑得更快。

```cpp
  // 开始随便取一个节点加入MST中
  for (int i = 1; i <= N; i++) dis[i] = map[1][i];
  
  vis[1] = true;
  
  int min, min_index;  // 最短的距离及其下标
  for (int i = 1; i < N; i++) {
    min = INF;  // 默认距离MST为最大值

    // 寻找离MST最近的节点
    for (int j = 1; j <= N; j++) {
      if (!vis[j] && dis[j] < min) {
        min = dis[j];  // 更新最短距离
        min_index = j;
      }
    }

    vis[min_index] = true;
    sum += dis[min_index];

    for (int j = 1; j <= N; j++) {
      if (!vis[j] && map[min_index][j] < dis[j]) {
        dis[j] = map[min_index][j];
      }
    }
  }
```

## [【模板】最小生成树](https://www.luogu.com.cn/problem/P3366)

思路：一道简单的模板题，不过Prim看了好久才明白（跟Dijkstra一样。。。）

### Prim算法（暴力）

```cpp
#include <iostream>
#include <cstring>
using namespace std;
const int INF = 0x3f3f3f3f;

bool vis[5005];
int dis[5005];
int map[5005][5005];

int main() {
  int N, M, sum;
  cin >> N >> M;
  
  // 初始化map
  memset(map, 0x3f, sizeof(map));
  for (int i = 1; i <= N; i++) map[i][i] = 0;

  // 读入边
  int x, y, z;
  for (int i = 1; i <= M; i++) {
    cin >> x >> y >> z;
    map[x][y] = min(map[x][y], z);
    map[y][x] = min(map[y][x], z);
  }

  // 开始随便取一个节点加入MST中
  for (int i = 1; i <= N; i++) dis[i] = map[1][i];
  
  vis[1] = true;
  
  int min, min_index;  // 最短的距离及其下标
  for (int i = 1; i < N; i++) {
    min = INF;  // 默认距离MST为最大值

    // 寻找离MST最近的节点
    for (int j = 1; j <= N; j++) {
      if (!vis[j] && dis[j] < min) {
        min = dis[j];  // 更新最短距离
        min_index = j;
      }
    }

    vis[min_index] = true;
    sum += dis[min_index];

    for (int j = 1; j <= N; j++) {
      if (!vis[j] && map[min_index][j] < dis[j]) {
        dis[j] = map[min_index][j];
      }
    }
  }

  cout << sum << endl;
}
```

### Kruskal算法（优化后的并查集）

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int INF = 0x3f3f3f3f;
int N, M, cnt = 0, sum = 0;

struct edge{
  int x;
  int y;
  int w;
}ed[200005];

bool cmp(const edge &a, const edge &b) {
  return a.w < b.w;
}

int fa[5005], rk[5005];
void init(int n) {
  for (int i = 1; i <= n; i++) {
    fa[i] = i;
    rk[i] = 1;
  }
}
int find(int x) {
  while (x != fa[x]) x = fa[x] = fa[fa[x]];
  return x;
  //return x == fa[x] ? x : (fa[x] = find(fa[x]));  // 递归实现
}
void merge(int i, int j) {
  int x = find(i);
  int y = find(j);
  if (rk[x] <= rk[y]) fa[x] = y;
  else fa[y] = x;
  if (rk[x] == rk[y] && x != y) rk[y]++;
}

void Kruskal() {
  for (int i = 1; i <= M; i++) {
    if (cnt == N - 1) break;
    int fx = find(ed[i].x);
    int fy = find(ed[i].y);
    if (fx != fy) {
      merge(fx, fy);
      sum += ed[i].w;
      cnt++;
    }
  }
}

int main() {
  cin >> N >> M;
  init(N);
  for (int i = 1; i <= M; i++) {
    cin >> ed[i].x >> ed[i].y >> ed[i].w;
  }
  sort(ed + 1, ed + 1 + M, cmp);
  Kruskal();
  cout << sum << endl;
}
```

## 参考链接

- [最小生成树](https://oi-wiki.org/graph/mst/)
- [浙江大学-MOOC](https://www.icourse163.org/course/ZJU-93001)
- [MOOC-PDF](/pdf/8-1.pdf)