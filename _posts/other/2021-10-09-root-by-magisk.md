---
layout:     post
title:      "红米K20 Pro获得root权限"
subtitle:   "通过 TWRP 安装 Magisk"
date:       2021-10-09 00:34:38
author:     "XDong"
header-img: "img/post-bg-magisk.png"
tags:
    - Magisk
    - TWRP
    - Root
    - 刷机
---

# 记一次刷机过程

起因：玩pvz途中，突然想要刷下金币，但是游戏广告突然看不了了，就萌生了开挂的念头🤣，于是就在网上寻找一些root的教程

## [一个合格的教程](https://www.bilibili.com/video/BV1Ly4y1u7YE "【Magisk卡刷】这应该是B站最详细的Root教程！！!")

<div style="position: relative; padding: 30% 45%;">
<iframe style="position: absolute; width: 100%; height: 100%; left: 0; top: 0;" src="https://player.bilibili.com/player.html?aid=803520573&bvid=BV1Ly4y1u7YE&cid=353487269&page=1&as_wide=1&high_quality=1&danmaku=1" frameborder="no" scrolling="no" allowfullscreen="true">
</iframe>
</div>

在这个视频中，获得root权限一共有三步

1. 解BL锁
2. 刷入[TWRP](https://twrp.me/)(一个第三方Recovery)
3. 通过TWRP刷入Magisk

### 解BL锁

很简单的一步，百度即可

### 刷入TWRP

在[TWRP](https://twrp.me/)中下载对应版本的TWRP即可

### 刷入Magisk

通过TWRP刷入Magisk，以获得root权限

参考[通过 TWRP 安装 Magisk 操作指南]("https://miuiver.com/install-magisk-via-twrp/")一文

## 自己的一些尝试

- 直接安装Magisk

### 直接安装Magisk

参考[小米手机获取 Root 权限教程（详细图文）](https://miuiver.com/how-to-root-xiaomi-phone/)一文

照着教程操作，直接安装Magisk失败，碰到错误`FAILED (remote: 'Error flashing partition : Volume Full')`，网上也找不到对应的解决办法，只能退而求其次，通过TWRP刷入Magisk

## 总结

虽然成功root并开挂了，但是root后银行软件会有警告，最后还是刷了回去🤣

## 参考链接

- [【Magisk卡刷】这应该是B站最详细的Root教程！！!_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1Ly4y1u7YE?zw)
- [申请解锁小米手机 (miui.com)](https://www.miui.com/unlock/index.html)
- [TeamWin - TWRP](https://twrp.me/)
- [topjohnwu/Magisk: The Magic Mask for Android (github.com)](https://github.com/topjohnwu/Magisk)
- [小米手机获取 Root 权限教程（详细图文） – MIUI历史版本 (miuiver.com)](https://miuiver.com/how-to-root-xiaomi-phone/)
- [yanbuyu/XiaomiCTSPass: 强制小米设备通过谷歌CTS测试 (github.com)](https://github.com/yanbuyu/XiaomiCTSPass)
- [MIUI 国际版/EU 版本地化教程 - 小米钱包篇 - 少数派 (sspai.com)](https://sspai.com/post/60065)
- [Home - GameGuardian](https://gameguardian.net/ "Awesome Game Cheat")
