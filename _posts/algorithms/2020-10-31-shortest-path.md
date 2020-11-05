---
layout:     post
title:      "图的最短路"
subtitle:   "CF-Round-G"
date:       2020-10-31 19:45:42
author:     "XDong"
header-img: "img/post-bg-wlop-2880x1800.jpg"
tags:
    - 算法
---


# 图的最短路

>最短路径问题的抽象

>1. 在网络中，求两个不同顶点之间的所有路径中，边的权值之和最小的那一条路径
>2. 这条路径就是两点之间的最短路径(Shortest Path)
>3. 第一个顶点为源点(Source)
>4. 最后一个顶点为终点(Destination)

- [图的最短路](#图的最短路)
  - [单源最短路](#单源最短路)
    - [无权图](#无权图)
    - [有权图](#有权图)
  - [多源最短路](#多源最短路)
    - [单源最短路算法](#单源最短路算法)
    - [Floyd算法](#floyd算法)
  - [G. Reducing Delivery Cost](#g-reducing-delivery-cost)
  - [P1119 灾后重建](#p1119-灾后重建)
  - [参考链接](#参考链接)

## 单源最短路

>单源最短路径问题：从某固定源点出发，求其到所有其他顶点的最短路径

>1. (有向)无权图
>2. (有向)有权图


### 无权图

按照递增（非递减）的顺序找出到各个顶点的最短路,即BFS

```cpp
#include <iostream>
#include <queue>
using namespace std;
int matrix[1000][1000];
int dist[1000];
int path[1000];
void unweighted(int S) {
  queue<int> q;
  q.push(S);
  while(!q.empty()) {
    int V = q.front();
    q.pop();
    for (int i = 0; i < 1000; i++) {
      if (matrix[V][i] && dist[i] == -1) {
        dist[i] = dist[V] + 1;
        path[i] = V;
        q.push(i); 
      }
    }
  }
}
```

### 有权图

按照递增的顺序找出到各个顶点的最短路,即Dijkstra算法

```cpp
// PTA Emergency
#include <cstring>
#include <iostream>
using namespace std;
const int INF = 0x3f3f3f3f;
int map[5005][5005];
int dist[5005], path[5005];  // 最短路径  上一个必经城市
int team[5005], gather_team[5005], road[5005];  // 医疗队数量  聚集医疗队数量  最短路径数量
bool collected[5005];
int N, M, C1, C2;

int min_dist() {
  int min = INF;
  int index = -1;
  for (int i = 0; i < N; i++) {
    if (!collected[i] && min > dist[i]) {
      min = dist[i];
      index = i;
    }
  }
  return index;
}

void init() {
  memset(dist, 0x3f, sizeof(dist));
  for (int i = 0; i < N; i++) {
    path[i] = -1;
  }
  return;
}

void dijkstra(int sour, int desti) {
  init();
  dist[sour] = 0;
  gather_team[sour] = team[sour];
  road[sour] = 1;
  while (1) {
    int v = min_dist();
    if (v == -1) {
      break;
    }
    // cout << "v:" << v << " " << "dist:" << dist[v] << endl;
    collected[v] = true;
    for (int i = 0; i < N; i++) {
      if (map[v][i] && !collected[i]) {
          if (dist[v] + map[v][i] == dist[i]) {  // 长度相等 添加最短路径数量和医疗队数量
            road[i] += road[v];  
            if (gather_team[v] + team[i] > gather_team[i]) {
              gather_team[i] = gather_team[v] + team[i];
            }
          } else if (dist[v] + map[v][i] < dist[i]) {  // 更新最短路径和医疗队数量
            dist[i] = dist[v] + map[v][i];
            path[i] = v;
            road[i] = road[v];
            gather_team[i] = gather_team[v] + team[i];
          }
      }
    }
  }
}

int main() {
  cin >> N >> M >> C1 >> C2;
  init();
  int x, y, w;
  for (int i = 0; i < N; i++) {
    cin >> team[i];
  }
  for (int i = 0; i < M; i++) {
    cin >> x >> y >> w;
    map[x][y] = w;
    map[y][x] = w;
  }
  dijkstra(C1, C2);
  cout << road[C2] << " " << gather_team[C2];
  return 0;
}
```

## 多源最短路

>求任意两顶点间的最短路径

>1. 直接将单源最短路算法调用V遍
>2. Floyd算法

### [单源最短路算法](#有权图)

### Floyd算法

![](/img/algorithms/floyd.jpg)

```cpp
void floyd() {
  for (int i = 0; i < N; i++) {  // 自回路权重为0，没有直接路径为INF
    for (int j = 0; j < N; j++) {
      dist[i][j] = map[i][j];
    }
  }
  for (int k = 0; k < N; i++) {  // 以k为中间路径
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }
}
```

## [G. Reducing Delivery Cost](https://codeforces.com/contest/1433/problem/G)

You are a mayor of Berlyatov. There are n districts and m two-way roads between them. The i-th road connects districts xi and yi. The cost of travelling along this road is wi. There is some path between each pair of districts, so the city is connected.

There are k delivery routes in Berlyatov. The i-th route is going from the district ai to the district bi. There is one courier on each route and the courier will always choose the cheapest (minimum by total cost) path from the district ai to the district bi to deliver products.

The route can go from the district to itself, some couriers routes can coincide (and you have to count them independently).

You can make at most one road to have cost zero (i.e. you choose at most one road and change its cost with 0).

Let d(x,y) be the cheapest cost of travel between districts x and y.

Your task is to find the minimum total courier routes cost you can achieve, if you optimally select the some road and change its cost with 0. In other words, you have to find the minimum possible value of ∑i=1kd(ai,bi) after applying the operation described above optimally.

Input
The first line of the input contains three integers n, m and k (2≤n≤1000; n−1≤m≤min(1000,n(n−1)2); 1≤k≤1000) — the number of districts, the number of roads and the number of courier routes.

The next m lines describe roads. The i-th road is given as three integers xi, yi and wi (1≤xi,yi≤n; xi≠yi; 1≤wi≤1000), where xi and yi are districts the i-th road connects and wi is its cost. It is guaranteed that there is some path between each pair of districts, so the city is connected. It is also guaranteed that there is at most one road between each pair of districts.

The next k lines describe courier routes. The i-th route is given as two integers ai and bi (1≤ai,bi≤n) — the districts of the i-th route. The route can go from the district to itself, some couriers routes can coincide (and you have to count them independently).

Output
Print one integer — the minimum total courier routes cost you can achieve (i.e. the minimum value ∑i=1kd(ai,bi), where d(x,y) is the cheapest cost of travel between districts x and y) if you can make some (at most one) road cost zero.

中文大意:可以选择一条道路并更改其成本0,求所有快递路线的成本之和最小值

解析:有多个起点和终点,为多源最短路问题,用Dijkstra算法求每个起点到其他顶点的最短路,再枚举每条边的权值被改为0,记录最小值

```cpp
  for (auto i : edges) {  // 枚举每条边的权值被改为0
    int a = i.first;
    int b = i.second;
    int ans = 0;
    for (auto j : route) {  // 求和
      ans += min(res[j.first][j.second], 
      min(res[j.first][a] + res[j.second][b],
      res[j.first][b] + res[j.second][a]));
    }
    sum = min(sum, ans);
  }
```

```cpp
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int MAXSIZE = 1005;
int n, m, k;
int dist[MAXSIZE];          // 最短路径
bool collected[MAXSIZE];    // x到y的y是否收集
int res[MAXSIZE][MAXSIZE];  // 存储结果
typedef pair<int, int> P;   // 距离 编号
struct Edge {
  int to;
  int cost;
};
struct Edge edges[MAXSIZE];
vector<Edge> map[MAXSIZE];  // 有权图

void dijkstra(int start) {
  memset(dist, 0x3f, sizeof(dist));
  memset(collected, 0, sizeof(collected));
  dist[start] = 0;
  priority_queue<P, vector<P>, greater<P>> que;  // 相当于dist数组 second为下标
  que.push({0, start});
  while (!que.empty()) {
    P p = que.top();
    que.pop();
    int v = p.second;
    if (!collected[v]) {
      collected[v] = true;
      for (int i = 0; i < map[v].size(); i++) {
        Edge ed = map[v][i];
        if (!collected[ed.to]) {
          if (dist[v] + ed.cost < dist[ed.to]) {
            dist[ed.to] = dist[v] + ed.cost;
            que.push({dist[ed.to], ed.to});
          }
        }
      }
    }
  }
  for (int j = 1; j <= n; j++) {  // 记录最短路
    res[start][j] = dist[j];
    res[j][start] = dist[j];
  }
}

int main() {
  cin >> n >> m >> k;
  int x, y, w;
  vector<pair<int, int>> edges;
  for (int i = 0; i < m; i++) {  // 读入有权图
    cin >> x >> y >> w;
    map[x].push_back({y, w});  
    map[y].push_back({x, w});
    edges.push_back({x, y});  // 记录路径
  }
  vector<pair<int, int>> route;  // 记录道路
  for (int i = 0; i < k; i++) {
    cin >> x >> y;
    route.push_back({x, y});
  }
  for (int i = 1; i < n; i++) {  // dijkstra算法 算出每个点的单源最短路
    dijkstra(i);
  }

  int sum = INT_MAX;
  for (auto i : edges) {  // 枚举每条边的权值被改为0
    int a = i.first;
    int b = i.second;
    int ans = 0;
    for (auto j : route) {  // 求和
      ans += min(res[j.first][j.second], 
      min(res[j.first][a] + res[j.second][b],
      res[j.first][b] + res[j.second][a]));
    }
    sum = min(sum, ans);
  }
  cout << sum << endl;
  return 0;
}
```

## [P1119 灾后重建](https://www.luogu.com.cn/problem/P1119)

```cpp
#include <iostream>
#include <cstring>
using namespace std;
const int INF = 0x3f3f3f3f;
int N, M;
int map[205][205], times[205];

// 最短路径中的中间村庄k已经重建好了
void floyd(int k) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      map[i][j] = min(map[i][j], map[i][k] + map[k][j]);
    }
  }
} 

int main() {
  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    cin >> times[i];
  }
  memset(map, 0x3f, sizeof(map));  // 初始化
  for (int i = 0; i < N; i++) {
    map[i][i] = 0;
  }
  int x, y, w, t;
  for (int i = 0; i < M; i++) {
    cin >> x >> y >> w;
    map[x][y] = map[y][x] = w;
  }
  int Q, index = 0;
  cin >> Q;
  for (int i = 0; i < Q; i++) {
    cin >> x >> y >> t;
    while (times[index] <= t && index < N) {  // 模拟重建到询问的时间
      floyd(index);  // 只有到了重建时间，才会把该村庄加入
      index++;
    }
    if (times[x] > t || times[y] > t || map[x][y] == INF) {  
      cout << -1 << endl; // 两个端点村庄还没重建好或者不连通
    } else {
      cout << map[x][y] << endl;
    }
  }
  return 0;
}
```

## 参考链接

- [浙江大学-MOOC](https://www.icourse163.org/course/ZJU-93001)
- [MOOC-PDF](/pdf/7-1.pdf)