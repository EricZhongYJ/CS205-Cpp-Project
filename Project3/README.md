# CS205 C/C++ Programming - 2022 Fall - Project3

**Name:** 钟元吉(Zhong Yuanji)

**SID:** 12012613

## 1. 项目内容与实现

### 要求：

仅通过c语言实现一个支持加、减、乘、数乘、行列式、求逆等运算的矩阵结构体的动态库

**注意：**

1. 内置方法与宏定义名称均使用双下划线`__`开始
2. 使用`const`参数保证对非输出矩阵`ret`的传入数据不更改
3. 使用不易重复、随机的浮点数常量`NULLF`和空矩阵`NULLMatrix`来作为无法返回操作结果整数的错误结果
4. 由于不同操作系统清除命令行显示的命令与指针储存大小不同，程序通过宏操作识别是否为`Win32`进行区分`Window` (`"cls"`清屏，指针4字节)和`Linux` (`"clear"`清屏，指针8字节)

### 实现方法：

按头文件[`Matrix.h`](./inc/Matrix.h)中的函数顺序，详细函数头请参考[头文件](./inc/Matrix.h)。

* 通过给定行数、列数与一维浮点数数据指针来构造矩阵结构体
* 通过含`[ ,;]`的**字符数组**来构造矩阵结构体，例如：

```c
Matrix *mat = createMatrixFromStr("[1,2;3 4]");
```

* 删除矩阵结构体：将释放**该结构体**及其**浮点数数组**对应的内存
* **输出为字符串**：当行数和列数非零时，**需要手动释放字符数组的内存**
* 复制矩阵结构体：重新复制一份数组，地址值不同
* 取**子矩阵**：包含开始的行和列，不包括结束的行和列，地址值不同
* 取**余子式矩阵**：即不包括指定行和列的矩阵
* 矩阵与矩阵的和、差、积
* 矩阵与数字的和、差、数乘(积)
* 矩阵的最小、最大值：为了避免与`min,max`函数的冲突，这里函数名使用`minOfMatrix,maxOfMatrix`
* 矩阵的**行列式**`det`与**逆矩阵**`inv`
* 矩阵的**转置**`transpose`与**旋转90度**`rotate90`
* 给出了含有矩阵操作的**矩阵操作系统**，可以保存10个自定义矩阵，见文件[`Test.c`](./src/Test.c)

### 错误检验：

对输入的代码进行以下类型的错误检验

| 错误类型                                           | 对应输出整数 |
| -------------------------------------------------- | :----------: |
| 运算中输入的第一个矩阵或其数据是空指针             |      -1      |
| 运算中输入的第二个矩阵或其数据是空指针             |      -2      |
| 运算中输出矩阵是空指针                             |      -3      |
| 运算中输入的两个矩阵行数或列数错误，不满足运算要求 |      -4      |
| 取子矩阵或余子式时输入的行数或列数越界或有误       |      -5      |
| 求逆矩阵时，矩阵不可逆                             |      -6      |

```c
// Return int:  1:sucessful
//             -1:input Matrix mat is NULL pointer
//             -2:input Matrix oth is NULL pointer
//             -3:output Matrix ret is NULL pointer
//             -4:the size of input Matrix is wrong
//             -5:the input float row or col is wrong
//             -6:the Matrix is not invertible
```

### 其他亮点：

矩阵操作系统(矩阵计算器)通过输入数字来进行对应操作，显示的提示如下：

```
Matrix Calculator:
Operation:
        1:Define the matrix                     2:View the matrix
        3:Get the submatrix                     4:Get cofactor matrix
        5:Add two matrices                      6:Subtract two matrices
        7:Add matrix and scalar                 8:Subtract matrix and scalar
        9:Multiply two matrices                 10:Multiply matrix and scalar
        11:Get minimal of matrix                12:Get maximal of matrix
        13:Get determinant of matrix            14:Get inverse of matrix
        15:Transpose the matrix                 16:Rotate 90 degree on the matrix
        q:quit
```



## 2. 代码运行

以矩阵操作系统(矩阵计算器)即测试文件的运行为例：

##### 生成动态链并运行：

```bash
gcc -shared -fPIC ./MatrixFunc.c -o libMatrix.so
gcc ./Test.c -o CTask -L. -lMatrix
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH # Linux
./CTask
```

第二行最后一个参数可以改为`libMatrix.so`

##### 运行测试：

使用`makefile`来编译并运行：

```bash
make
```

示例参考报告第三部分。

## 3. 文件说明

| 文件名       | 内容解释                           |
| ------------ | ---------------------------------- |
| Matrix.h     | 矩阵结构体、宏定义与函数头         |
| MatrixFunc.c | 矩阵结构体有关的函数               |
| Test.c       | 交互式矩阵计算器的实现             |
| Demo1.c      | Part 3示例1:基本要求的实现         |
| Demo2.c      | Part 3示例2:对错误输入的判断       |
| README.md    | 项目简述                           |
| report.pdf   | 项目报告                           |
| makefile     | 生成交互式矩阵计算器的makefile文件 |

