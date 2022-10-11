---
layout:     post
title:      "栈与队列的实现"
subtitle:   ""
date:       2022-10-11 12:06:22
author:     "XDong"
header-img: "img/post-bg-wlop-1.jpg"
tags:
    - 复习
    - 数据结构
    - 栈
    - 队列
---

# 栈与队列的实现

## 顺序栈

栈空条件为`S.top == -1`

栈满条件为`S.top == MaxSize - 1`

### 顺序栈的实现

```cpp
typedef struct {
  ElemType data[MaxSize];  // 存放栈中元素
  int top;                 // 栈顶指针
} SqStack;
```

### 顺序栈的基本操作

1. 初始化
2. 判空
3. 入栈
4. 出栈
5. 获得栈顶元素

```cpp
void InitStack(SqStack &S) { S.top = -1; }

bool StackEmpty(SqStack S) {
  if (S.top == -1)
    return true;
  else
    return false;
}

bool Push(SqStack &S, ElemType x) {
  if (S.top == MaxSize - 1) return false;
  S.data[++S.top] = x;
  return true;
}

bool Pop(SqStack &S, ElemType &x) {
  if (S.top == -1) return false;
  x = S.data[S.top--];
  return true;
}

bool GetTop(SqStack S, ElemType &x) {
  if (S.top == -1) return false;
  x = S.data[S.top];
  return true;
}
```

## 链栈的实现

```cpp
// 链栈的定义
typedef struct StackNode {
  ElemType data;           // 数据域
  struct StackNode *next;  // 指针域
} StackNode, *LinkStack;   // 栈类型定义
```

## 顺序队列

队空的条件为`Q.front == Q.rear`

队满的条件为`(Q.rear + 1) % MaxSize == Q.front`

### 顺序队列的实现

```cpp
typedef struct {
  ElemType data[MaxSize];  // 存放队列元素
  int front, rear;         // 队头指针和队尾指针
} SqQueue;
```

### 顺序队列的基本操作

1. 初始化
2. 判空
3. 入队
4. 出队

```cpp
void InitQueue(SqQueue &Q) { Q.front = Q.rear = 0; }

bool QueueEmpty(SqQueue Q) {
  if (Q.front == Q.rear)
    return true;
  else
    return false;
}

bool EnQueue(SqQueue &Q, ElemType x) {
  if ((Q.rear + 1) % MaxSize == Q.front) return false;  // 队满则报错
  Q.data[Q.rear] = x;
  Q.rear = (Q.rear + 1) % MaxSize;  // 队尾指针加1取模
  return true;
}

bool DeQueue(SqQueue &Q, ElemType &x) {
  if (Q.front == Q.rear) return false;  // 队空则报错
  x = Q.data[Q.front];
  Q.front = (Q.front + 1) % MaxSize;  // 队头指针加1取模
  return true;
}
```

## 链式队列

队空的条件为`Q.front == Q.rear`

### 链式队列的实现

```cpp
typedef struct QueueNode {
  ElemType data;
  struct QueueNode *next;
} QueueNode;
typedef struct {            // 链式队列
  QueueNode *front, *rear;  // 队列的队头和队尾指针
} LinkQueue;
```

### 链式队列的基本操作

1. 初始化
2. 判空
3. 入队
4. 出队

```cpp
void InitQueue(LinkQueue &Q) {
  Q.front = Q.rear = new QueueNode;  // 建立头结点
  Q.front->next = NULL;
}

bool QueueEmpty(LinkQueue Q) {
  if (Q.front == Q.rear)
    return true;
  else
    return false;
}

void EnQueue(LinkQueue &Q, ElemType x) {
  QueueNode *s = new QueueNode;
  s->data = x;  // 创建新结点，插入到链尾
  s->next = NULL;
  Q.rear->next = s;
  Q.rear = s;
}

bool DeQueue(LinkQueue &Q, ElemType &x) {
  if (Q.front == Q.rear) return false;  // 队列为空
  QueueNode *s = Q.front->next;
  x = s->data;  // 保存队列第一个元素的值
  Q.front->next = s->next;
  if (Q.rear == s) Q.rear = Q.front;  // 若队列中只有一个结点，则删除后为空
  delete s;
  return true;
}
```
