# CS205 C/C++ Programming - 2022 Fall - Project1

**Name:** 钟元吉(Zhong Yuanji)

**SID:** 12012613

## 1. 项目内容与实现

### 要求：

实现一个通过命令行传参的两位(整数或浮点数)数乘法计算器

### 实现：

* 浮点数判断
* 错误判断
* 整数任意精度乘法
* 浮点数乘法

### 错误检验：

对输入的代码进行以下类型的错误检验

| 错误类型 |                            |                      |
| :------: | -------------------------- | -------------------- |
| 命令行输入错误 | 1. 输入参数不为2           |                      |
| 数字错误 | 2. 存在不合理的字符        | 3. 存在至少2个小数点 |
|          | 4. 指数上有小数点          | 5. 数字以e或E开始    |
|          | 6. 存在至少2个指数符号e或E | 7. 存在不合理的减号  |

```c++
// Error type:
// Please check the number of inputs. It must be 2.
// The # input cannot be interpret as numbers! (invalid char)
// There are more than one dots in the # number.
// The exponent of the # number cannot be a float number.
// The first char in the # number cannot be 'e' or 'E'.
// There are more than one 'e' or 'E' in the # number.
// There is an incorrect minus signal in the # number.
```

### 其他亮点：

程序会告知**具体错误提示**，例如：

```
Input: ./mul -2.5e10 --2
Output: There is an incorrect minus signal in the second number.
```



## 2. 代码运行

使用`g++`来编译并运行：

```bash
g++ ./Project1/source.cpp -o mul
./mul 2 3
```

示例参考报告第三部分。

