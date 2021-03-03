---
layout:     post
comments: true
title:      "区间DP"
subtitle:   "洛谷题单【动态规划3】区间与环形动态规划"
date:       2021-03-03 16:08:58
author:     "XDong"
header-img: "img/post-bg-wlop-2880x1800.jpg"
tags:
    - 算法
---


# 区间DP

题目

![题目](/img/algorithms/section-dynamic-planning-problems.png)

## [P1220 关路灯](https://www.luogu.com.cn/problem/P1220)

dp[i][j]: **当从i到j的灯都熄灭后剩下的灯的总功率**

dp[i][j][0]: **关掉i到j的灯后，老张站在i端点**

dp[i][j][1]: **关掉i到j的灯后，老张站在j端点**

状态转移方程

$dp[i][j][0] =$  
$min((dp[i + 1][j][0] + (a[i + 1] - a[i]) * (sum[i] + sum[n] - sum[j])),$  
$(dp[i + 1][j][1] + (a[j] - a[i]) * (sum[i] + sum[n] - sum[j])));$

$dp[i][j][1] =$  
$min((dp[i][j - 1][0] + (a[j] - a[i]) * (sum[i - 1] + sum[n] - sum[j - 1])),$  
$(dp[i][j - 1][1] + (a[j] - a[j - 1]) * (sum[i - 1] + sum[n] - sum[j - 1])));$

代码

```cpp
// 关灯不需要时间，所以走过的地点的灯会被随手关掉，老张只会在左右两边
#include <bits/stdc++.h>
using namespace std;

int dp[55][55][2];
int a[55], b[55], sum[55];
int main() {
  int n, c;
  cin >> n >> c;
  for (int i = 1; i <= n; i++) {
    cin >> a[i] >> b[i];
    sum[i] = sum[i - 1] + b[i];
  }
  memset(dp, 0x3f, sizeof(dp));
  dp[c][c][0] = dp[c][c][1] = 0;
  for (int l = 2; l <= n; l++) {
    for (int i = 1; i + l - 1 <= n; i++) {
      int j = i + l - 1;
      dp[i][j][0] = min(
          (dp[i + 1][j][0] + (a[i + 1] - a[i]) * (sum[i] + sum[n] - sum[j])),
          (dp[i + 1][j][1] + (a[j] - a[i]) * (sum[i] + sum[n] - sum[j])));
      dp[i][j][1] =min(
        (dp[i][j - 1][0] + (a[j] - a[i]) * (sum[i - 1] + sum[n] - sum[j - 1])),
        (dp[i][j - 1][1] + (a[j] - a[j - 1]) * (sum[i - 1] + sum[n] - sum[j - 1])));
    }
  }
  cout << min(dp[1][n][0], dp[1][n][1]) << endl;
  return 0;
}
```

## [P3205 [HNOI2010]合唱队](https://www.luogu.com.cn/problem/P3205)

状态转移方程
```cpp
  // 从左边进来肯定前1个人比他高，前1个人有2种情况，要么在i+1号位置，要么在j号位置
  if (a[i] < a[i + 1]) dp[i][j][0] += dp[i + 1][j][0];
  if (a[i] < a[j]) dp[i][j][0] += dp[i + 1][j][1];
  // 从右边进来肯定前1个人比他矮，前1个人有2种情况，要么在j-1号位置，要么在i号位置
  if (a[j] > a[i]) dp[i][j][1] += dp[i][j - 1][0];
  if (a[j] > a[j - 1]) dp[i][j][1] += dp[i][j - 1][1];
```

代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int a[1005];
int dp[1005][1005][2];
int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    dp[i][i][0]  = 1;  // 一个人默认从左边进来
  }
  for (int l = 2; l <= n; l++) {
    for (int i = 1; i + l - 1 <= n; i++) {
      int j = i + l - 1;
      if (a[i] < a[i + 1]) dp[i][j][0] += dp[i + 1][j][0];
      if (a[i] < a[j]) dp[i][j][0] += dp[i + 1][j][1];
      if (a[j] > a[i]) dp[i][j][1] += dp[i][j - 1][0];
      if (a[j] > a[j - 1]) dp[i][j][1] += dp[i][j - 1][1];
      dp[i][j][0] %= 19650827;
      dp[i][j][1] %= 19650827;
    }
  }
  cout << ((dp[1][n][0] + dp[1][n][1]) % 19650827) << endl;
  return 0;
}
```

## [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)

由于石子是环形的，所以要复制一遍数组a

```cpp
  for (int i = N + 1; i <= 2 * N; i++) {
    a[i] = a[i - N];
  }
```

状态转移方程

```cpp
  f1[i][j] = min(f1[i][j], f1[i][k] + f1[k + 1][j] + sum[j] - sum[i - 1]);
  f2[i][j] = max(f2[i][j], f2[i][k] + f2[k + 1][j] + sum[j] - sum[i - 1]);
```

代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int a[205], sum[205], f1[205][205], f2[205][205];
int main() {
  int N;
  cin >> N;
  for (int i = 1; i <= N; i++) {
    cin >> a[i];
    sum[i] = sum[i - 1] + a[i];
  }
  for (int i = N + 1; i <= 2 * N; i++) {
    a[i] = a[i - N];
    sum[i] = sum[i - 1] + a[i];
  }
  
  for (int len = 2; len <= N; len++) {
    for (int i = 1; i <= 2 * N - 1; i++) {
      int j = len + i - 1;
      f1[i][j] = INT_MAX;
      for (int k = i; k < j && k <= 2 * N - 1; k++) {
        f1[i][j] = min(f1[i][j], f1[i][k] + f1[k + 1][j] + sum[j] - sum[i - 1]);
        f2[i][j] = max(f2[i][j], f2[i][k] + f2[k + 1][j] + sum[j] - sum[i - 1]);
      }
    }
  }

  int mi = INT_MAX, ma = 0;
  for (int i = 1; i <= N; i++) {
    mi = min(mi, f1[i][i + N - 1]);
    ma = max(ma, f2[i][i + N - 1]);
  }
  cout << mi << endl
       << ma << endl;
  return 0;
}
```

## [P1063 [NOIP2006 提高组] 能量项链](https://www.luogu.com.cn/problem/P1063)

参考石子合并

代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int a[205], dp[205][205];
int main() {
  int N;
  cin >> N;
  for (int i = 1; i <= N; i++) {
    cin >> a[i];
    a[N + i] = a[i];
  }
  a[2 * N + 1] = a[1];

  for (int l = 2; l <= N; l++) {
    for (int i = 1; i <= 2 * N - 1; i++) {
      int j = i + l - 1;
      for (int k = i; j <= 2 * N && k < j; k++) {
        dp[i][j] = max(dp[i][j], dp[i][k] + dp[k + 1][j] + a[i] * a[k + 1] * a[j + 1]);
      }
    }
  }
  int res = 0;
  for (int i = 1; i <= N; i++) {
    res = max(res, dp[i][i + N - 1]);
  }
  cout << res << endl;
  return 0;
}
```

## [P1005 [NOIP2007 提高组] 矩阵取数游戏](https://www.luogu.com.cn/problem/P1005)

高精度+区间DP即可

对每行进行区间DP，所得最大分数为每行的最大分数之和

代码

```cpp
int matrix[85][85];
BigInt power_2[85];

int main() {
  power_2[0].data[0] = 1;
  power_2[0].digits = 1;
  for (int i = 1; i <= 80; i++) {
    power_2[i] = power_2[i - 1].multiplication_low(2);
  }

  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> matrix[i][j];
    }
  }
  // 每行分开进行处理
  BigInt res;
  for (int cas = 1; cas <= n; cas++) {
    BigInt temp;
    BigInt dp[85][85];
    for (int l = 1; l <= m; l++) {
      for (int i = 1; i <= m; i++) {
        int j = i + l - 1;
        // 每次取数只能选行首或者行尾
        // 当区间为1~m时 进行第一次取数
        // 当区间为i~i时 进行最后一次取数
        // 这个dp为逆序 先进行最后一次取数 再进行第一次取数
        temp = dp[i][j - 1] +
               power_2[m - j + i].multiplication_low(matrix[cas][j]);
        dp[i][j] > temp ? dp[i][j] = dp[i][j] : dp[i][j] = temp;
        temp = dp[i + 1][j] +
               power_2[m - j + i].multiplication_low(matrix[cas][i]);
        dp[i][j] > temp ? dp[i][j] = dp[i][j] : dp[i][j] = temp;
      }
    }
    res += dp[1][m];
  }
  cout << res << endl;
  return 0;
}
```
