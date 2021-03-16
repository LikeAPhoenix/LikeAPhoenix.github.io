---
layout:     post
title:      "关于我的博客"
subtitle:   "这篇博客是给以后的自己的教程"
date:       2021-03-16 19:29:15
author:     "XDong"
header-img: "img/post-bg-eva-q-asuka-1920x1200.png"
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

现在用的是[disqus](https://disqus.com/)，但是disqus的评论框不能免费去广告

未来打算换成[gitalk](https://github.com/gitalk/gitalk)
