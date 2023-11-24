# COMMENT TO DOCS

## Introduction

这个库（或者说工具）可以帮助你将C接口的注释提取出来，然后将注释转换到Markdown格式的文档。

首先它基于[LLVM-LibTooling](https://clang.llvm.org/docs/LibTooling.html)提取AST，导出注释。一个C++编写的后端将这些数据转换到json格式，然后你可以选择将这些数据转换到Markdown，或是自行编写转换代码将其转换到你想要的任何数据格式。

如果你不熟悉c/C++，这个项目中还提供了Python和JavaScript的语言绑定。

**支持哪些语言:**

- [x] `C`
- [ ] `C++`

**支持哪些类型的文件：**

- [x] `.h`
- [ ] `.cpp`, `.c``

## Origin of Project
