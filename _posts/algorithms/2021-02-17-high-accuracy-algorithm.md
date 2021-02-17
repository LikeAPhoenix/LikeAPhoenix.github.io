---
layout:     post
title:      "高精度算法模板"
subtitle:   "洛谷 P1932 A+B A-B A*B A/B A%B Problem"
date:       2021-02-17 01:27:41
author:     "XDong"
header-img: "img/post-bg-wlop-2880x1800.jpg"
tags:
    - 算法
---


# 高精度算法

高精度计算（Arbitrary-Precision Arithmetic），也被称作大整数（bignum）计算，运用了一些算法结构来支持更大整数间的运算（数字大小超过语言内建整型）。

## 高精度对高精度

### 高精度加法

竖式加法

![plus](/img/algorithms/plus.png)

```cpp
  // 重载运算符+ 默认为 x > 0 && y > 0
  friend BigInt operator+(const BigInt &x, const BigInt &y) {
    BigInt res;
    res.digits = max(x.digits, y.digits);
    for (int i = 0; i < res.digits; i++) {
      res.data[i] = x.data[i] + y.data[i];
    }
    for (int i = 0; i < res.digits; i++) {
      if (res.data[i] > 9) {
        res.data[i + 1] += res.data[i] / 10;
        res.data[i] %= 10;
      }
    }
    if (res.data[res.digits] != 0) {
      res.digits++;
    }
    return res;
  }
```

### 高精度减法

竖式减法

![subtraction](/img/algorithms/subtraction.png)

```cpp
  // 重载运算符- 默认为 x > 0 && y > 0 && x > y
  friend BigInt operator-(const BigInt &x, const BigInt &y) {
    BigInt res;
    res.digits = max(x.digits, y.digits);
    for (int i = 0; i < res.digits; i++) {
      res.data[i] = x.data[i] - y.data[i];
    }
    for (int i = 0; i < res.digits; i++) {
      if (res.data[i] < 0) {
        res.data[i + 1]--;
        res.data[i] += 10;
      }
    }
    while (res.data[res.digits - 1] == 0 && res.digits > 1) {
      res.digits--;
    }
    return res;
  }
```

### 高精度乘法

竖式乘法

![multiplication-short](/img/algorithms/multiplication-short.png)

```cpp
  // 重载运算符* 默认为 x > 0 && y > 0
  friend BigInt operator*(const BigInt &x, const BigInt &y) {
    BigInt res;
    res.digits = x.digits + y.digits;
    for (int i = 0; i < x.digits; i++) {
      for (int j = 0; j < y.digits; j++) {
        res.data[i + j] += x.data[i] * y.data[j];
      }
    }
    for (int i = 0; i < res.digits; i++) {
      if (res.data[i] > 9) {
        res.data[i + 1] += res.data[i] / 10;
        res.data[i] %= 10;
      }
    }
    while (res.data[res.digits - 1] == 0 && res.digits > 1) {
      res.digits--;
    }
    return res;
  }
```

### 高精度除法

竖式长除法

![division](/img/algorithms/division.png)

```cpp
  // 将一个高精度数增大到10^y倍
  void move(int y) {
    for (int i = y + digits - 1; i >= 0; i--) {
      if (i >= y) {
        data[i] = data[i - y];
      } else {
        data[i] = 0;
      }
    }
    digits += y;
  }
  // 重载运算符/ 默认为 x > 0 && y > 0
  friend BigInt operator/(const BigInt &x, const BigInt &y) {
    BigInt res, xx = x;
    res.digits = max(x.digits - y.digits + 1, 1);
    for (int i = res.digits - 1; i >= 0; i--) {
      BigInt temp = y;
      temp.move(i);
      while (xx >= temp) {
        res.data[i]++;
        xx -= temp;
      }
    }
    while (res.data[res.digits - 1] == 0 && res.digits > 1) {
      res.digits--;
    }
    return res;
  }
```

### 高精度取余

与高精度除法类似

```cpp
  // 重载运算符% 默认为 x > 0 && y > 0
  friend BigInt operator%(const BigInt &x, const BigInt &y) {
    BigInt res = x;
    for (int i = x.digits - y.digits + 1; i >= 0; i--) {
      BigInt temp = y;
      temp.move(i);
      while (res >= temp) {
        res -= temp;
      }
    }
    return res;
  }
```

## 高精度对低精度

### 高精度乘上低精度

模拟手工乘法

```cpp
  // 高精度乘上低精度
  BigInt multiplication_low(long long int x) {
    BigInt res;
    res.digits = digits;
    long long int carry = 0;  // 进位
    for (int i = 0; i < res.digits; i++) {
      res.data[i] = data[i] * x + carry;
      carry = res.data[i] / 10;
      res.data[i] %= 10;
    }
    while (carry != 0) {
      res.data[res.digits++] = carry % 10;
      carry /= 10;
    }
    while (res.data[res.digits - 1] == 0 && res.digits > 1) {
      res.digits--;
    }
    return res;
  }
```

### 高精度除上低精度

模拟手工除法

```cpp
  // 高精度除上低精度
  BigInt divsion_low(long long int x) {
    BigInt res;
    res.digits = digits;
    long long int reminder = 0;
    for (int i = res.digits - 1; i >= 0; i--) {
      res.data[i] = (reminder * 10 + data[i]) / x;
      reminder = (reminder * 10 + data[i]) % x;
    }
    while (res.data[res.digits - 1] == 0 && res.digits > 1) {
      res.digits--;
    }
    return res;
  }
```

### 高精度取余低精度

模拟手工除法取余

```cpp
  // 高精度取余低精度
  long long int reminder_low(long long int x) {
    BigInt res;
    res.digits = digits;
    long long int reminder = 0;
    for (int i = res.digits - 1; i >= 0; i--) {
      res.data[i] = (reminder * 10 + data[i]) / x;
      reminder = (reminder * 10 + data[i]) % x;
    }
    while (res.data[res.digits - 1] == 0 && res.digits > 1) {
      res.digits--;
    }
    return reminder;
  }
```

## 完整模板

- 支持+ - * / %运算，只能是正数
- 重载了<< >>
- 重载了=
- 重载了> >= < <= == !=
- 重载了+= -= *= /=

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXDigit = 1e4 + 5;  // 最大位数

struct BigInt {
  int data[MAXDigit];  // 存储数据
  int digits;          // 当前位数
  BigInt() {
    fill(data, data + MAXDigit, 0);
    digits = 0;
  }
  void read() {
    string str;
    cin >> str;
    for (int i = str.size() - 1; i >= 0; i--) {
      data[digits++] = str[i] - '0';
    }
  }
  void print() {
    for (int i = digits - 1; i >= 0; i--) {
      cout << data[i];
    }
    cout << endl;
  }

  // 高精度乘上低精度
  BigInt multiplication_low(long long int x) {
    BigInt res;
    res.digits = digits;
    long long int carry = 0;  // 进位
    for (int i = 0; i < res.digits; i++) {
      res.data[i] = data[i] * x + carry;
      carry = res.data[i] / 10;
      res.data[i] %= 10;
    }
    while (carry != 0) {
      res.data[res.digits++] = carry % 10;
      carry /= 10;
    }
    while (res.data[res.digits - 1] == 0 && res.digits > 1) {
      res.digits--;
    }
    return res;
  }
  // 高精度除上低精度
  BigInt divsion_low(long long int x) {
    BigInt res;
    res.digits = digits;
    long long int reminder = 0;
    for (int i = res.digits - 1; i >= 0; i--) {
      res.data[i] = (reminder * 10 + data[i]) / x;
      reminder = (reminder * 10 + data[i]) % x;
    }
    while (res.data[res.digits - 1] == 0 && res.digits > 1) {
      res.digits--;
    }
    return res;
  }
  // 高精度取余低精度
  long long int reminder_low(long long int x) {
    BigInt res;
    res.digits = digits;
    long long int reminder = 0;
    for (int i = res.digits - 1; i >= 0; i--) {
      res.data[i] = (reminder * 10 + data[i]) / x;
      reminder = (reminder * 10 + data[i]) % x;
    }
    while (res.data[res.digits - 1] == 0 && res.digits > 1) {
      res.digits--;
    }
    return reminder;
  }

  // 重载运算符=
  BigInt &operator=(const BigInt &x) {
    if (this != &x) {
      fill(data, data + MAXDigit, 0);
      for (int i = 0; i < x.digits; i++) {
        data[i] = x.data[i];
      }
      digits = x.digits;
    }
    return *this;
  }

  // 重载运算符<
  friend bool operator<(const BigInt &x, const BigInt &y) {
    if (x.digits != y.digits) {
      return x.digits < y.digits;
    }
    for (int i = x.digits - 1; i >= 0; i--) {
      if (x.data[i] != y.data[i]) {
        return x.data[i] < y.data[i];
      }
    }
    return false;
  }
  // 重载运算符<=
  friend bool operator<=(const BigInt &x, const BigInt &y) {
    if (x.digits != y.digits) {
      return x.digits < y.digits;
    }
    for (int i = x.digits - 1; i >= 0; i--) {
      if (x.data[i] != y.data[i]) {
        return x.data[i] < y.data[i];
      }
    }
    return true;
  }
  // 重载运算符>
  friend bool operator>(const BigInt &x, const BigInt &y) {
    if (x.digits != y.digits) {
      return x.digits > y.digits;
    }
    for (int i = x.digits - 1; i >= 0; i--) {
      if (x.data[i] != y.data[i]) {
        return x.data[i] > y.data[i];
      }
    }
    return false;
  }
  // 重载运算符>=
  friend bool operator>=(const BigInt &x, const BigInt &y) {
    if (x.digits != y.digits) {
      return x.digits > y.digits;
    }
    for (int i = x.digits - 1; i >= 0; i--) {
      if (x.data[i] != y.data[i]) {
        return x.data[i] > y.data[i];
      }
    }
    return true;
  }
  // 重载运算符==
  friend bool operator==(const BigInt &x, const BigInt &y) {
    if (x.digits != y.digits) {
      return false;
    }
    for (int i = x.digits - 1; i >= 0; i--) {
      if (x.data[i] != y.data[i]) {
        return false;
      }
    }
    return true;
  }
  // 重载运算符!=
  friend bool operator!=(const BigInt &x, const BigInt &y) {
    if (x.digits != y.digits) {
      return true;
    }
    for (int i = x.digits - 1; i >= 0; i--) {
      if (x.data[i] != y.data[i]) {
        return true;
      }
    }
    return false;
  }

  // 重载+= -= *= /=运算符
  BigInt &operator+=(const BigInt &x) {
    *this = *this + x;
    return *this;
  }
  BigInt &operator-=(const BigInt &x) {
    *this = *this - x;
    return *this;
  }
  BigInt &operator*=(const BigInt &x) {
    *this = *this * x;
    return *this;
  }
  BigInt &operator/=(const BigInt &x) {
    *this = *this / x;
    return *this;
  }

  // 重载运算符+ 默认为 x > 0 && y > 0
  friend BigInt operator+(const BigInt &x, const BigInt &y) {
    BigInt res;
    res.digits = max(x.digits, y.digits);
    for (int i = 0; i < res.digits; i++) {
      res.data[i] = x.data[i] + y.data[i];
    }
    for (int i = 0; i < res.digits; i++) {
      if (res.data[i] > 9) {
        res.data[i + 1] += res.data[i] / 10;
        res.data[i] %= 10;
      }
    }
    if (res.data[res.digits] != 0) {
      res.digits++;
    }
    return res;
  }
  // 重载运算符- 默认为 x > 0 && y > 0 && x > y
  friend BigInt operator-(const BigInt &x, const BigInt &y) {
    BigInt res;
    res.digits = max(x.digits, y.digits);
    for (int i = 0; i < res.digits; i++) {
      res.data[i] = x.data[i] - y.data[i];
    }
    for (int i = 0; i < res.digits; i++) {
      if (res.data[i] < 0) {
        res.data[i + 1]--;
        res.data[i] += 10;
      }
    }
    while (res.data[res.digits - 1] == 0 && res.digits > 1) {
      res.digits--;
    }
    return res;
  }
  // 重载运算符* 默认为 x > 0 && y > 0
  friend BigInt operator*(const BigInt &x, const BigInt &y) {
    BigInt res;
    res.digits = x.digits + y.digits;
    for (int i = 0; i < x.digits; i++) {
      for (int j = 0; j < y.digits; j++) {
        res.data[i + j] += x.data[i] * y.data[j];
      }
    }
    for (int i = 0; i < res.digits; i++) {
      if (res.data[i] > 9) {
        res.data[i + 1] += res.data[i] / 10;
        res.data[i] %= 10;
      }
    }
    while (res.data[res.digits - 1] == 0 && res.digits > 1) {
      res.digits--;
    }
    return res;
  }
  // 将一个高精度数增大到10^y倍
  void move(int y) {
    for (int i = y + digits - 1; i >= 0; i--) {
      if (i >= y) {
        data[i] = data[i - y];
      } else {
        data[i] = 0;
      }
    }
    digits += y;
  }
  // 重载运算符/ 默认为 x > 0 && y > 0
  friend BigInt operator/(const BigInt &x, const BigInt &y) {
    BigInt res, xx = x;
    res.digits = max(x.digits - y.digits + 1, 1);
    for (int i = res.digits - 1; i >= 0; i--) {
      BigInt temp = y;
      temp.move(i);
      while (xx >= temp) {
        res.data[i]++;
        xx -= temp;
      }
    }
    while (res.data[res.digits - 1] == 0 && res.digits > 1) {
      res.digits--;
    }
    return res;
  }
  // 重载运算符% 默认为 x > 0 && y > 0
  friend BigInt operator%(const BigInt &x, const BigInt &y) {
    BigInt res = x;
    for (int i = x.digits - y.digits + 1; i >= 0; i--) {
      BigInt temp = y;
      temp.move(i);
      while (res >= temp) {
        res -= temp;
      }
    }
    while (res.data[res.digits - 1] == 0 && res.digits > 1) {
      res.digits--;
    }
    return res;
  }
};

istream &operator>>(istream &in, BigInt &x) {
  string str;
  cin >> str;
  for (int i = str.size() - 1; i >= 0; i--) {
    x.data[x.digits++] = str[i] - '0';
  }
  return in;
}
ostream &operator<<(ostream &out, BigInt &x) {
  for (int i = x.digits - 1; i >= 0; i--) {
    cout << x.data[i];
  }
  return out;
}

int main() {
  BigInt a, b, c;
  cin >> a >> b;
  cout << (c = a + b) << endl;
  if (a > b) {
    cout << (c = a - b) << endl;
  } else {
    cout << '-' << (c = b - a) << endl;
  }
  cout << (c = a * b) << endl << (c = a / b) << endl << (c = a % b) << endl;

  cout << (c = a.multiplication_low(50)) << endl;
  cout << (c = a.divsion_low(50)) << endl << a.reminder_low(50) << endl;
  return 0;
}
```

## 参考链接

- [洛谷题解](https://www.luogu.com.cn/problem/solution/P1932)
- [oi-wiki](https://oi-wiki.org/)