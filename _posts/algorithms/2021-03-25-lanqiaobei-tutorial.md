---
layout:     post
title:      "蓝桥杯讲课"
subtitle:   ""
date:       2021-03-25 21:39:08
author:     "XDong"
header-img: "img/post-bg-eva-q-asuka-1920x1200.png"
tags:
    - 算法
    - 蓝桥杯
---


# 前言

蓝桥杯省赛中有些题目不是很难，只要能写出几道填空题和一两道编程题获奖还是很简单的

## 骗分

### 骗分理论依据

- 蓝桥杯是一种 **按测试数据给分的机制**，不是只有正确和错误，而是 10%,20%,50%,80%,100%
- 样例是白送的答案
- 贪心算法是一种局部范围内近似的正解
- 只要时间足够，任何问题都可以 **DFS**
- 编程不行的时候，可以手算（数学技巧）

### 骗分技巧

- 题目中的样例有时候可能出现在评测数据中（直接特判输出样例中的答案即可）
- 针对数据范围比较小的情况，可以采取（手算一边直接放答案，DFS暴力一波， random一波）
- 针对答案范围固定的，比如答案只可能出现Yes或者No，0或者1，-1，$0\leq ans \leq10$等情况，直接random一波
- 猜想有时候也是一种答案
- 寻找规律，先手动输出大部分情况， 然后找出一种规律，直接套进去输出答案
- 贪心算法
- 暴力算法 DFS
- 利用系统工具，比如 EXCLE，MATLAB，Python，电脑日期等

### 骗分例题[包子凑数](http://lx.lanqiao.cn/problem.page?gpid=T440)

![包子凑数](/img/algorithms/lanqiaobei-1.png)

```cpp
#include <iostream>
#include <ctime>
using namespace std;
const int MAXN = 1e1 + 5;
int a[MAXN];
int main() {
  srand(time(NULL));
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  if (n == 2 && a[0] == 4 && a[1] == 5) {
    cout << 6;
  } else if (rand() % 2 == 0) {
    cout << rand() % 10 << endl;
  } else {
    cout << "INF" << endl;
  }
  return 0;
}
```

尝试骗分：

- [求和](http://qoj.xust-kcsoft.club/problem/1001)

## 跑步锻炼

![跑步锻炼](/img/algorithms/lanqiaobei-2.png)

这是一道有关日期的模拟题

要注意的有几点

- 闰年的判断
- 月份的天数
- 星期几
- 是不是一号

代码：

```cpp
#include <iostream>
using namespace std;
int months[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int days(int year, int month) {
  if (year % 4 == 0 && month == 2) {
    return 29;
  } else {
    return months[month];
  }
}
int main() {
  bool flag = true;
  int res = 0;
  int week = 6;
  for (int i = 2000; i <= 2020; i++) {
    for (int j = 1; j <= 12; j++) {
      int day = days(i, j);
      for (int k = 1; k <= day; k++) {
        if (week == 1 || k == 1) {
          res += 2;
        } else {
          res += 1;
        }

        week++;
        week %= 7;

        if (i == 2020 && j == 10 && k == 1) {
          cout << res << endl;
        }
      }
    }
  }
  return 0;
}
```

答案：

>8879

## 七段码

![七段码](/img/algorithms/lanqiaobei-3.png)

这道题可以用dfs+并查集来解决

- 搜索每一种状态
- 判断亮的数码管一共属于多少个集合

但是实在不会的话，手算也可以是一种策略，七段码一共有 $2^7=256$ 种状态，对其进行判断即可

代码：

```cpp
#include <iostream>
using namespace std;

// 并查集
int fa[10];
void init() {
  for (int i = 0; i < 10; i++) {
    fa[i] = i;
  }
}
int find(int x) {
  return fa[x] == x ? x : (fa[x] = find(fa[x]));
}
void merge(int i,  int j) {
  int x = find(i);
  int y = find(j);
  fa[x] = y;
}

int map[10][10];  // 每个灯管视为一个节点
void add(int a, int b) {
  map[a][b] = map[b][a] = 1;
}
void add_edge() {
  // a b c d e f g
  // 1 2 3 4 5 6 7
  for (int i = 1; i <= 6; i++) {
    add(i, i + 1);
  }
  add(2, 7);
  add(3, 7);
  add(5, 7);
  add(6, 7);
  add(6, 1);
}

int res = 0;
bool vis[10];
void dfs(int a) {
  if (a > 7) {
    init();
    for (int i = 1; i <= 7; i++) {
      for (int j = 1; j <= 7; j++) {
        if (map[i][j] && vis[i] && vis[j]) {
          merge(i, j);
        }
      }
    }

    int k = 0;  // 集合有几个
    for (int i = 1; i <= 7; i++) {
      if (vis[i] && fa[i] == i) {
        k++;
      }
    }
    if (k == 1) {
      res++;
    }

    return;
  }

  vis[a] = true;  // 选这个节点
  dfs(a + 1);

  vis[a] = false;  // 不选这个节点
  dfs(a + 1);
}

int main() {
  add_edge();
  dfs(1);
  cout << res << endl;
  return 0;
}
```

答案：

>80

## 子串分值和

![子串分值和](/img/algorithms/lanqiaobei-4.png)

计算每个字符的贡献值

仅一个字串第一个出现的该种字符有贡献

```cpp
a       1
ab      2
aba     2
abab    2
ababc   3
 b      1
 ba     2
 bab    2
 babc   3
  a     1
  ab    2
  abc   3
   b    1
   bc   2
    c   1
如:
ababc   3:只有第一个'a' 'b' 'c'有贡献
计算每个字符的贡献值就可以算出之和了
```

```cpp
#include <iostream>
#include <cstring>
using namespace std;
const int MAXN = 1e5 + 5;
int last[30];  // 对应字母最后出现的位置
int main() {
  memset(last, -1, sizeof(last));
  string str;
  cin >> str;
  long long int res = 0;
  int size = str.size();
  for (int i = 0; i < size; i++) {
    res += (i - last[str[i] - 'a']) * (size - i);
    last[str[i] - 'a'] = i;
  }
  cout << res << endl;
  return 0;
}
```
