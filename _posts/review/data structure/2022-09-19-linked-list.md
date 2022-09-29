---
layout:     post
title:      "链表实现"
subtitle:   ""
date:       2022-09-19 16:38:14
author:     "XDong"
header-img: "img/post-bg-wlop-1.jpg"
tags:
    - 复习
    - 数据结构
    - 链表
---

# 链表

## 结构体定义

```cpp
// 单链表结构体
typedef struct LNode {
  ElemType data;
  struct LNode *next;
} LNode, *LinkedList;
```

## 头插法

```cpp
// 头插法
LinkedList HeadInsert(LinkedList &L) {
  int x;
  L = new LNode;  // 创建头结点
  L->next = NULL;        // 初始化为空链表
  while (cin >> x && x != -1) {  // 输入-1表示结束
    LNode *s = new LNode;
    s->data = x;
    s->next = L->next;
    L->next = s;
  }
  return L;
}
```

## 尾插法

```cpp
// 尾插法
LinkedList TailInsert(LinkedList &L) {
  int x;
  L = new LNode;  // 创建头结点
  L->next = NULL;        // 初始化为空链表
  LNode *r = L;          // r为表尾结点
  while (cin >> x && x != -1) {  // 输入-1表示结束
    LNode *s = new LNode;
    s->data = x;
    r->next = s;
    r = s;
  }
  return L;
}
```

## 按序号查找结点值

```cpp
// 按序号查找结点值
LNode *GetElem(LinkedList L, int i) {
  int j = 1;              // 计数器
  LNode *p = L->next;     // p为第1个结点指针
  if (i < 0) return NULL; // i无效，返回NULL
  if (i == 0) return L;   // i=0，返回表头
  while (p && j < i) {    // 查找第i个结点
    p = p->next;
    j++;
  }
  return p;               // 返回第i个结点的指针，若i>表长，返回NULL
}
```

## 按值查找表结点

```cpp
// 按值查找表结点
LNode *LocateElem(LinkedList L, ElemType e) {
  LNode *p = L->next;
  while (p && p->data != e) {  // 从第1个结点查找数据为e的结点
    p = p->next;
  }
  return p;
}
```

## 插入操作

```cpp
// 插入操作
void Insert(LinkedList L, int i, ElemType e) {
  LNode *p = GetElem(L, i-1);  // 查找i的前驱结点
  while (p) {
    LNode *q = new LNode;
    q->next = p->next;
    p->next = q;
  }
}
```

## 删除操作

```cpp
// 删除操作
void Delete(LinkedList L, int i) {
  LNode *p = GetElem(L, i-1);  // 查找i的前驱结点
  while (p) {
    LNode *q = p->next;
    p->next = q->next;
    delete q;
  }
}
```

## 双链表结构体定义

```cpp
// 双链表结构体
typedef struct DLNode {
  ElemType data;
  struct DLNode *prev;
  struct DLNode *next;
} DLNode, *DLinkedList;
```

## 所有代码

```cpp
#include <iostream>
using namespace std;
typedef int ElemType;

// 单链表结构体
typedef struct LNode {
  ElemType data;
  struct LNode *next;
} LNode, *LinkedList;

// 头插法
LinkedList HeadInsert(LinkedList &L) {
  int x;
  L = new LNode;  // 创建头结点
  L->next = NULL;        // 初始化为空链表
  while (cin >> x && x != -1) {  // 输入-1表示结束
    LNode *s = new LNode;
    s->data = x;
    s->next = L->next;
    L->next = s;
  }
  return L;
}

// 尾插法
LinkedList TailInsert(LinkedList &L) {
  int x;
  L = new LNode;  // 创建头结点
  L->next = NULL;        // 初始化为空链表
  LNode *r = L;          // r为表尾结点
  while (cin >> x && x != -1) {  // 输入-1表示结束
    LNode *s = new LNode;
    s->data = x;
    r->next = s;
    r = s;
  }
  return L;
}

// 按序号查找结点值
LNode *GetElem(LinkedList L, int i) {
  int j = 1;              // 计数器
  LNode *p = L->next;     // p为第1个结点指针
  if (i < 0) return NULL; // i无效，返回NULL
  if (i == 0) return L;   // i=0，返回表头
  while (p && j < i) {    // 查找第i个结点
    p = p->next;
    j++;
  }
  return p;               // 返回第i个结点的指针，若i>表长，返回NULL
}

// 按值查找表结点
LNode *LocateElem(LinkedList L, ElemType e) {
  LNode *p = L->next;
  while (p && p->data != e) {  // 从第1个结点查找数据为e的结点
    p = p->next;
  }
  return p;
}

// 插入操作
void Insert(LinkedList L, int i, ElemType e) {
  LNode *p = GetElem(L, i-1);  // 查找i的前驱结点
  while (p) {
    LNode *q = new LNode;
    q->next = p->next;
    p->next = q;
  }
}

// 删除操作
void Delete(LinkedList L, int i) {
  LNode *p = GetElem(L, i-1);  // 查找i的前驱结点
  while (p) {
    LNode *q = p->next;
    p->next = q->next;
    delete q;
  }
}

// 双链表结构体
typedef struct DLNode {
  ElemType data;
  struct DLNode *prev;
  struct DLNode *next;
} DLNode, *DLinkedList;
```