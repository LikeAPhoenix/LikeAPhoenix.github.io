---
layout:     post
title:      "并查集"
subtitle:   "Disjoint Set Union"
date:       2020-11-04 19:21:00
author:     "XDong"
header-img: "img/post-bg-wlop-2880x1800.jpg"
tags:
    - 算法
    - 并查集
---


# 并查集
并查集是一种树形的数据结构,顾名思义,它用于处理一些不交集的合并及查询问题.   
它支持两种操作:    
- 查找(Find):确定某个元素处于哪个子集    
- 合并(Union):将两个子集合并成一个集合    

## 初始化
```cpp
void init(int n) {
  for (int i = 1; i <= n; i++) {
    fa[i] = 1;  // 默认父节点为自己
  }
}
```

用fa数组来存储元素的父节点,默认父节点为自己

## 查询
```cpp
int find(int x) {
  if (fa[x] == x) {
    return x;
  } else {
    find(fa[x]);
  }
}
```

用递归的方式来查询根节点,当父节点为本身的时候,即为根节点.要判断两个元素是否属于同一个集合,只需要看它们的根节点是否相同即可.

## 合并
```cpp
void merge(int i, int j) {  // 将i并向j
  fa[find(i)] = find(j);
}
```

找到两者的根节点,再把前者根节点的根节点设为后者的根节点即可

## 优化Ⅰ 考虑高度的初始化和合并
- 对于每棵树,记录这棵树的高度(rank)
- 合并时假如两颗树的rank不同,那么从rank小的向大的连边
![](/img/algorithms/dsu-1.jpg)
![](/img/algorithms/dsu-2.jpg)

```cpp
void init(int n) {  // 初始化
  for (int i = 1; i <= n; i++) {
    fa[i] = i;
    rk[i] = 1;
  }
}

void merge(int i, int j) {  // 合并
  int x = find(i);
  int y = find(j);
  if (rank[x] <= rank[y]) {
    fa[x] = y;
  } else {
    fa[y] = x;
  }
  if (rank[x] == rank[y] && x != y) {
    rk[y]++;
  }
}
```

## 优化Ⅱ 路径压缩
在查询的过程中,把沿途的每个节点的父节点都设为根节点即可    
![](/img/algorithms/dsu-3.png)
![](/img/algorithms/dsu-4.png)

```cpp
int find(int x) {
  if (x == fa[x]) {
    return x;
  } else {
    fa[x] = find(fa[x]);
    return fa[x];
  }
}
```

通常可以写为一行
```cpp
int find(int x) {
  return x == fa[x] ? x : (fa[x] = find(fa[x]));
}
```

也可以用循环实现
```cpp
int find(int x) {  
  while (x != fa[x]) x = fa[x] == fa[fa[x]];
  return x;
}
```

## 优化后的模板
```cpp
int fa[MAXN], rk[MAXN];  // rank代表深度
void init(int n) {
  for (int i = 1; i <= n; i++) {
    fa[i] = i;
    rk[i] = 1;
  }
}
int find(int x) {
  /* 循环实现
  while (x != fa[x]) x = fa[x] == fa[fa[x]];
  return x;
  */
  return x == fa[x] ? x : (fa[x] = find(fa[x]));
}
void merge(int i, int j) {
  int x = find(i);
  int y = find(j);
  if (rk[x] <= rk[y]) {
    fa[x] = y;
  } else {
    fa[y] = x;
  }
  if (rk[x] == rk[y] && x != y) {
    rk[y]++;
  }
}
```

## 注意事项

- 记得在main函数中调用init函数进行初始化
- 访问一个节点的根节点时用find函数，因为集合关系可能已经更新了，如进行了merge操作，但是fa[i]记录的还是以前的根节点

## [PTA:File Transfer](https://pintia.cn/problem-sets/1302953266564911104/problems/1315322294215434241)
We have a network of computers and a list of bi-directional connections. Each of these connections allows a file transfer from one computer to another. Is it possible to send a file from any computer on the network to any other?

Input Specification:
Each input file contains one test case. For each test case, the first line contains N (2≤N≤10^4), the total number of computers in a network. Each computer in the network is then represented by a positive integer between 1 and N. Then in the following lines, the input is given in the format:

>I c1 c2  

where I stands for inputting a connection between c1 and c2; or

>C c1 c2  

where C stands for checking if it is possible to transfer files between c1 and c2; or

>S  

where S stands for stopping this case.

Output Specification:
For each C case, print in one line the word "yes" or "no" if it is possible or impossible to transfer files between c1 and c2, respectively. At the end of each case, print in one line "The network is connected." if there is a path between any pair of computers; or "There are k components." where k is the number of connected components in this network.

中文大意:问两台计算机之间能否传输文件

解析:使用并查集即可

代码

```cpp
#include <iostream>
using namespace std;
const int MAXN = 10005;
int fa[MAXN], rk[MAXN];  // rank代表深度
void init(int n) {
  for (int i = 1; i <= n; i++) {
    fa[i] = i;
    rk[i] = 1;
  }
}
int find(int x) {
  return x == fa[x] ? x : (fa[x] = find(fa[x]));
}
void merge(int i, int j) {
  int x = find(i);
  int y = find(j);
  if (rk[x] <= rk[y]) {
    fa[x] = y;
  } else {
    fa[y] = x;
  }
  if (rk[x] == rk[y] && x != y) {
    rk[y]++;
  }
}
int main() {
  int total, x, y;
  cin >> total;
  init(total);
  char opt;
  while (cin >> opt && opt != 'S') {
    cin >> x >> y;
    if (opt == 'C') {
      if (find(x) == find(y)) {
        cout << "yes" << endl;
      } else {
        cout << "no" << endl;
      }
    } else if (opt == 'I') {
      merge(x, y);
    }
  }
  int com = 0;
  for (int i = 1; i <= total; i++) {
    if (fa[i] == i) {
      com++;
    }
  }
  if (com == 1) {
    cout << "The network is connected." << endl;
  } else {
    cout << "There are " << com << " components." << endl;
  }
  return 0;
}
```

## 参考链接
- [算法学习笔记(1) : 并查集](https://zhuanlan.zhihu.com/p/93647900)