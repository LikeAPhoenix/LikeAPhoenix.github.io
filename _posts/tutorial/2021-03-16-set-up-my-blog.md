---
layout:     post
title:      "关于我的博客"
subtitle:   "这篇博客是给以后的自己的教程"
date:       2021-03-16 19:29:15
author:     "XDong"
header-img: "img/post-bg-eva-q-asuka.png"
tags:
    - 教程
---


# XDong Blog

XDong Blog的模板来自于[Hux Blog](http://huangxuan.me/)

github仓库为：[repo](https://github.com/Huxpro/huxpro.github.io)

XDong Blog clone的分支为[dependabot/npm_and_yarn/lodash-4.17.19](https://github.com/Huxpro/huxpro.github.io/tree/dependabot/npm_and_yarn%2Flodash-4.17.19)

## github page

XDong Blog使用的是github page，并绑定了自己的域名[xdong.site](https://xdong.site/)

## jekyll

>Jekyll 是一个简单的博客形态的静态站点生产机器。它有一个模版目录，其中包含原始文本格式的文档，通过一个转换器（如 Markdown）和我们的 Liquid 渲染器转化成一个完整的可发布的静态网站，你可以发布在任何你喜爱的服务器上。Jekyll 也可以运行在 GitHub Page 上，也就是说，你可以使用 GitHub 的服务来搭建你的项目页面、博客或者网站，而且是完全免费的。

jekyll教程：

- [到底如何使用jekyll发布博客?](https://www.zhihu.com/question/35248182/answer/1081510662)
- [Jekyll + Github Pages 博客搭建入门](https://www.jianshu.com/p/9f198d5779e6)

## 部分_config.yml配置说明

```yml
# MathJax rendering for layout:page (e.g. post preview)
page-mathjax: true
# 说明：是否对数学公式进行渲染（渲染的话显示的公式在网页加载的时候会出现变化）（不过我现在还不知道有什么用）
```

## 数学公式

在_includes/head.html文件中添加代码

```html
    <!-- 数学公式 -->
    <script type="text/x-mathjax-config">
        MathJax.Hub.Config({
            tex2jax: {
                skipTags: ['script', 'noscript', 'style', 'textarea', 'pre', 'code'],
                inlineMath: [ ['$','$'] ],
                <!--不需要displayMath(行外公式 我也不知道为什么)-->
                processEscapes: true
            },
            TeX: {
                equationNumbers: {
                    autoNumber: "AMS"
                },
                <!--自定义的宏-->
                Macros: {
                    lbrace: "\\{",
                    rbrace: "\\}"
                }
            }
        });
    </script>
```

### 自定义宏

在mathjax中，公式中的"{"要用"\\\\{"来表示，但是vscode中的"{"却是用"\\{"来表示，这就导致博客和vscode markdown中总会有一个无法正确显示公式

查询资料看到了[stackoverflow](https://stackoverflow.com/questions/41312777/mathjax-curly-brackets-dont-show-up-using-jekyll/41312791)中有人用自定义宏的方式解决了这样的问题

最后我通过在mathjax和vscode markdown-all-in-one中定义一个同名的宏解决了问题

#### mathjax

mathjax中宏的用法[MathJax文档](http://docs.mathjax.org/en/latest/input/tex/macros.html)

```html
Macros: {
    lbrace: "\\{",
    rbrace: "\\}"
}
```

#### vscode markdown-all-in-one

KaTeX中宏的用法[Markdown+Math](https://marketplace.visualstudio.com/items?itemName=goessner.mdmath)

```json
"markdown.extension.katex.macros": {
    "\\lbrace": "\\{",
    "\\rbrace": "\\}"
}
```

## 评论框

以前用的是[disqus](https://disqus.com/)，但是disqus的评论框不能免费去广告

现在已经换成[gitalk](https://github.com/gitalk/gitalk)

gitalk教程：

- [Add Gitalk to Your Jekyll Blog](https://aerolith.ink/2018/08/25/Gitalk/)

## 建站时间与网站计数

首先引入在footer.html中引入脚本

```html
<!-- 不蒜子脚本 -->
<script async src="//busuanzi.ibruce.info/busuanzi/2.3/busuanzi.pure.mini.js">
</script>
```

然后添加span

```html
<!-- 站点计时 -->
<span id='site_time'></span>
<br>
<!-- 不蒜子计数 -->
<span id="busuanzi_container_site_uv">
    👤Total Visitors <span id="busuanzi_value_site_uv"></span> |
</span>
<span id="busuanzi_container_site_pv">
    👀Total Visits <span id="busuanzi_value_site_pv"></span>
</span>
<br>
```

编写js计时函数

```html
<!-- 站点计时 -->
<script>
    function siteTime() {
        window.setTimeout("siteTime()", 1000);
        var seconds = 1000;
        var minutes = seconds * 60;
        var hours = minutes * 60;
        var days = hours * 24;
        var years = days * 365;
        var today = new Date();
        var todayYear = today.getFullYear();
        var todayMonth = today.getMonth() + 1;
        var todayDate = today.getDate();
        var todayHour = today.getHours();
        var todayMinute = today.getMinutes();
        var todaySecond = today.getSeconds();
        var t1 = Date.UTC(2020, 10, 24, 00, 00, 00);  //此处填写建站时间
        var t2 = Date.UTC(todayYear, todayMonth, todayDate, todayHour, todayMinute, todaySecond);
        var t2 = Date.UTC(todayYear, todayMonth, todayDate, todayHour, todayMinute, todaySecond);
        var diff = t2 - t1;
        var diffYears = Math.floor(diff / years);
        var diffDays = Math.floor((diff / days) - diffYears * 365);
        var diffHours = Math.floor((diff - (diffYears * 365 + diffDays) * days) / hours);
        var diffMinutes = Math.floor((diff - (diffYears * 365 + diffDays) * days - diffHours * hours) / minutes);
        var diffSeconds = Math.floor((diff - (diffYears * 365 + diffDays) * days - diffHours * hours - diffMinutes * minutes) / seconds);
        var title = '{{ site.title }}'  // 获取名称
        document.getElementById("site_time").innerHTML =
            "⏱️" + title + " already run " + diffYears + " years " + diffDays + " days " + diffHours + " hours " + diffMinutes + " mins " + diffSeconds + " s";
    }
    siteTime();
</script>
```

## jekyll livereload

>LiveReload is available as an option during development: with jekyll serve --livereload no more manual page refresh.

正常情况下，可以通过`jekyll serve --livereload`来使用livereload功能

由于版本问题`eventmachine`版本问题，要在`Gemfile`中添加一行代码

```
gem 'eventmachine', '1.2.7', git: 'https://github.com/eventmachine/eventmachine.git', tag: 'v1.2.7'
```

>⚠️
>但是在Hux Blog中，`livereload`功能没有作用，在新的jekyll项目是可以起作用的

### 百二秦关终属楚

最后终于可以使用livereload了！！！😊😊😊

1. 查看控制台报错，发现是`cors`的原因
2. google了下原因，修改了`sw.js`
中189行为```const fetched = fetch(getCacheBustingUrl(event.request), { cache: "no-store", mode: "no-cors"});```
3. 已经可以成功刷新，修改为延迟自动刷新，在`sw-registration.js`中增加一行
```setTimeout(()=>location.reload(), 3000)```

## cdn资源总结

- [lib.baomitu.com](https://cdn.baomitu.com/)用于大部分js文件，如Mathjax，fastclick，部分css文件，如font-awesome，原[cdnjs.cloudflare.com](https://cdnjs.cloudflare.com/)的国内访问不流畅
- alicdn用于bilibili图标
- [cdn.jsdelivr.net](https://www.jsdelivr.com/)用于gitalk的js文件

参考：

- [不蒜子 - 极简网页计数器](http://busuanzi.ibruce.info/)
- [Mike Lyou Blog](https://blog.mikelyou.com/2020/08/18/busuanzi-visitor-counts-and-sitetime/)
