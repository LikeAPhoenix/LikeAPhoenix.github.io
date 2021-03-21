---
layout:     post
title:      "KMP算法"
subtitle:   "Knuth-Morria-Pratt"
date:       2020-11-03 15:30:21
author:     "XDong"
header-img: "img/post-bg-wlop-2880x1800.jpg"
tags:
    - 算法
    - KMP
---


# KMP算法


## 介绍
KMP算法是一种改进的字符串匹配算法，由D.E.Knuth，J.H.Morris和V.R.Pratt提出的，因此人们称它为克努特—莫里斯—普拉特操作（简称KMP算法）。KMP算法的核心是利用匹配失败后的信息，尽量减少模式串与主串的匹配次数以达到快速匹配的目的。具体实现就是通过一个next()函数实现，函数本身包含了模式串的局部匹配信息。KMP算法的时间复杂度O(m+n)。
![](/img/algorithms/kmp-9.jpg)


## build_match函数
![](/img/algorithms/kmp-14.jpg)

代码实现
```cpp
void build_next(string &pattern, int *next) {  // O(m)
  int i;
  next[0] = -1;
  for (int j = 1; j < pattern.length(); j++) {
    i = next[j - 1];
    while (i >= 0 && (pattern[i + 1] != pattern[j])) {  // 不相等继续前移i
      i = next[i];
    }
    if (pattern[i + 1] == pattern[j]) {
      next[j] = i + 1;
    } else {
      next[j] = -1;
    }
  }
}
``` 


## 代码
```cpp
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
const int MAXSIZE = 100000;

void build_next(string &pattern, int *next) {
  int i;
  next[0] = -1;
  for (int j = 1; j < pattern.length(); j++) {
    i = next[j - 1];
    while (i >= 0 && (pattern[i + 1] != pattern[j])) {  // 不相等继续前移i
      i = next[i];
    }
    if (pattern[i + 1] == pattern[j]) {
      next[j] = i + 1;
    } else {
      next[j] = -1;
    }
  }
}

int KMP(string str, string pattern) {
  int n = str.size();
  int m = pattern.size();
  if (n < m) {
    return -1;
  }

  int *next = new int[m];
  build_next(pattern, next);
  int s = 0, p = 0;
  while (s < n && p < m) {
    if (str[s] == pattern[p]) {
      s++;
      p++;
    } else if (p > 0) {
      p = next[p - 1] + 1;  // pattern指针向前滑动
    } else {
      s++;  // str指针后移
    }
  }
  return (p == m) ? (s - m) : -1;
}

int main() {
  string str = "This is a simple";
  string pattern = "simple";
  int index = KMP(str, pattern);
  cout << str[index];
  return 0;
}
```


## 参考链接
- [浙江大学-MOOC](https://www.icourse163.org/course/ZJU-93001)
- [MOOC-PDF](/pdf/KMP.pdf)