---
layout:     post
title:      "KMP算法"
subtitle:   ""
date:       2024-03-11 16:17:01
author:     "XDong"
header-img: "img/post-bg-wlop-1.jpg"
tags:
    - 算法
    - KMP
---

# KMP算法

参考[oi维基](https://oi-wiki.org/string/kmp/)

## KMP模板

```cpp
#include <bits/stdc++.h>
#define IO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
const int MAXN = 1e5 + 5;
int pmt[MAXN];

void get_pmt(const string& s) {
  for (int i = 1, j = 0; i < s.size(); i++) {
    while (j && s[i] != s[j]) j = pmt[j - 1];
    if (s[i] == s[j]) j++;
    pmt[i] = j;
  }
}

void kmp(const string& t, const string& p) {
  for (int i = 0, j = 0; i < t.size(); i++) {
    while (j && s[i] != p[j]) j = pmt[j - 1];
    if (s[i] == p[j]) j++;
    if (j == p.size()) {
      cout << i - j + 1 << endl;
      j = pmt[j - 1];
    }
  }
}

void kmp(const string& t, const string& p) {
  string temp = p + '#' + t;
  int m = t.size(), n = p.size();
  get_pmt(temp);
  for (int i = n + 1; i <= m + n; i++) {
    if (pmt[i] == n) cout << i - 2 * n << endl;
  }
}
```