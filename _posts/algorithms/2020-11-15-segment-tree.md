---
layout:     post
title:      "线段树"
subtitle:   "线段树的模板及几道例题"
date:       2020-11-15 22:53:29
author:     "XDong"
header-img: "img/post-bg-wlop.jpg"
tags:
    - 算法
    - 线段树
---


# 线段树

线段树是算法竞赛中常用的用来维护 **区间信息** 的数据结构。

线段树可以在 ***O(logN)*** 的时间复杂度内实现单点修改、区间修改、区间查询（区间求和，求区间最大值，求区间最小值）等操作。

线段树维护的信息，需要满足可加性，即能以可以接受的速度合并信息和修改信息，包括在使用懒惰标记时，标记也要满足可加性（例如取模就不满足可加性，对 **4** 取模然后对 **3** 取模，两个操作就不能合并在一起做）。

## 线段树的建立

线段树是一棵 **平衡二叉树** 。母结点代表整个区间的和，越往下区间越小。注意，线段树的每个节点都对应一条线段（区间），但并不保证所有的 **线段（区间）** 都是线段树的节点，这两者应当区分开。

如果有一个数组[1,2,3,4,5]，那么它对应的线段树大概长这个样子：

![线段树的建立](/img/algorithms/segment-tree-1.jpg)

```cpp
void build(ll l = 1, ll r = n, ll p = 1) {
  if (l == r) {
    tree[p] = arr[l];
  } else {
    ll mid = (l + r) / 2;
    build(l, mid, 2 * p);
    build(mid + 1, r, 2 * p + 1);
    tree[p] = tree[2 * p] + tree[2 * p + 1];
  }
}
```

## 区间修改

如果要求修改区间  *[l,r]* ，把所有包含在区间 *[l,r]* 中的节点都遍历一次、修改一次，时间复杂度无法承受。我们这里要引入一个叫做 **「懒惰标记」** 的东西。

```cpp
// cl 当前区间左边界 cr 当前区间右边界 d区间修改的值
// l 要修改的区间左边界 r 要修改的区间右边界
void update(ll l, ll r, ll d, ll p = 1, ll cl = 1, ll cr = n) {
  if (cr < l || cl > r) {  // 当前区间与要修改的区间没有交集
    return;
  } else if (cl >= l && cr <= r) {  // 要修改的区间包含当前区间
    tree[p] += (cr - cl + 1) * d;
    if (cr > cl) {  // 不是叶子节点
      mark[p] += d;
    }
  }else {  // 修改区间包含部分当前区间
    ll mid = (cl + cr) / 2;
    push_down(p, cr - cl + 1);  // 向下传递
    update(l, r, d, 2 * p, cl, mid);
    update(l, r, d, 2 * p + 1, mid + 1, cr);
    tree[p] = tree[2 * p] + tree[2 * p + 1];
  }
}
```

```cpp
inline void push_down(ll p, ll len) {  // 标记向下传递
  mark[2 * p] += mark[p];  // 向下传递lazy标记
  mark[2 * p + 1] += mark[p];  
  tree[2 * p] += mark[p] * (len - len / 2);  // 更新区间和
  tree[2 * p + 1] += mark[p] * (len / 2);
  mark[p] = 0;  // 清空lazy标记
}
```

## 区间查询

区间查询类似于区间修改

```cpp
ll query(ll l, ll r, ll p = 1, ll cl = 1, ll cr = n) {
  if (cr < l || cl > r) {  // 当前区间与要查询的区间没有交集 
    return 0;
  } else if (cl >= l && cr <= r) {  // 要查询的区间包含当前区间
    return tree[p];
  } else {  // 查询区间包含部分当前区间
    ll mid = (cl + cr) / 2;
    push_down(p, cr - cl + 1);
    return (query(l, r, 2 * p, cl, mid) +
    query(l, r, 2 * p + 1, mid + 1, cr));
  }
}
```

## [线段树模板题（区间加）](https://www.luogu.com.cn/problem/P3372)

解析：线段树的基本操作

代码：

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
const ll MAXSIZE = 4e5 + 5;
ll tree[MAXSIZE];
ll arr[MAXSIZE];
ll mark[MAXSIZE];  // lazy标记
ll n, m;

// 左右区间 树节点指针
void build(ll l = 1, ll r = n, ll p = 1) {
  if (l == r) {
    tree[p] = arr[l];
  } else {
    ll mid = (l + r) / 2;
    build(l, mid, 2 * p);
    build(mid + 1, r, 2 * p + 1);
    tree[p] = tree[2 * p] + tree[2 * p + 1];
  }
}

inline void push_down(ll p, ll len) {  // 标记向下传递
  mark[2 * p] += mark[p];  // 向下传递lazy标记
  mark[2 * p + 1] += mark[p];  
  tree[2 * p] += mark[p] * (len - len / 2);  // 更新区间和
  tree[2 * p + 1] += mark[p] * (len / 2);
  mark[p] = 0;  // 清空lazy标记
}

// cl 当前区间左边界 cr 当前区间右边界 d区间修改的值
// l 要修改的区间左边界 r 要修改的区间右边界
void update(ll l, ll r, ll d, ll p = 1, ll cl = 1, ll cr = n) {
  if (cr < l || cl > r) {  // 当前区间与要修改的区间没有交集
    return;
  } else if (cl >= l && cr <= r) {  // 要修改的区间包含当前区间
    tree[p] += (cr - cl + 1) * d;
    if (cr > cl) {  // 不是叶子节点
      mark[p] += d;
    }
  }else {  // 修改区间包含部分当前区间
    ll mid = (cl + cr) / 2;
    push_down(p, cr - cl + 1);  // 向下传递
    update(l, r, d, 2 * p, cl, mid);
    update(l, r, d, 2 * p + 1, mid + 1, cr);
    tree[p] = tree[2 * p] + tree[2 * p + 1];
  }
}

// cl 当前区间左边界 cr 当前区间右边界
// l 要查询的区间左边界 r 要查询的区间右边界
ll query(ll l, ll r, ll p = 1, ll cl = 1, ll cr = n) {
  if (cr < l || cl > r) {  // 当前区间与要查询的区间没有交集 
    return 0;
  } else if (cl >= l && cr <= r) {  // 要查询的区间包含当前区间
    return tree[p];
  } else {  // 查询区间包含部分当前区间
    ll mid = (cl + cr) / 2;
    push_down(p, cr - cl + 1);
    return (query(l, r, 2 * p, cl, mid) +
    query(l, r, 2 * p + 1, mid + 1, cr));
  }
}

int main() {
  cin >> n >> m;
  for (ll i = 1; i <= n; i++) {
    cin >> arr[i];
  }
  build(1, n, 1);

  ll flag, x, y, k;
  for (ll i = 0; i < m; i++) {
    cin >> flag >> x >> y;
    if (flag == 1) {
      cin >> k;
      update(x, y, k);
    } else {
      cout << query(x, y) << endl;
    }
  }
  
  return 0;
}
```

## 线段树优化

```cpp
#include <bits/stdc++.h>
#define IO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 5, NA = 0;
ll tree[MAXN * 4], mark[MAXN * 4], a[MAXN];
ll n, m;

// 构造线段树
void build(int l, int r, int p) {
  if (l == r) {
    tree[p] = a[l];
  } else {
    int mid = (l + r) / 2;
    build(l, mid, 2 * p);
    build(mid + 1, r,  2 * p + 1);
    tree[p] = tree[2 * p] + tree[2 * p + 1];
  }
}
// 更新函数
void upd(ll p, ll d, ll len) {
  tree[p] += d * len;
  (mark[p] == NA) ? (mark[p] = d) : (mark[p] += d);
}
// 向下传递标记
void push_down(int p, int len) {
  if (mark[p] != NA) {
    upd(2 * p, mark[p], len - len / 2);
    upd(2 * p + 1, mark[p], len / 2);
    mark[p] = NA;
  }
}
// 区间更新值
void update(int l, int r, int d, int p = 1, int cl = 1, int cr = n) {
  if (cl >= l && cr <= r) {
    return upd(p, d, cr - cl + 1);
  }
  push_down(p, cr - cl + 1);
  int mid = (cl + cr) / 2;
  if (mid >= l) {
    update(l, r, d, 2 * p, cl, mid);
  }
  if (mid < r) {
    update(l, r, d, 2 * p + 1, mid + 1, cr);
  }
  tree[p] = tree[2 * p] + tree[2 * p + 1];
}
// 查询区间和
ll query(int l, int r, int p = 1, int cl = 1, int cr = n) {
  if (cl >= l && cr <= r) {
    return tree[p];
  }
  push_down(p, cr - cl + 1);
  int mid = (cl + cr) / 2;
  if (mid >= r) {
    return query(l, r, 2 * p, cl, mid);
  } else if (mid < l) {
    return query(l, r, 2 * p + 1, mid + 1, cr);
  } else {
    return query(l, r, 2 * p, cl, mid) + query(l, r, 2 * p + 1, mid + 1, cr);
  }
}

int main() {
  cin >> n >> m;
  for (ll i = 1; i <= n; i++) {
    cin >> a[i];
  }
  build(1, n, 1);

  ll flag, x, y, k;
  for (ll i = 0; i < m; i++) {
    cin >> flag >> x >> y;
    if (flag == 1) {
      cin >> k;
      update(x, y, k);
    } else {
      cout << query(x, y) << endl;
    }
  }
  return 0;
}
```

关于区间修改和区间查询的一点不一样

- 修改：不用返回值所以两个if语句可以同时成立
- 查询：需要返回值，if-else语句中只有一个能够成立

## 参考链接

- [算法学习笔记(14): 线段树](https://zhuanlan.zhihu.com/p/106118909)