# CS205 C/C++ Programming - 2022 Fall - Project2

**Name:** 钟元吉(Zhong Yuanji)

**SID:** 12012613

## 1. 项目内容与实现

### 要求：

实现一个通过输入传参、支持加、减、乘、除、余数、乘方、括号、取整、三角函数、对数等数学计算，以及参数赋值与调用的计算器

#### **注意：**

1. 任意位置的空格均会被忽略；
2. 程序中统一采用科学计数法进行输出；
3. 函数中**可以不使用括号**(下面写法省略括号)；
4. 数字与(参数、函数)、(参数、函数)与(参数、函数)之间的乘法**可以不写乘号**（但**数字与数字之间的乘号不可省略**）。

### 实现：

* 正常输入:`-12.34`、科学计数法输入：标准:`-1.234e1`、不标准:`123.4e-1`
* 加:`a+b`、减:`a-b`、乘:`a*b`或`a(b)`(当b不是数字的时候还可以写作`ab`或`(a)b`)、除:`a/b`、括号`(a)`
* 余数:`a%b`、乘方:`a^b`、开平方:`sqrt(a)`或`sqrt a`
* 阶乘`a!`
* 向下取整:`floor a`或`floor(a)`、向上取整:`ceil a`、绝对值:`abs a`
* 三角函数:`sin a`,`cos a`,`tan a`,`asin a`,`acos a`,`atan a`
* 对数:`log a`、指数:`exp a`
* 常数：π:`pi`、自然对数底数`e`或`E`（均精确到100位小数）
* 结果储存：`ans`、自定义变量:`num = 1`
* 退出：`q`

### 错误检验：

对输入的代码进行一下类型的错误检验

```c++
// Store error type and position, type:
//  (format:) 1: invalid variable name     2: no input                    3: start with equal sign
//            4: invalid char              5: different number of ()      6: wrong number of nums or ops
//            7: number follow variable    8: operator follow operator / input start with operator
//  (number:) 9: more than one dots        10: float exponent             11: more than one 'e'
// (compute:) 12: divide by zero           13: include inf or nan         14: invalid operator
```

## 2. 代码运行

使用`cmake`来编译并运行：

```bash
cmake . & make
./Project2.out
```

示例参考报告第三部分。
