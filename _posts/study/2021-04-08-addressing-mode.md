---
layout:     post
title:      "数据寻址方式"
subtitle:   "一共7种方法"
date:       2021-04-08 11:51:52
author:     "XDong"
header-img: "img/post-bg-eva-q-asuka.png"
tags:
    - 学习
    - 微机原理
    - 寻址方式
---


<!-- x86asm代码高亮 -->
<link rel="stylesheet" href="/css/styles/gradient-dark.css">
<script src="/js/highlight.pack.js"></script>
<script>hljs.initHighlightingOnLoad();</script>


# 数据寻址方式

数据寻址方式就是形成操作数地址的方法

1. 操作数包含在指令中。这样的数称为 **立即数** ，相应的寻址方式称为 **立即寻址** 方式
2. 操作数在CPU内部的某个寄存器中。相应的寻址方式称为 **寄存器寻址** 方式
3. 操作数在内存储器中，指令中给出操作数在内存储器中的地址信息。在这种情况下，需要操作数在内存中的物理地址才能对它进行存取操作。相应的寻址方式称为 **存储器寻址** 方式
4. 操作数在I/O端口寄存器中。对于端口地址的不同给出方式，就形成不同的端口寻址方式，称为I/O端口寻址方式

## 立即寻址

指令的操作数（地址码）直接给出操作数本身

特点 **无物理地址**

```x86asm
MOV AX, 251    ;将10进制数251送入寄存器AX，251是立即数
MOV AL, '5'
MOV AL, OE8H
MOV AX, 2346H
```

## 寄存器寻址

操作数在CPU内部的通用寄存器中，指令中指定寄存器名

特点 **无物理地址**

```x86asm
MOV AX, CX  ;将16位寄存器CX中的内容送入寄存器AX
MOV DL, BL
```

## 存储器寻址

- 段地址由寄存器给出
- 偏移地址从指令地址码部分计算求得

偏移地址被称为 **有效地址（Effective Address，EA）**
指令地址码字段给出的地址，称为 **形式地址** 或 **位移量（DISP）**

### 直接寻址

操作数在内存中，操作数的有效地址由指令地址码字段直接给出

```x86asm
EA = DISP
```

汇编语言格式

```x86asm
地址表达式
[地址表达式]
[数字表达式]
```

```x86asm
MOV AL, TABLE   ;地址表达式
MOV AL, [TABLE] ;[地址表达式]
MOV AL, [1000H] ;[数字表达式]
```

$[1000H] = DS * 10H + 1000H = 31000H$

### 寄存器间接寻址

操作数在内存中，操作数的有效地址被放在一个寄存器中，该寄存器由指令地址码字段指定，可以使用基址寄存器BX、BP或变址寄存器SI、DI

>使用的寄存器为BX，SI，DI，则操作数默认在数据段中，使用的寄存器位BP，则操作数默认在堆栈段中

汇编语言格式

```x86asm
[基址寄存器名或变址寄存器名]
```

```x86asm
MOV AX, [BX]
MOV AL, [BP]
MOV AX, ES : [DI] ;
MOV AX, [BX]
```

### 寄存器相对寻址

操作数在内存中，操作数的有效地址为基址或变址寄存器与一个位移量之和（或差）

>使用的寄存器为BX，SI，DI，则操作数默认在数据段中，使用的寄存器位BP，则操作数默认在堆栈段中

汇编语言格式

```x86asm
位移量[基址寄存器名或变址寄存器名]
位移量±基址寄存器名或变址寄存器名
```

```x86asm
MOV AX, 20H[SI]
MOV Cl, [BP + 2000H]
MOV AX, STR[BX]
```

### 基制加变址寻址

操作数在内存中，操作数的有效地址是两个指定寄存器的值之和

汇编语言格式

```x86asm
[基址寄存器名][变址寄存器名]
[基址寄存器名+变址寄存器名]
```

```x86asm
MOV AX, [BX][SI]
MOV AX, [BX + SI]
```

### 相对基址加变址寻址

操作数在存储器中（**内存为主存储器**），存储单元的有效地址为一个基址寄存器、一个变址寄存器的内容及指令中指定的8位或16位位移量的和

汇编语言格式

```x86asm
位移量[基址寄存器名][变址寄存器名]
[基址寄存器名+变址寄存器名+位移量]
```

```x86asm
MOV AL, TABLE[BX][SI]
MOV AL, TABLE[BX + SI]
MOV AL, [TABLE + BX + SI]
```