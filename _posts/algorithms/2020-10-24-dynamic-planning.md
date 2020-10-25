---
layout:     post
title:      "基础dp总结"
subtitle:   " \"01背包 完全背包 多重背包及其优化 分组背包 最长公共子序列等动态规划问题\""
date:       2020-10-24 17:00:00
author:     "XDong"
header-img: "img/post-bg-wlop-2880x1800.jpg"
tags:
    - 算法
---


# 基础DP总结

- [基础DP总结](#基础dp总结)
  - [装箱问题](#装箱问题)
  - [01背包](#01背包)
  - [完全背包](#完全背包)
  - [多重背包问题](#多重背包问题)
    - [基础解法,转化为01背包问题,复杂度为O(n^3)](#基础解法转化为01背包问题复杂度为on3)
    - [二进制优化,转化为01背包问题,但物品数量为log(n),即复杂度为O(n^2log(n))](#二进制优化转化为01背包问题但物品数量为logn即复杂度为on2logn)
    - [单调队列优化:现在还不会](#单调队列优化现在还不会)
  - [分组背包](#分组背包)
  - [最长公共子序列](#最长公共子序列)
  - [最长上升子序列](#最长上升子序列)
  - [最短编辑距离](#最短编辑距离)
  - [最大子段和](#最大子段和)
  - [有依赖的背包](#有依赖的背包)

## [装箱问题](https://www.luogu.com.cn/problem/P1049)
>有一个箱子容量为V（正整数，0≤V≤20000），同时有n个物品（0&lt;n≤=30，每个物品有一个体积（正整数）。  
要求n个物品中，任取若干个装入箱内，使箱子的剩余空间为最小。

```cpp
#include <iostream>
using namespace std;

int dp[20001];
int v[31];
int main() {
  int V, n;
  cin >> V >> n;
  for (int i = 1; i <= n; i++) {
    cin >> v[i];
  }

  for (int i = 1; i <= n;i++) // dp[j]表示箱子体积为j时,当前最大能装的重量
    for (int j = V; j >= v[i]; j--)
      dp[j] = max(dp[j], dp[j - v[i]] + v[i]);

  cout << V - dp[V];
  return 0;
}
```

类似装箱问题的题目还有很多,  
"求m个数中和为n的方法",  
"给定一个正整数n，求将其分解成若干个素数之和的方案总数"  
此类题目通常只有一个变量,dp方程跟通常题目不一样,dp方程更为简单,价值即为体积或者重量的参数.

```cpp
// 装箱问题状态方程
for (int i = 1; i <= n;i++) // dp[j]表示箱子体积为j时,当前最大能装的重量
  for (int j = V; j >= v[i]; j--)
    dp[j] = max(dp[j], dp[j - v[i]] + v[i]);

// 小于等于n的素数之和为n的状态方程
for (int i = 1; i <= number(n); i++)
    for (int j = prime[i]; j <= n; j++)
        dp[j] += dp[j - prime[i]]; //状态方程 dp[j]为不选prime[j]的方法，dp[j-prime[i]]为选prime[j]的方法

// 洗发水最小小费的状态方程
for (int i = 0; i < 3; i++)
  for (int j = value[i]; j <= N; j++)
    dp[j] = max(dp[j], dp[j - value[i]] + value[i]);
```

***

## [01背包](https://www.acwing.com/problem/content/2/)

>有 N 件物品和一个容量是 V 的背包。每件物品只能使用一次。  
第 i 件物品的体积是 vi，价值是 wi。  
求解将哪些物品装入背包，可使这些物品的总体积不超过背包容量，且总价值最大。  
输出最大价值。

```cpp
#include <iostream>
using namespace std;

int dp[1001], v[1001], w[1001];
// dp[i]代表体积为i时可以装的最大物品价值,v代表volume, w代表worth

int main() {
  int N, V;
  cin >> N >> V;
  for (int i = 0; i < N; i++)
    cin >> v[i] >> w[i];

  for (int i = 0; i < N; i++) // 从第一件开始,到最后一件
    for (int j = V; j >= v[i]; j--) // 从后向前,防止重复选取
      dp[j] = max(dp[j], dp[j - v[i]] + w[i]); // 状态转移方程

  cout << dp[V];
  return 0;
}
```

***

## [完全背包](https://www.acwing.com/problem/content/3/)

>有 N 种物品和一个容量是 V 的背包，每种物品都有无限件可用。  
第 i 种物品的体积是 vi，价值是 wi。  
求解将哪些物品装入背包，可使这些物品的总体积不超过背包容量，且总价值最大。  
输出最大价值。

```cpp
#include <iostream>
using namespace std;

int dp[1001], v[1001], w[1001];
// dp[i]代表体积为i时可以装的最大物品价值,v代表volume, w代表worth
int main() {
  int N, V;
  cin >> N >> V;
  for (int i = 0; i < N; i++)
    cin >> v[i] >> w[i];
  
  for (int i = 0; i < N; i++) // 从第一种物品到第N种物品
    for (int j = v[i]; j <= V; j++) // 从小到大,不断转移
      dp[j] = max(dp[j], dp[j - v[i]] + w[i]); // 状态转移方程

  cout << dp[V];
  return 0;
}
```

***

## [多重背包问题](https://www.acwing.com/problem/content/4/)

>有 N 种物品和一个容量是 V 的背包。  
第 i 种物品最多有 si 件，每件体积是 vi，价值是 wi。  
求解将哪些物品装入背包，可使物品体积总和不超过背包容量，且价值总和最大。  
输出最大价值。

### 基础解法,转化为01背包问题,复杂度为O(n^3)

```cpp
#include <iostream>
using namespace std;

int dp[10000], v[101], w[101], s[101]; //v value w worth s 数量
int main() {
  int N, V;
  cin >> N >> V;
  for (int i = 0; i < N; i++) {
    cin >> v[i] >> w[i] >> s[i];
  }

  for (int i = 0; i < N; i++) { // 转换为01背包问题
    for (int j = V; j >= v[i]; j--) {
      for (int k = 1; k <= s[i] && k * v[i] <= j; k++)
      dp[j] = max(dp[j], dp[j - k * v[i]] + k * w[i]);
    }
  }

  cout << dp[V];
}
```

### 二进制优化,转化为01背包问题,但物品数量为log(n),即复杂度为O(n^2log(n))

```cpp
#include <iostream> // 二进制优化
#include <vector>
using namespace std;

struct Good {
  int v;
  int w;
};

int dp[2010];
int main() {
  int N, V;
  cin >> N >> V;
  vector<Good> goods;
  for (int i = 0; i < N; i++) {
    int v, w, s;
    cin >> v >> w >> s;
    for (int k = 1; k <= s; k *= 2) { // 例如0-7可以由1 2 3 1组成
      s -= k;
      goods.push_back({v * k, w * k});
    }
    if (s > 0) {
      goods.push_back({v * s, w * s});
    }
  }

  for (auto good : goods) { // 01背包问题
    for (int j = V; j >= good.v; j--) {
      dp[j] = max(dp[j], dp[j - good.v] + good.w);
    }
    for (int k = 0; k <= V; k++) {
      cout << dp[k] << " ";
    }
    cout << endl;
  }
  cout << dp[V];
  return 0;
}
```

### 单调队列优化:现在还不会

```cpp
```

***

## [分组背包](https://www.luogu.com.cn/problem/P1757)

>两个数 m,n，表示一共有n件物品，总重量为m。
接下来n行，每行3个数a,b,c ，表示物品的重量，利用价值，所属组数。

```cpp
#include <iostream>
using namespace std;

int w[1009], v[1009], g[1009];
long long int dp[1009];
int main() {
    int m, n, group = 1;
    cin >> m >> n;
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> v[i] >> g[i];
        group = max(group, g[i]);
    }

    int k = 0; //代表物品号码
    for (int i = 1; i <= group; i++) {
        for (int j = m; j > 0; j--) {
            for (int k = 0; k < n; k++) { //k为循环变量
                if (g[k] != i || j < w[k]) {
                    continue;
                }
                dp[j] = max(dp[j], dp[j - w[k]] + v[k]);
            }
        }
    }

    cout << dp[m];
    return 0;
}
```

***

## [最长公共子序列](https://vjudge.net/contest/394624#problem/H)

>给出两个字符串A B，求A与B的最长公共子序列（子序列不要求是连续的）。  
比如两个串为：  
abcicba  
abdkscab  
ab是两个串的子序列，abc也是，abca也是，其中abca是这两个字符串最长的子序列。

```cpp
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

int dp[1001][1001];
int main() {
  string A, B, res;
  cin >> A >> B;
  memset(dp, 0, sizeof(dp));
  for (int i = 0; i < A.length(); i++) {
    for (int j = 0; j < B.length(); j++) {
      if (A[i] == B[j]) {
        dp[i + 1][j + 1] = dp[i][j] + 1; // 相等则直接加1
      } else {
        dp[i + 1][j + 1] = max(dp[i + 1][j], dp[i][j + 1]); // 不相等分为i+1,j 和 i,j+1两种情况
      }
    }
  }
  
  int i = A.length(), j = B.length();
  while (i != 0 && j != 0) { // 求最长公共子序列
    if (A[i - 1] == B[j - 1]) {
      res.push_back(A[i - 1]);
      i--;
      j--;
    } else if (dp[i - 1][j] > dp[i][j - 1]) {
      i--;
    } else {
      j--;
    }
  }

  reverse(res.begin(), res.end());
  cout << res;
}
```

***

## [最长上升子序列](https://www.baidu.com/s?ie=UTF-8&wd=%E6%9C%80%E9%95%BF%E4%B8%8A%E5%8D%87%E5%AD%90%E5%BA%8F%E5%88%97)

>如100，101，101，102，103，102的最长上升子序列为100，101，102，103，长度为4。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_N = 1005, MAX_I = 1000005, INF = 10000;
int dp[MAX_N], a[MAX_I];

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  fill(dp, dp + n, INF);
  for (int i = 0; i < n; i++) {
    *lower_bound(dp, dp + n, a[i]) = a[i]; // lower_bound返回第一个大于啊a[i]的地址
  }
  cout << lower_bound(dp, dp + n, INF) - dp;

  return 0;
}
```

***

## [最短编辑距离](https://www.luogu.com.cn/problem/P2758)

>设A和B是两个字符串。我们要用最少的字符操作次数，将字符串A转换为字符串B。这里所说的字符操作共有三种：  
1、删除一个字符；  
2、插入一个字符；  
3、将一个字符改为另一个字符；  
！皆为小写字母！  
求最少字符操作次数。

```cpp
#include <iostream>
using namespace std;

const int INF = 2001;
int dp[2001][2001];
int main() {
  string str1, str2;
  cin >> str1 >> str2;
  int len1 = str1.length(), len2 = str2.length();

  for (int i = 0; i <= len1; i++) {
    for (int j = 0; j <= len2; j++) {
      if (i == 0) dp[i][j] = j;
      if (j == 0) dp[i][j] = i;
      if (i != 0 && j != 0) dp[i][j] = INF;
    }
  }

  for (int i = 1; i <= len1; i++) { // str下标从0开始，dp数组从1开始
    for (int j = 1; j <= len2; j++) {
      if (str1[i - 1] == str2[j - 1])
        dp[i][j] = dp[i - 1][j - 1]; // 相等不用操作
      else {
        int temp = min(dp[i][j - 1] + 1, dp[i - 1][j] + 1); //增加，删除
        dp[i][j] = min(temp, dp[i - 1][j - 1] + 1); //增减，删除，修改中去最小值
      }
    }
  }

  cout << dp[len1][len2];
  return 0;
}
```

***

## [最大子段和](https://www.luogu.com.cn/problem/P1115)

>给出一个长度为 n 的序列 a，选出其中连续且非空的一段使得这段和最大。

```cpp
#include <iostream>
using namespace std;

const int INF = -10005;
long long int dp[200005];
int a[200005];
int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    dp[i] = a[i]; // 默认子段和为本身
  }

  for (int i = 1; i < n; i++) {
    dp[i] = max(dp[i], dp[i - 1] + a[i]); // 不选则最大子段和为本身
  }

  long long int res = INF;
  int flag = 0;
  for (int i = 0; i < n; i++) {
    res = max(dp[i], res); // 选出最大值
  }
  cout << res;
}
```

***

## [有依赖的背包](https://www.luogu.com.cn/problem/P1064)

>选附件必须要选主件，求V * W之和的最大值。

```cpp
#include <cstring>
#include <iostream>
using namespace std;

int dp[32009], money[61], value[61], group[61][3];
int main() {
  int n, m, q, val;
  cin >> n >> m;

  memset(group, 0, sizeof(group));
  for (int i = 0; i < m; i++) {
    cin >> money[i] >> val >> q;
    value[i] = val * money[i]; // 所求为val * money
    if (q == 0) {  // 分组,group[i][0]为主件
      group[i][0] = 1;
    } else {
      if (group[q - 1][1] == 0) {  // 附件
        group[q - 1][1] = i;
      } else {
        group[q - 1][2] = i;
      }
    }
  }

  for (int i = 0; i < m; i++) {
    if (group[i][0] == 1) {
      for (int j = n; j >= money[i]; j--) {
        dp[j] = max(dp[j], dp[j - money[i]] + value[i]);  // 选主件

        int f1_index = group[i][1], f2_index = group[i][2];
        if (f1_index != 0 && j >= money[i] + money[f1_index]) {  // 主件加附件1
          dp[j] = max(dp[j], dp[j - money[i] - money[f1_index]] + value[i] + value[f1_index]);
        }
        if (f2_index != 0 && j >= money[i] + money[f2_index]) {  // 主件加附件2
          dp[j] = max(dp[j], dp[j - money[i] - money[f2_index]] + value[i] + value[f2_index]);
        }
        if (f1_index && f2_index && j >= money[i] + money[f1_index] + money[f2_index]) {
          dp[j] = max(dp[j], dp[j - money[i] - money[f1_index] - money[f2_index]]  // 主件加附件1和2
          + value[i] + value[f1_index] + value[f2_index]);
        }
      }
    }
  }
  cout << dp[n] << endl;
  return 0;
}
```

***
***
