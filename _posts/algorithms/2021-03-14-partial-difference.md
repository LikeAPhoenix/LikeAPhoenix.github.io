---
layout:     post
title:      "前缀和、差分"
subtitle:   "及不同区间操作比较"
date:       2021-03-14 00:40:37
author:     "XDong"
header-img: "img/post-bg-eva-q-asuka-1920x1200.png"
tags:
    - 算法
---


# 前缀和、差分

## 前缀和

前缀和是一种重要的预处理，能大大降低查询的时间复杂度。可以简单理解为“数列的前n项的和”

- 区间求和复杂度为$O(1)$

```cpp
a[i]: 1  2  3  4  5  //原始数组
b[i]: 1  3  6  10 15 // 前缀和数组
```

代码：

```cpp
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    b[i] = a[i] + a[i - 1];
  }
```

### 二维前缀和

$sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + a[i][j]$

### [最大子序和](https://www.acwing.com/problem/content/137/)

代码：
```cpp
#include <cstring>
#include <iostream>
using namespace std;

int sum[int(3e5 + 5)];
int main() {
  int n, m, num, res = 0;
  memset(sum, 0, sizeof(sum));
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> num;
    sum[i] = sum[i - 1] + num;
    for (int j = 1; j <= m; j++) {
      if (i >= j) {
        res = max(res, sum[i] - sum[i - j]);
      }
    }
  }
  cout << res << endl;
  return 0;
}
```

## 差分

差分是一种和前缀和相对的策略，可以当做是求和的逆运算，指的就是当前值与前一个值的差值

- 区间加减复杂度为$O(1)$

```cpp
a[i]: 1  2  3  4  5  //原始数组
b[i]: 1  1  1  1  1  //差分数组
```

代码：

```cpp
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    b[i] = a[i] - a[i - 1];
  }
```

### 一维差分加减

```cpp
void insert(int l, int r, int c) {
  b[l] += c;
  b[r + 1] -= c;
}
```

### 二维差分加减

$b[i][j] = a[i][j] - a[i - 1][j] - a[i][j - 1] + a[i - 1][j - 1]$

```cpp
void insert(int x1, int y1, int x2, int y2, int c) {
  b[x1][y1] += c;
  b[x1][y2 + 1] -= c;
  b[x2 + 1][y1] -= c;
  b[x2 + 1][y2 + 1] += c; 
}
```

### [差分](https://www.acwing.com/problem/content/799/)

代码：

```cpp
#include <bits/stdc++.h>
#define IO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

const int MAXN = 1e5 + 5;
int a[MAXN], b[MAXN];

void insert(int l, int r, int c) {
  b[l] += c;
  b[r + 1] -= c;
}

int main() {
  IO;
  int n, m;
  cin >> n >> m;
  for (int i = 1; i<= n; i++) {
    cin >> a[i];
    b[i] = a[i] - a[i - 1];
  }
  for (int i = 1; i <= m; i++) {
    int l, r, n;
    cin >> l >> r >> n;
    insert(l, r, n);
  }
  int res = 0;
  for (int i = 1; i <= n; i++) {
    res += b[i];
    cout << res << " ";
  }
  return 0;
}
```

## 不同区间操作总结分析

### 前缀和

- 区间求和$O(1)$
- 单点修改$O(n)$

### 差分

- 区间修改$O(1)$
- 单点查询$O(n)$

### [树状数组](https://xdong.site/2020/11/20/binary-index-tree/)

- 单点修改$O(logn)$
- 区间修改$O(logn)$
- 单点查询$O(logn)$
- 区间求和$O(logn)$

### [线段树（树状数组拓展版）](https://xdong.site/2020/11/15/segment-tree/)

- 单点修改$O(logn)$
- 区间修改$O(logn)$
- 单点查询$O(logn)$
- 区间求和$O(logn)$
- 区间最大值$O(logn)$
- 区间最小值$O(logn)$

## 参考链接

- [10-3.pdf](/pdf/10.3.pdf)
- [oi-wiki](https://oi-wiki.org/)