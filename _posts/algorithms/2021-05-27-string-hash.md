---
layout:     post
title:      "字符串hash"
subtitle:   ""
date:       2021-05-27 00:28:10
author:     "XDong"
header-img: "img/post-bg-wlop-1.jpg"
tags:
    - 算法
    - 字符串
    - 字符串hash
---


# 字符串hash

用于方便地比较两个字符串是否相等

## 什么是hash

散列函数（英语：Hash function）又称散列算法、哈希函数，是一种从任何一种数据中创建小的数字“指纹”的方法。散列函数把消息或数据压缩成摘要，使得数据量变小，将数据的格式固定下来。该函数将数据打乱混合，重新创建一个叫做散列值（hash values，hash codes，hash sums，或hashes）的指纹。散列值通常用一个短的随机字母和数字组成的字符串来代表。好的散列函数在输入域中很少出现散列冲突。在散列表和数据处理中，不抑制冲突来区别数据，会使得数据库记录更难找到。

## hash的思想

我们定义一个把字符串映射到整数的函数$f$，这个$f$称为是 Hash 函数。

我们希望这个函数$f$可以方便地帮我们判断两个字符串是否相等。

具体来说，哈希函数最重要的性质可以概括为下面两条：

在 Hash 函数值不一样的时候，两个字符串一定不一样；

在 Hash 函数值一样的时候，两个字符串不一定一样（但有大概率一样，且我们当然希望它们总是一样的）。

Hash 函数值一样时原字符串却不一样的现象我们成为哈希碰撞。

## 构造字符串hash

### 自然溢出hash

base1为进制，unsigned long long会对$2^{64} - 1$取模

```cpp
ull hash1(string s) {
  ull res = 0;
  int size = s.length();
  for (int i = 0; i < size; i++) {
    res = (res * base1 + ull(s[i]));
  }
  return res;
}
```

### 单hash

类似于自然溢出hash，但是不对unsiged long long的边界取模，而是对一个指定的质数取模

```cpp
ull hash1(string s) {
  ull res = 0;
  int size = s.length();
  for (int i = 0; i < size; i++) {
    res = (res * base1 + ull(s[i])) % mod1;
  }
  return res;
}
```

### 双hash

进行两次hash即可，降低hash冲突

```cpp
ull hash1(string s) {
  ull res = 0;
  int size = s.length();
  for (int i = 0; i < size; i++) {
    res = (res * base1 + ull(s[i])) % mod1;
  }
  return res;
}

ull hash2(string s) {
  ull res = 0;
  int size = s.length();
  for (int i = 0; i < size; i++) {
    res = (res * base2 + ull(s[i])) % mod2;
  }
  return res;
}
```

## [【模板】字符串哈希](https://www.luogu.com.cn/problem/P3370 "https://www.luogu.com.cn/problem/P3370")

```cpp
#include <bits/stdc++.h>
#define IO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const ull base = 233333;
const ull mod1 = 1e9 + 7;
const ull mod2 = 1e9 + 9;
const int MAXN = 1e4 + 5;
string str[MAXN];
struct Node{
  ull hash1;
  ull hash2;
} a[MAXN];

bool cmp(const Node &a, const Node &b) {
  return a.hash1 < b.hash1;
}

ull hash1(string s) {
  ull res = 0;
  int size = s.length();
  for (int i = 0; i < size; i++) {
    res = (res * base + ull(s[i])) % mod1;  // 可以不取余，因为unsigned long long 会自然溢出
    // res = (res * base1 + ull(s[i])) % mod1;
  }
  return res;
}

ull hash2(string s) {
  ull res = 0;
  int size = s.length();
  for (int i = 0; i < size; i++) {
    res = (res * base + ull(s[i])) % mod2;  // 可以不取余，因为unsigned long long 会自然溢出
    // res = (res * base1 + ull(s[i])) % mod2;
  }
  return res;
}

int main() {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> str[i];
    a[i].hash1 = hash1(str[i]);
    a[i].hash2 = hash2(str[i]);
  }
  sort(a, a + N, cmp);

  int res = 1;
  for (int i = 1; i < N; i++) {
    if (a[i].hash1 != a[i - 1].hash1 || a[i].hash2 != a[i - 1].hash2) {
      res++;
    }
  }
  cout << res << endl;
  return 0;
}
```

## 参考链接

- [维基百科](https://zh.wikipedia.org/wiki/散列函数 "https://zh.wikipedia.org/wiki/散列函数")
- [oi-wiki](https://oi-wiki.org/string/hash/ "https://oi-wiki.org/string/hash/")