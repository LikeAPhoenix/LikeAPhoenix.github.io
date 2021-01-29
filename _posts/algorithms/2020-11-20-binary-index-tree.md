---
layout:     post
title:      "树状数组"
subtitle:   "单点修改和区间查询，时间复杂度均为Ologn"
date:       2020-11-20 23:07:37
author:     "XDong"
header-img: "img/post-bg-wlop-2880x1800.jpg"
tags:
    - 算法
---


# 树状数组

树状数组（Binary Index Tree, BIT）也是很多OIer心中最简洁优美的数据结构之一。最简单的树状数组支持两种操作，时间复杂度均为 ***O(logn)***

- **单点修改** 更改数组中一个元素的值
- **区间查询** 查询一个区间内所有元素的和

## 引入

实现 **单点修改** **区间查询** 的方法有多种

- 普通数组，单点修改为 ***O(1)*** ，区间求和为 ***O(n)***
- 前缀和，单点修改为 ***O(n)*** ，区间求和为 ***O(1)***

![前缀和](/img/algorithms/partial-sum.png)

但是程序的运行时间，是由最慢的步骤决定的

关于数组的维护，有个很自然的想法：可以用一个数组维护若干个小区间，单点修改时，只更新包含这一元素的区间；求前n项和时，通过将区间进行组合，得到从1到n的区间，然后对所有用到的区间求和。

树状数组这种结构非常合适，它的单点修改和区间求和为 ***O(logn)***

![树状数组](/img/algorithms/binary-index-tree-1.jpg)

$C1 = A1$  
$C2 = A2 + C1 == A2 + A1$  
$C3 = A3$  
$C4 = A4 + C3 + C2 = A4 + A3 + A2 + A1$  
$C5 = A5$  
$C6 = A6 + C5 = A6 + A5$  
$C7 = A7$  
$C8 = A8 + C7 + C6 + C4 = A8 + A7 + A6 + A5 + A4 + A3 + A2 + A1$  

我们定义，二进制数最右边的一个1，连带着它之后的0为 **lowbit(x)**。那么我们用 **Ci** 维护区间 **(Ai - lowbit(x), Ai)**

## 实现

### 区间维护长度lowbit(x)

例如 **lowbit(74)** 和 **lowbit(40)**

![x & (-x)](/img/algorithms/binary-index-tree-2.png)

$lowbit(74) = lowbit(2) = 10B = 2$  
$C2 = C1 + A2 = A1 + A2$  

$lowbit(40) = lowbit(8) = 1000B = 8$  
$C8 = A8 + C7 + C6 + C4 = A8 + A7 + A6 + A5 + A4 + A3 + A2 + A1$  

```cpp
int lowbit(int x) {  // 返回末尾最后一个1和后面的0
  return x & (-x);  // 即返回2^k
}
```

### 更新

```cpp
void add(int x, int y) { // 树状数组的+操作，将x位置上的数+y
  for (int i = x; i <= n; i += lowbit(i)) {
    tr[i] += y;
  }
}
```

### 求前缀和

```cpp
int get_sum(int x) {
  int res = 0;
  for (int i = x; i > 0; i -= lowbit(i)) {
    res += tr[i];
  }
  return res;
}
```

### 完整模板

```cpp
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
int a[N], tr[N];  // tr[]数组为树状数组
int n, m;

int lowbit(int x) {  // 返回末尾最后一个1和后面的0
  return x & (-x);  // 即返回2^k
}

void add(int x, int y) { // 树状数组的+操作，将x位置上的数+y
  for (int i = x; i <= n; i += lowbit(i)) {
    tr[i] += y;
  }
}

int get_sum(int x) {
  int res = 0;
  for (int i = x; i > 0; i -= lowbit(i)) {
    res += tr[i];
  }
  return res;
}
```

## [动态求连续区间和](https://www.acwing.com/problem/content/1266/)

解析：模板题

代码

```cpp
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
int a[N], tr[N];  // tr[]数组为树状数组
int n, m;

int lowbit(int x) {  // 返回末尾最后一个1和后面的0
  return x & (-x);  // 即返回2^k
}

void add(int x, int y) { // 树状数组的+操作，将x位置上的数+y
  for (int i = x; i <= n; i += lowbit(i)) {
    tr[i] += y;
  }
}

int get_sum(int x) {
  int res = 0;
  for (int i = x; i > 0; i -= lowbit(i)) {
    res += tr[i];
  }
  return res;
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    add(i, a[i]);
  }
  while (m--) {
    int k, x, y;
    cin >> k >> x >> y;
    if (k == 1) {
      add(x, y);
    } else if (k == 0) {
      cout << get_sum(y) - get_sum(x - 1) << endl;
    }
  }
  return 0;
}
```

## 参考链接

- [算法学习笔记(2) : 树状数组](https://zhuanlan.zhihu.com/p/93795692)
- [pdf](/pdf/10.1.pdf)
