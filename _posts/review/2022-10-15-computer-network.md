---
layout:     post
title:      "计算机网络背记知识点整理"
subtitle:   ""
date:       2022-10-15 13:00:31
author:     "XDong"
header-img: "img/post-bg-wlop-1.jpg"
tags:
    - 计算机网络
---

# 计算机网络

## 第1章 计算机网络体系结构

1. 计算机网络的概念：计算机网络是一个将分散的、具有独立功能的计算机系统，通过通信设备与线路连接起来，由功能完善的软件实现资源共享和信息传递的系统。简而言之，计算机网络就是一些互联的、自洽的的计算机系统的集合。
2. 服务数据单元（SDU）：为完成用户所要求的功能而应传送的数据。第$n$层的服务数据记为$n$-SDU。
3. 协议控制信息（PCI）：控制协议操作的信息。第$n$层的协议控制信息记为$n$-PCI。
4. 协议数据单元（PDU）：对等层次之间传送的数据单位称为该层的PDU。第$n$层的协议数据单元记为$n$-PDU。在实际的网络中，每层的协议数据单元都有一个通俗的名称，物理层的为**比特**，数据链路层的为**帧**，网络层的为**分组**，传输层的为**报文段**。
5. 协议：协议是规则的集合，由语法、语义和同步三部分组成。
   1. 语法规定了传输数据的格式。
   2. 语义规定了所要完成的功能，即需要发出何种控制信息，完成何种动作及做出何种应答。
   3. 同步规定了执行各种操作的条件、时序关系等，即事件实现顺序的详细说明。
6. 接口：接口是同一结点内相邻两层间交换信息的连接点，是一个系统内部的规定。
7. 服务：是指下层为紧邻的上层提供的功能调用，它是垂直的。
8. 传输控制协议（TCP）。它是面向连接的，数据传输的单位为报文段，能够提供可靠的交付。
9. 用户数据包协议（UDP）。它是无连接的，数据传输的单位是用户数据报，不保证提供可靠的交付，只能提供“尽最大努力交付”。

## 第2章 物理层

1. ![数据包服务和虚电路服务的比较](/img/review/compture-network-table-2.1.png)

### 电路交换、报文交换与分组交换

![三种数据交换方式的比较](/img/review/compture-network-chart-2.4.png)

#### 电路交换

电路交换技术分为三个阶段：连接建立、数据传输、连接释放。

电路交换技术的优点如下：

1. 通信时延小
2. 有序传输
3. 没有冲突
4. 适用范围广。既适用于传输模拟信号，又适用于传输数字信号
5. 实时性强
6. 控制简单

电路交换技术的缺点如下：

1. 建立连接时间长
2. 线路独占
3. 灵活性差
4. 难以规格化

#### 报文交换

数据交换的单位是报文，报文携带有目标地址、源地址等信息。报文交换在交换节点时采用的是存储转发的传输方式。

报文交换技术的优点如下：

1. 无需建立连接
2. 动态分配线路
3. 提高线路可靠性。如果某条传输路径发生故障，可重新选择另一条路径传输数据
4. 提高线路利用率
5. 提供多目标服务

报文交换技术的缺点如下；

1. 由于数据进入交换节点后要经历存储、转发这个过程，因此会引起转发时延
2. 报文交换对报文的大小没有限制，这就要求网络结点需要有较大的缓存空间

#### 分组交换

同报文交换一样，分组交换也采用了存储转发方式，但解决了报文交换中大报文传输的问题。分组交换限制了每次传送的数据块大小的上限，把大的数据块划分为合理的小数据块，再加上一些必要的控制信息，构成分组（Packet）。

分组交换的优点如下：

1. 无建立时延
2. 线路利用率高
3. 简化了存储管理（相对于报文交换）。因为分组的长度固定，相应的缓冲区的大小也固定，再交换节点中存储器的管理通常被简化为缓冲区的管理，相对比较容易
4. 加速传输。分组是逐个传输的，可以使后一个分组的存储操作与签一个分组的转发操作并行，这种流水线方式减少了报文的传输时间。此外，传输一个分组所需的缓冲区比传输一次报文所需的缓冲区小得多，这样因缓冲区不足而等待发送的概率及时间也必然少得多
5. 减少了出错概率和重发数据量

分组交换的缺点如下：

1. 存在传输时延
2. 需要传输额外的信息量
3. 当分组交换采用数据报服务时，可能会出现失序、丢失或重复分组的情况，分组到达目的结点时，要对分组按编号进行排序工作，因此很麻烦。若采用虚电路服务，虽无失序问题，但有呼叫建立、数据传输和虚电路释放三个过程