---
layout:     post
title:      "快速幂"
subtitle:   ""
date:       2020-11-11 10:51:35
author:     "XDong"
header-img: "img/post-bg-wlop-2880x1800.jpg"
tags:
    - 算法
---


# 快速幂

- [快速幂](#快速幂)
  - [递归快速幂](#递归快速幂)
  - [非递归快速幂](#非递归快速幂)
  - [参考链接](#参考链接)

快速幂（Exponentiation by squaring，平方求幂）是一种简单而有效的小算法，它可以以O(logn)的时间复杂度计算乘方。快速幂不仅本身非常常见，而且后续很多算法也都会用到快速幂。

## 递归快速幂

可以用二分的思路来得到一个递归方程：

![公式](/img/algorithms/exponentiation-by-squaring-1.svg)

- 如果n是奇数，则计算a^(n-1) * a
- 如果n是偶数，则计算a^(n/2)，然后平方
- 如果n是0，则返回1

```cpp
long long int quick_pow(int x, int y) {
  if (y == 0) {
    return 1;
  } else if (y % 2 == 1) {
    return quick_pow(x, y - 1) * x;  // % mod
  } else {
    long long int temp = quick_pow(x, y / 2);  // % mod
    return temp * temp;
  }
}
```

## 非递归快速幂

例如求7^10，可以把10写成二进制的形式(1010)2，7^10 = ((0 * 7^1) * **(1 * 7^2)** * (0 * 7^4) * **(1 * 7^8)**

```cpp
int quick_pow(int x, int y) {
  int ans = 1;
  while (y) {
    if (y & 1) {
      ans *= x;
    }
    x *= x;
    y >>= 1;
  }
  return ans;
}
```

![非递归快速幂](/img/algorithms/exponentiation-by-squaring-2.png)

## 参考链接

- [算法学习笔记(4)：快速幂](https://zhuanlan.zhihu.com/p/95902286)