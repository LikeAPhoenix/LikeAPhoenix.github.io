---
layout:     post
title:      "二分搜索"
subtitle:   "《挑战程序设计竞赛》3.1章"
date:       2021-03-11 14:45:16
author:     "XDong"
header-img: "img/post-bg-wlop-2880x1800.jpg"
tags:
    - 算法
    - 二分搜索
---


# 二分搜索

二分搜索法，是不断缩小解可能存在的范围，从而求得最优解的方法

二分搜索要注意边界条件 **< <=** 等等

同时边界条件有多种表示方式，不用太过纠结如

- l, r都表示满足条件的值
- l表示满足条件的值，r表示不满足条件的值

## 3.1.1 从有序数组中查找某个值

![3.1.1](/img/algorithms/3.1.1.png)

```cpp
int binary_search(int l, int r, int key) {
  while (l < r) {
    int mid = (l + r) / 2;
    if (a[mid] < key) {
      l = mid + 1;
    } else {
      r = mid;
    }
  }
  if (a[l] == key) {
    return l;
  } else {
    return -1;
  }
}
```

## 3.1.2 假定一个解并判断是否可行

![3.1.2](/img/algorithms/3.1.2.png)

```cpp
#include <iostream>
#include <cmath>
using namespace std;
double a[10000 + 5];
int N, K;
bool fun(double x) {
  int num = 0;
  for (int i = 0; i < N; i++) {
    num += int(a[i] / x);
  }
  return num >= K;
}
int main() {
  cin >> N >> K;
  for (int i = 0; i < N; i++) {
    cin >> a[i];
  }
  double l = 0, r = 100000;
  for (int i = 0; i < 100; i++) {
    double mid = (l + r) / 2;
    if (fun(mid)) {
      l = mid;
    } else {
      r = mid;
    }
  }
  // double输出会自动四舍五入
  printf("%.2f", floor(l * 100) / 100);
  return 0;
}
```

## 3.1.3 最大化最小值

![3.1.3](/img/algorithms/3.1.3.png)

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int a[100000 + 5];
int N, M;
bool judge(int d) {
  int last = 0;  // 第一头牛默认放在0
  for (int i = 1; i < M; i++) {
    int cur = last + 1;
    while (cur < N && a[cur] - a[last] < d) {
      cur++;
    }
    if (cur == N) return false;
    last = cur;
  }
  return true;
}
int main() {
  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    cin >> a[i];
  }
  sort(a, a + N);
  int l = 0, r = INT_MAX;
  while (l < r) {
    int mid = (l + r) / 2;
    if (judge(mid)) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  if (judge(l)) {
    cout << l << endl;
  } else {
    cout << l - 1 << endl; 
  }

/*   int l = 0, r = INT_MAX;  // l是满足条件的距离，r是不满足条件的距离
  while (l + 1 < r) {
    int mid = (l + r) / 2;
    if (judge(mid)) {
      l = mid;
    } else {
      r = mid;
    }
  }
  cout << l << endl; */
  return 0;
}

```

## 3.1.4 最大化平均值

![3.1.4](/img/algorithms/3.1.4.png)

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e4 + 5;
int n, k;
int w[MAXN], v[MAXN];
double y[MAXN];
bool judge(double x) {
  for (int i = 0; i < n; i++) {
    y[i] = v[i] - w[i] * x;
  }
  sort(y, y + n, greater<double>());
  double sum = 0;
  for (int i = 0; i < k; i++) {
    sum += y[i];
  }
  return sum >= 0;
}
int main() {
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    cin >> w[i] >> v[i];
  }
  double l = 0, r = INT_MAX;
  for (int i = 0; i < 100; i++) {
    double mid = (l + r) / 2;
    if (judge(mid)) {
      l = mid;
    } else {
      r = mid;
    }
  }
  printf("%.2f", l);
  return 0;
}
```

## 参考链接

- [《挑战程序设计竞赛》](/pdf/挑战程序设计竞赛.pdf)