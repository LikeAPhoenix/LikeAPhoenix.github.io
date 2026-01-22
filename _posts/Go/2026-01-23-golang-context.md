---
layout: post
title: "Golang Context"
subtitle: "Context总结"
date: 2026-01-23
author: "XDong"
header-img: "img/post-bg-wlop-1.jpg"
tags:
    - Go
---

在 Go 的工程实践里，`context.Context` 是最关键的基础设施之一。它用于描述请求的生命周期，贯穿 client -> server -> 下游服务，解决“超时、取消、请求级数据传播”的问题。本文会系统介绍 ctx 的概念、常见用法，并解释“client 取消 ctx 为什么会导致 server 的 `Request.Context()` 取消”的原因与示例。

## 什么是 Context

`context.Context` 是一个接口，主要提供三类能力：

- **取消信号**：通过 `Done()` 通知下游“我不需要了”。
- **截止时间**：通过 `Deadline()` 和 `Err()` 表示超时或取消。
- **请求级数据**：通过 `Value()` 携带必要的请求元数据（例如 request-id）。

核心思想：**在请求链路中层层传递 ctx，让每一层都能感知取消与超时**。

## 常见创建方式

```go
ctx := context.Background()
// 或者用于测试
ctx := context.TODO()
```

派生子 context：

```go
ctx, cancel := context.WithCancel(parent)
defer cancel()

ctx, cancel := context.WithTimeout(parent, 2*time.Second)
defer cancel()

ctx, cancel := context.WithDeadline(parent, time.Now().Add(2*time.Second))
defer cancel()
```

携带请求值：

```go
type ctxKey string

const requestIDKey ctxKey = "request_id"

ctx := context.WithValue(parent, requestIDKey, "abc-123")
```

注意：**一定要 `defer cancel()`**，避免 goroutine 泄漏；`WithValue` 只用于请求级元数据，不要塞业务对象或可变状态。

## 为什么 client 取消 ctx 会导致 server 的 Request.Context 取消

在 `net/http` 中，`server` 侧的 `Request.Context()` 与底层连接生命周期绑定：

- client 侧取消 ctx -> `http.Client` 会中止请求（关闭 body 或断开连接）。
- server 侧感知到连接被关闭或请求中断，`http.Server` 会触发该请求的 ctx 取消。
- 于是 server 的 handler 中 `r.Context().Done()` 会被关闭，`r.Context().Err()` 变为 `context.Canceled`。

这意味着：**client 中断请求，server 可以快速停止正在进行的耗时操作**，节省资源。

下面是一个实际示例。

## 示例：client 取消，server 感知并停止

### server 端

```go
package main

import (
    "log"
    "net/http"
    "time"
)

func main() {
    http.HandleFunc("/slow", func(w http.ResponseWriter, r *http.Request) {
        select {
        case <-time.After(5 * time.Second):
            w.Write([]byte("done"))
        case <-r.Context().Done():
            log.Printf("request canceled: %v", r.Context().Err())
        }
    })

    log.Fatal(http.ListenAndServe(":8080", nil))
}
```

### client 端

```go
package main

import (
    "context"
    "log"
    "net/http"
    "time"
)

func main() {
    ctx, cancel := context.WithTimeout(context.Background(), time.Second)
    defer cancel()

    req, _ := http.NewRequestWithContext(ctx, http.MethodGet, "http://localhost:8080/slow", nil)
    if _, err := http.DefaultClient.Do(req); err != nil {
        log.Printf("client error: %v", err)
    }
}
```

运行后，你会看到 server 端打印 `request canceled`。这就是 client 取消 ctx 导致 server `Request.Context()` 被取消的典型表现。

## Gin 中的 gin.Context 与 context.Context

Gin 的 `*gin.Context` 不是 `context.Context` 的实现，而是框架自定义的请求上下文，包含路由参数、请求/响应对象、绑定与渲染等能力。它和标准库 `context.Context` 的关系主要体现在以下几点：

- `gin.Context` 内部持有 `*http.Request`，因此**真正的取消与超时信号来自 `c.Request.Context()`**。
- 在 Gin handler 中，你仍然需要把 `c.Request.Context()` 透传给下游函数，确保超时/取消生效。
- Gin 自身也提供 `c.Set` / `c.Get` 用于在中间件间传值，这与 `context.WithValue` 不同，作用域也不同。

一个简化示例：

```go
func handler(c *gin.Context) {
    ctx := c.Request.Context()

    // 透传标准 context 给下游
    user, err := queryUser(ctx, "u123")
    if err != nil {
        c.JSON(500, gin.H{"error": "db error"})
        return
    }

    c.JSON(200, gin.H{"user": user})
}
```

**要点**：
- `gin.Context` 负责框架功能，`context.Context` 负责取消/超时与链路传播。
- 不要把 `*gin.Context` 作为 `context.Context` 传入下游函数，正确做法是 `c.Request.Context()`。

## 实际工程中 ctx 的常见用法

### 1) HTTP handler 中的请求链路传递

```go
func handler(w http.ResponseWriter, r *http.Request) {
    ctx := r.Context()

    // 透传给下游: db / rpc / cache
    user, err := queryUser(ctx, "u123")
    if err != nil {
        http.Error(w, "db error", http.StatusInternalServerError)
        return
    }

    fmt.Fprintf(w, "user=%s", user)
}

func queryUser(ctx context.Context, id string) (string, error) {
    ctx, cancel := context.WithTimeout(ctx, 100*time.Millisecond)
    defer cancel()

    // 这里是伪代码
    if err := db.QueryContext(ctx, "SELECT ...", id); err != nil {
        return "", err
    }
    return "ok", nil
}
```

**要点**：
- 在 handler 入口拿 `r.Context()`。
- 下游统一使用 `QueryContext` / `Do(ctx)`，让超时和取消自然生效。

### 2) 并发任务协作 + 快速失败

```go
func fetchAll(ctx context.Context, ids []string) error {
    g, ctx := errgroup.WithContext(ctx)

    for _, id := range ids {
        id := id
        g.Go(func() error {
            return fetchOne(ctx, id)
        })
    }

    return g.Wait()
}
```

**要点**：
- 一个 goroutine 出错或 ctx 取消，其他任务会收到 `ctx.Done()`。
- 非常适合“多路调用 + 快速失败”的场景。

### 3) 记录请求级 metadata（如 Request-ID）

```go
type ctxKey string

const requestIDKey ctxKey = "request_id"

func withRequestID(ctx context.Context, id string) context.Context {
    return context.WithValue(ctx, requestIDKey, id)
}

func requestIDFrom(ctx context.Context) string {
    if v := ctx.Value(requestIDKey); v != nil {
        if s, ok := v.(string); ok {
            return s
        }
    }
    return ""
}
```

**要点**：
- key 使用自定义类型，防止冲突。
- 只放轻量级、只读的元数据。

## 使用建议和常见误区

- **一定传 ctx**：公共函数优先签名 `func(ctx context.Context, ...)`。
- **及时 cancel**：`WithTimeout/WithCancel` 都要 `defer cancel()`。
- **不要滥用 WithValue**：不要把大对象或业务状态放进 ctx。
- **不要在后台任务里使用请求 ctx**：后台任务应基于 `context.Background()` 或独立 ctx。

## 小结

`context.Context` 是 Go 服务端工程的“请求生命线”。当 client 取消请求时，server 端 `Request.Context()` 会被取消，允许服务端及时中止耗时任务，节省资源并提高整体稳定性。建立起“请求从入口到下游都带 ctx”的习惯，可以让系统更可靠、更可控。

如果你想进一步扩展，可以结合 trace、metrics 或 gRPC 的 metadata，把 ctx 贯穿整个可观测性链路。
