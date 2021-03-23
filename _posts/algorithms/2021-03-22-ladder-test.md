---
layout:     post
title:      "天梯赛测试题解"
subtitle:   ""
date:       2021-03-22 23:25:32
author:     "XDong"
header-img: "img/post-bg-eva-q-asuka-1920x1200.png"
tags:
    - 算法
---


# 天梯赛测试题解

## L1

### [1-古风排版](https://pintia.cn/problem-sets/994805046380707840/problems/994805091888906240)

这是一道模拟题

输入样例

>4
This is a test case

输出样例

>asa T  
st ih  
e tsi  
ce s

对样例而言，第 $1, 5 = 1 + 4, 9 = 1 + 4 + 4, 13 = 1 + 4 + 4 + 4, 17 = 1 + 4 + 4 + 4 + 4 + 4$ 这5个字符即 "T" " " "a" "s" "a"属于古风排版的第一行，按照该方法得到每一行的古风排版后，倒叙输出即可

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;
  getchar();
  string str;
  getline(cin, str);
  while (str.size() % N) {
    str.push_back(' ');
  }
  vector<string> s;
  for (int i = 0; i < N; i++) {
    string temp;
    for (int j = i; j < str.size(); j += N) {
      temp.push_back(str[j]);
    }
    reverse(temp.begin(), temp.end());
    s.push_back(temp);
  }
  for (int i = 0; i < s.size(); i++) {
    cout << s[i] << endl;
  }
  return 0;
}
```

### [2-大笨钟](https://pintia.cn/problem-sets/994805046380707840/problems/994805119944605696)

这是一道简单的模拟题

模拟即可

```cpp
#include <bits/stdc++.h>
#define IO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int main() {
  IO;
  string str;
  cin >> str;
  int h = (str[0] - '0') * 10 + (str[1] - '0');
  int m = (str[3] - '0') * 10 + (str[4] - '0');
  int cnt = h;
  if (m) {
    cnt++;
  }
  if (cnt > 12) {
    cnt -= 12;
    for (int i = 0; i < cnt; i++) {
      cout << "Dang";
    }
    cout << endl;
  } else {
    cout << "Only " << str << ".  Too early to Dang.";
  }
  return 0;
}
```

### [3-宇宙无敌加法器](https://pintia.cn/problem-sets/994805260223102976/problems/994805263297527808)

这是一道模拟题

先将要相加的两个字符串s1和s2都扩展到与s等长，然后从字符串后往前（即从低位到高位）按照进制相加到res中，记得要加进位carry。输出的时候记得不要输出前面的0，假如没有一次输出的话输出0即可

```cpp
#include <bits/stdc++.h>
#define IO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int main() {
  // IO;
  string s, s1, s2, res;
  int carry = 0;  // 进位
  cin >> s >> s1 >> s2;
  s1.insert(s1.begin(), s.size() - s1.size(), '0');  // 前面补0到跟s一样长
  s2.insert(s2.begin(), s.size() - s2.size(), '0');  // 前面补0到跟s一样长
  res = s;
  // 重低位到高位
  for (int i = s.length() - 1; i >= 0; i--) {
    int temp = s[i] == '0' ? 10 : (s[i] - '0');  // 这位数是多少进制
    res[i] = (s1[i] - '0' + s2[i] - '0' + carry) % temp + '0';
    carry = (s1[i] - '0' + s2[i] - '0' + carry) / temp;
  }
  if (carry != 0) {
    res = '1' + res;
  }
  
  bool flag = false;  // 是否输出过
  for (int i = 0; i < res.size(); i++) {
    if (res[i] != '0' || flag) {
      flag = true;
      cout << res[i];
    }
  }
  if (!flag) {
    cout << '0' << endl;
  }
  return 0;
}
```

### [4-情人节](https://pintia.cn/problem-sets/994805046380707840/problems/994805097018540032)

这是一道简单的模拟题

模拟即可

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  int cnt = 0;
  string str;
  string a ="", b = "";
  while (cin >> str && str != ".") {
    cnt++;
    if (cnt == 2) {
      a =  str;
    }
    if (cnt == 14) {
      b = str;
    }
  }
  if (a != "" && b != "") {
    cout << a << " and " << b << " are inviting you to dinner..." << endl;
  } else if (a != "") {
    cout << a << " is the only one for you..." << endl;
  } else {
    cout << "Momo... No one is for you ..." << endl;
  }
  return 0;
}
```

### [5-I Love GPLT](https://pintia.cn/problem-sets/994805046380707840/problems/994805108934557696)

这是一道简单的模拟题

模拟即可

```cpp
#include <bits/stdc++.h>
#define IO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int main() {
  IO;
  string str = "I Love GPLT";
  for (int i = 0; i < str.size(); i++) {
    cout << str[i] << endl;
  }
  return 0;
}
```

### [6-是不是太胖了](https://pintia.cn/problem-sets/994805046380707840/problems/994805104983523328)

这是一道简单的模拟题

模拟即可

```cpp
#include <bits/stdc++.h>
#define IO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int main() {
  int H;
  cin >> H;
  double res = (H - 100) * 0.9 * 2;
  printf("%.1lf\n", res);
  return 0;
}
```

### [7-到底是不是太胖了](https://pintia.cn/problem-sets/994805046380707840/problems/994805102173339648)

这是一道简单的模拟题

模拟即可

```cpp
#include <bits/stdc++.h>
#define IO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int main() {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    int H, W;
    cin >> H >> W;
    double stand = (H - 100) * 0.9 * 2;
    if (abs(W - stand) < 0.1 * stand) {
      cout << "You are wan mei!" << endl;
    } else if (W < stand) {
      cout << "You are tai shou le!" << endl;
    } else {
      cout << "You are tai pang le!" << endl;
    }
  }
  return 0;
}
```

### [8-外星人的一天](https://pintia.cn/problem-sets/1372823602584285184/problems/1372823729201901575)

这是一道简单的模拟题

设地球人是时刻为d h m，外星人的时刻为dd hh mm

- $dd = (d + 1) / 2$
- 如果天数为奇数 $hh = h / 2$ ，否则 $hh = (24 + h) / 2$
- $mm = (((h \% 2) * 60) + m) / 2$

```cpp
#include <bits/stdc++.h>
#define IO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int main() {
  IO;
  int cas;
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    int d;
    cin >> d;
    string str;
    cin >> str;
    int h = (str[0] - '0') * 10 + (str[1] - '0');
    int m = (str[3] - '0') * 10 + (str[4] - '0');
    int hh, mm;
    int dd = (d + 1) / 2;
    if (d % 2) {
      mm = (((h % 2) * 60) + m) / 2;
      hh = h / 2;
    } else {
      mm = (((h % 2) * 60) + m) / 2;
      hh = (24 + h) / 2;
    }
    string res;
    res.push_back((hh / 10) + '0');
    res.push_back((hh % 10) + '0');
    res.push_back(':');
    res.push_back((mm / 10) + '0');
    res.push_back((mm % 10) + '0');
    if (d == 0) {
      cout << d << " " << str << endl;
    } else {
      cout << dd << " " << res << endl;
    }
  }
  return 0;
}
```

## L2

### [1-功夫传人](https://pintia.cn/problem-sets/994805046380707840/problems/994805059118809088)

这道题主要考查的是树的遍历

祖师爷门下的徒子徒孙家谱是一个 **树形结构**

![图片](/img/algorithms/PTA-L2-020.png)

我们只要遍历这颗树，便会知道所有得道者的功力总和

树的遍历有两种

- 广度遍历（层次遍历）
- 深度遍历（前序遍历，中序遍历，后序遍历）

我的代码是使用的广度遍历


注意：题目的输入师傅不一定出现了徒弟的前面，所以我们这里用一个vec二维数组来保存题目的输入

```cpp
vector<vector<int>> in;  // 保存题目的输入
```

```cpp
#include <bits/stdc++.h>
#define IO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
const int MAXN = 1e5 + 5;
vector<vector<int>> in;
double a[MAXN];
int main() {
  IO;
  int N;
  double Z, r;
  cin >> N >> Z >> r;
  int cnt, temp;
  for (int i = 0; i < N; i++) {
    vector<int> vec;
    cin >> cnt;
    vec.push_back(cnt);
    for (int i = 0; i < cnt; i++) {
      cin >> temp;
      vec.push_back(temp);
    }
    if (cnt == 0) {
      cin >> temp;
      vec.push_back(temp);
    }
    in.push_back(vec);
  }
  double res = 0;
  a[0] = Z;
  queue<int> que;
  que.push(0);
  while (!que.empty()) {
    int q = que.front();
    que.pop();
    int cnt = in[q][0];
    for (int i = 1; i <= in[q][0]; i++) {
      a[in[q][i]] = a[q] * (1.0 - r / 100);
      que.push(in[q][i]);
    }
    if (cnt == 0) {
      a[q] *= in[q][1];
      res += a[q];
    }
  }
  cout << (long long int)(res) << endl;
  return 0;
}
```

### [2-抢红包](https://pintia.cn/problem-sets/994805046380707840/problems/994805066890854400)

这道题目是一道结构体排序题

我们定义一个结构体来保存一个人的有关信息

```cpp
struct Node {
  int money;
  int get;
  int id;
} node[MAXN];
```

而C++自带排序sort函数，但是我们需要自己定义**比较方式**

```cpp
bool cmp(Node &a, Node &b) {
  if (a.money != b.money) {
    return ((a.money) > (b.money));
  } else if (a.get != b.get) {
    return ((a.get) > (b.get));
  } else {
    return ((a.id) < (b.id));
  }
}
```

```cpp
#include <bits/stdc++.h>
#define IO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
const int MAXN = 1e4 + 5;
struct Node {
  int money;
  int get;
  int id;
} node[MAXN];
bool cmp(Node &a, Node &b) {
  if (a.money != b.money) {
    return ((a.money) > (b.money));
  } else if (a.get != b.get) {
    return ((a.get) > (b.get));
  } else {
    return ((a.id) < (b.id));
  }
}
int main() {
  int N;
  cin >> N;
  for (int i = 1; i <= N; i++) {
    int K;
    cin >> K;
    node[i].id = i;
    for (int j = 0; j < K; j++) {
      int N, P;
      cin >> N >> P;
      node[i].money -= P;
      node[N].money += P;
      node[N].get += 1;
    }
  }
  sort(node + 1, node + 1 + N, cmp);
  for (int i = 1; i <= N; i++) {
    double temp = node[i].money * 0.01;
    printf("%d %.2lf\n", node[i].id, temp);
  }
  return 0;
}
```

### [3-家庭房产](https://pintia.cn/problem-sets/994805046380707840/problems/994805068539215872)

这道题可以用[并查集](https://oi-wiki.org/ds/dsu/)来解决

定义Person结构体存储个人信息

```cpp
struct Person {
  int id;
  int house_cnt;
  int house_area;
} people[MAXN];
```

定义Home结构体存储家庭信息

```cpp
struct Home {
  int min_id = INT_MAX;
  int number;
  int house_cnt;
  int house_area;
  double aver_cnt;
  double aver_area;
} homes[MAXN];
```

解题思路

1. 使用并查集合并输入的id的父母及子女信息
2. 统计一个大家庭的信息和最小编号
3. 对homes结构体数组进行快速排序
4. 输出答案

```cpp
#include <bits/stdc++.h>
#define IO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
const int MAXN = 1e4 + 5;
bool vis[MAXN];  // 代表有无该编号的人

struct Person {
  int id;
  int house_cnt;
  int house_area;
} people[MAXN];
struct Home {
  int min_id = INT_MAX;
  int number;
  int house_cnt;
  int house_area;
  double aver_cnt;
  double aver_area;
} homes[MAXN];
bool cmp(const Home &a, const Home &b) {
  if (a.aver_area != b.aver_area) {
    return a.aver_area > b.aver_area;
  } else {
    return a.min_id < b.min_id;
  }
}

int fa[MAXN], rk[MAXN];
void init(int n) {
  for (int i = 1; i <= n; i++) {
    fa[i] = i;
    rk[i] = 1;
  }
}
int find(int x) { return x == fa[x] ? x : (fa[x] = find(fa[x])); }
void merge(int i, int j) {
  int x = find(i);
  int y = find(j);
  if (rk[x] <= rk[y]) {
    fa[x] = y;
  } else {
    fa[y] = x;
  }
  if (rk[x] == rk[y] && x != y) {
    rk[y]++;
  }
}

int main() {
  init(10000);
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int id, father, mother;
    cin >> id >> father >> mother;
    vis[id] = true;
    if (father != -1) {
      vis[father] = true;
      merge(father, id);
    }
    if (mother != -1) {
      vis[mother] = true;
      merge(mother, id);
    }

    int k, temp;
    cin >> k;
    for (int j = 0; j < k; j++) {
      cin >> temp;
      vis[temp] = true;
      merge(id, temp);
    }

    cin >> people[id].house_cnt >> people[id].house_area;
  }
  // homes下标用该集合的祖先表示
  for (int i = 0; i < MAXN; i++) {
    if (vis[i]) {
      int father = find(i);
      homes[father].min_id = min(homes[father].min_id, i);
      homes[father].number++;
      homes[father].house_cnt += people[i].house_cnt;
      homes[father].house_area += people[i].house_area;
    }
  }
  for (int i = 0; i < MAXN; i++) {
    if (homes[i].number) {
      homes[i].aver_cnt = 1.0 * homes[i].house_cnt / homes[i].number;
      homes[i].aver_area = 1.0 * homes[i].house_area / homes[i].number;
    }
  }
  sort(homes, homes + MAXN, cmp);
  int res = 0;
  for (int i = 0; i < n; i++) {
    if (homes[i].aver_cnt > 0) {
      res++;
    }
  }
  cout << res << endl;
  for (int i = 0; i < res; i++) {
    printf("%04d %d %.3lf %.3lf\n", homes[i].min_id, homes[i].number,
           homes[i].aver_cnt, homes[i].aver_area);
  }
  return 0;
}
```