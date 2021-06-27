---
layout:     post
title:      "数据库复习"
subtitle:   "Database Review"
date:       2021-06-27 23:58:06
author:     "XDong"
header-img: "img/post-bg-wlop-1.jpg"
tags:
    - 复习
    - 数据库
---


# 数据库复习

## 第1章

### 了解数据库管理系统的主要功能

1. 数据定义功能
2. 数据组织、存储和管理
3. 数据操纵功能
4. 数据库的事务管理和运行管理
5. 数据库的建立和维护功能
6. 其他功能

### 理解三级模式和二级映像在数据独立性的作用

- 模式（schema）：逻辑模式，是数据库中全体数据的逻辑结构和特征的描述，是所有用户的公共数据视图。
- 外模式（external schema）：子模式（subschema）或用户模式，它是数据库用户能够看见和使用的局部数据的逻辑结构和特征的描述。
- 内模式（internal schema）：存储模式（storage schema），一个数据库只有一个内模式，它是数据物理结构和存储方式的描述，是数据在数据库内部的组织方式。

- 外模式/模式映像：**保证了数据与程序的逻辑独立性**
- 模式/内模式映像：**保证了物理独立性**

### 掌握简单E-R图的建立

E-R图提供了表示实体型、属性和联系的方法

1. 实体型用矩形表示
2. 属性用椭圆形表示
3. 联系用菱形表示（如果一个联系具有属性，则这些属性也要用无向边与该联系连接起来）

## 第2章

### 掌握在数据表建立时，要有关系完整性约束

关系模型中有三类完整性约束：实体完整性、参照完整性和用户定义的完整性

1. 实体完整性：若属性（一个或一组属性）A是基本关系R的主属性，则A不能取空值
2. 参照完整性：关系模型中的实体之间的联系用关系来表示
3. 用户定义的完整性：针对某一具体应用的数据必须满足的语义要求

### 关系代数在查询时的应用（单表、两表、三表）

#### 集合运算符

- 并：$R \cup S$
- 差：$R - S$
- 交：$R \cap S$
- 笛卡尔积：$R \times S$

#### 专门运算符

- 选择
- 投影
- 连接：等值连接、非等值连接、自然连接
- 除运算

## 第3章

### 掌握SQL语言在查询中的描述

#### 建表

```sql
CREATE TABLE SC(
    Sno CHAR(9),
    Cno CHAR(4),
    Grade SMALLINT,
    PRIMARY KEY(Sno, Cno),
    FOREIGN KEY(Sno) REFERENCES Stduent(Sno),
    FOREIGN KEY(Cno) REFERENCES Student(Cno)
);
```

#### 单表查询

```sql
SELECT Sno, Con
FROM SC;

SELECT DISTINCT Cno
FROM SC
WHERE Age < 20;

SELECT Sname, Sno, Ssex
FROM Student
WHERE Sname LIKE '欧阳_';

-- 姓刘的
SELECT Sname, Sno, Ssex
FROM Student
WHERE Sname LIKE '刘%'

-- ASC升序 DESC降序
SELECT Sno, Grade
FROM SC
WHERE Cno = '3'
ORDER BY Grade DESC, Sno; 
-- Sno默认为升序

SELECT COUNT(DISTINCT Sno)
FROM SC;

SELECT AVG(Grade)
FROM SC
WHERE Cno = '1';

SELECT Cno, COUNT(Sno)
FROM SC
GROUP BY Cno;

SELECT Sno, AVG(Grade)
FROM SC
GROUP BY Sno
HAVING AVG(Grade) >= 90;
```

#### 连接查询

```sql
-- 连接查询
SELECT Student.Sno, Sname
FROM Student, SC
WHERE Student.Sno = SC.Sno AND SC.Cno = '2' AND SC.Grade > 90;

SELECT FIRST.Cno, SECOND.Cpno
FROM Course FIRST, Course SECOND
WHERE FIRST.Cpno = SECOND.Cno;

SELECT Sname
FROM Student
WHERE Sno IN(
    SELECT Sno
    FROM SC
    WHERE Cno = '2'
);
```

#### 嵌套查询

```sql
-- 嵌套查询
SELECT Sname
FROM Student
WHERE Sno IN (
    SELECT Sno
    FROM SC
    WHERE Cno = '2'
);

SELECT DISTINCT JNO
FROM SPJ
WHERE PNO != (
    SELECT DISTINCT PNO
    FROM S, SPJ
    WHERE S.CITY = '天津' AND S.SNO = SPJ.SNO
);
```

### 视图在数据独立性的作用，会建立简单视图，完成例如查询语句的作用（例如视图可以表述某系学生的课程后和成绩）

视图是从一个或几个基本表（或视图）导出的表，它与基本表不同，是一个虚表。

#### 视图的作用

1. 视图能简化用户操作
2. 视图使用户能以多种角度看待同一数据
3. **视图对重构数据库提供了一定程度的逻辑独立性**
4. 视图能够对机密数据提供安全保护
5. 适当的利用视图可以更清晰地表达查询

#### 建立简单视图

```sql
CREATE VIEW IS_S1(Sno, Sname, Grade)
AS
SELECT Stduent.Sno, Sname, Grade
FROM Student, SC
WHERE Sdept = 'IS' AND Stduent.Sno = SC.Sno AND SC.Cno = '1';

CREATE VIEW IS_S2(Cno, Grade)
AS
SELECT Cno, Grade
FROM SC;
```

### 第4章

#### 用户身份鉴别

该方法由系统提供一定的方式让用户标识自己的名字或身份。每次用户要求进入系统时，由系统进行核对，通过鉴定后才能提供系统的使用权

分为以下四种方法：

1. 静态口令鉴别
2. 动态口令鉴别
3. 生物特征鉴别
4. 智能卡鉴别

#### 存储控制

通过**定义用户权限**和**合法权限检查**确保只有合法权限的用户访问数据库，所有未授权的人员无法存取数据

##### 自主存取控制方法

在自主存取控制方法中，用户对于不同的数据库对象有不同的存取权限，不同的用户对同一对象也有不同的权限，而且用户还可将其拥有的存取权限转授给其他用户。因此自主存取控制非常灵活。

GRANT授权语句：

```sql
GRANT SELECT
ON TABLE Stduent
TO U2, U3;

GRANT UPDATE(Sno), SELECT
ON TABLE SC
TO PUBLIC
WITH GRANT OPTION;
```

REVOKE收回语句：

```sql
REVOKE SELECT
ON TABLE SC
FROM PUBLIC;
```

##### 强制存取控制方法

在强制存取控制方法中，每一个数据库对象被标以一定的密级，每一个用户也被授予某一个级别的许可证。对于任意一个对象， 只有具有合法许可证的用户才可以存取。强制存取控制因此相对比较严格。

#### 视图机制

为不同的用户定义视图，通过视图机制把要保密的数据对无权存取的用户隐藏起来，从而自动地对数据提供一定程度的安全保护。

#### 审计

建立审计日志，把用户对数据库的所有操作自动记录下来放入审计日志中，DBA可以利用审计跟踪的信息，重现导致数据库现有状况的一系列事件，找出非法存取数据的人，时间和内容等。

#### 数据加密

对存储和传输的数据进行加密处理，从而使得不知道解密算法的人无法获知数据的内容。

## 第5章

