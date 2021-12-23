---
layout:     post
title:      "质数筛"
subtitle:   ""
date:       2020-11-11 10:07:27
author:     "XDong"
header-img: "img/post-bg-wlop.jpg"
tags:
    - 算法
    - 质数筛
---


# 质数筛

- [质数筛](#质数筛)
  - [朴素求法](#朴素求法)
  - [朴素法优化](#朴素法优化)
  - [埃氏筛](#埃氏筛)
  - [欧拉筛](#欧拉筛)

## 朴素求法

枚举每个小于N的值是否可以被N整除

```cpp
bool is_prime(int x) {
  if (x == 1) {
    return false;
  }
  for (int i = 2; i < x; i++) {
    if (x % i == 0) {
      return false;
    }
  }
}
```

## 朴素法优化

不难想到，N除上大于(N / 2)一定是除不尽的，所以枚举到(N / 2)即可  
可以再优化一下，一个数假如可以进行因数分解，分解得到的数一个小于sqrt(x)，
一个大于sqrt(x)，所以枚举到sqrt(x)即可

```cpp
bool is_prime(int x) {  // 普通法 O(logN)
  if (x == 1) {
    return false;
  }
  for (int i = 2; i <= x / 2; i++) {
    if (x % i == 0) {
      return false;
    }
  }
}
```

即使朴素法优化后，效率还是很低，数据规模较小时，
效率还可以接受，当规模较大效率就很低了，这时候就要用筛法来处理了

## 埃氏筛

>埃拉托斯特尼筛法，简称埃氏筛或爱氏筛，是一种由希腊数学家埃拉托斯特尼所提出的一种简单检定素数的算法。要得到自然数n以内的全部素数，必须把不大于根号n的所有素数的倍数剔除，剩下的就是素数。

实现思路

- 从质数2开始进行枚举
- 如果数字是质数，将范围内所有该数的倍数标记成非质数
- 继续向后枚举，直到遍历完范围内所有的数位置

```cpp
bool is_prime[10000];
void eratosthenes(int x) {
  memset(is_prime, true, sizeof(is_prime));  // 所有数默认标记为质数
  is_prime[1] = false;  // 1不是质数

  for (int i = 2; i <= x; i++) {  // 从2开始枚举
    if (is_prime[i]) {  // 如果i是质数
      for (int j = 2; i * j <= n; j++) {  // i的倍数不是质数
        is_prime[i * j] = false;
      }
    }
  }
}
```

埃氏筛的时间复杂度O(nloglogn)，相较于朴素法已经有了很大的改进，但是仍然会筛掉一些重复的合数

## 欧拉筛

在埃氏筛法的基础上，让每个合数只被它的最小质因子筛选一次，以达到不重复的目的

```cpp
int prime[10000];
bool is_prime[10000];
void euler(int x) {
  memset(is_prime, true, sizeof(is_prime));
  is_prime[1] = false;
  int cnt = 0;
  for (int i = 2; i <= x; i++) {
    if (is_prime[i]) {  // 为质数
      prime[++cnt] = i; 
    }
    for (int j = 1; i * prime[j] <= N; j++) {
      is_prime[i * prime[j]] = false;
      if (i % prime[j] == 0) {  // 防止重复筛去
        break;
      }
    }
  }
}
```

欧拉筛的关键在于

```cpp
if (i % prime[j] == 0) {  // 防止重复筛去
  break;
}
```

这个判断可以防止重复筛去，即每个数只被最小质因子筛去

如果i % prime[j] == 0不退出，**i = k * prime[j]**  
如果继续运算j + 1，**i * prime[j + 1] = (k * prime[j + 1]) * prime[j]**  
prime[j]是最小的质因数，所以**i * prime[j + 1] = (k * prime[j + 1]) * prime[j]**被重复筛去

例如i = 8 ，j = 1，prime[j] = 2，如果不跳出循环，prime[j + 1] = 3，8 * 3 = 4 * 3 * 2 = 2 * 12，在i = 12时会计算