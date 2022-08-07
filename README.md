# iample language
## 简介
这是一个类似[BF](https://zhwiki.ruiprime.cn/wiki/Brainfuck)的深奥的编程语言，具有一些常见的指令，如输入输出、if判断等。

## 十分简单的Hello world!
先放代码(examples\\Hello world.iam)
```
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++> H
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++> e
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++> l
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++> o
++++++++++++++++++++++++++++++++> Space
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++> w
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++> r
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++> d
+++++++++++++++++++++++++++++++++> !
++++++++++> \n

loop count
^>>>>>>>>>>>>>>>=+

|^                                  restart
.>.>..>.>.>.<<.>>>.<<<<.>>>>>.>.>.  print
^>>>>>>>>>>>>>>+ ?<{                loop
```
>个人英语不太好，如果有注释不对的地方请告诉我

可以看到，`iample`主要由`+`、`-`、`>`、`<`、`|`、`?`、`.`等组成的。下表列出了所有符号和对应解释。

| 符号 | 解释 |
|:---:|:---|
| + | 当前寄存器加一 |
| - | 当前寄存器减一 |
| > | 右移指针 |
| < | 左移指针 |
| \| | 记录当前位置 |
| [ | 跳转到下一个“\|” |
| ] | 跳转到上一个“\|”|
| ^ | 重置指针(指向第一个寄存器) |
| = | 重置当前寄存器(设置为0) |
| ? | 判断最后两个寄存器是否满足条件，满足则跳转到前或后的“\|” |
| . | 打印当前寄存器的数值(转换成字符) |
| , | 从键盘输入一个数值存储到当前寄存器|

其他的字符会省略掉。

所以，上面的代码就非常简单了。先存储下`H`、`e`、`l`、`l`、`o`、`<空格>`、`w`、`o`、`r`、`l`、`d`、`!`、`<换行>`的ASCII码值，再按顺序输出就可以了。因为有重复，所有可以省略掉`l`、`o`。在命令行里先转到项目目录，再执行`tcc -run iample.c "examples\Hello world.iam"`就可以看见打印的`Hello world!`了!(我用的是`tcc version 0.9.27 (x86_64 Windows)`如使用其他编译器请自行改变命令。)

为了~~好玩~~增加一些功能，在`loop count`注释后面还设置了打印次数，在`...>>>=`后面有几个加号就打印几次`Hello world!`。注意，因流程问题，0个`+`号或多个`-`号均会打印一个`Hello world!`,类似`do ... while ...`循环。