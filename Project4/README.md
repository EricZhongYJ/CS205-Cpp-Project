# CS205 C/C++ Programming - 2022 Fall - Project4

**Name:** 钟元吉(Zhong Yuanji)

**SID:** 12012613

## 1. 项目内容与实现

### 要求：

仅通过c语言对3中的矩阵结构体改进矩阵乘法部分、实现随机矩阵的生成

**注意**(同[Project3](../Project3))：

1. 内置方法与宏定义名称均使用双下划线`__`开始
2. 使用`const`参数保证对非输出矩阵`ret`的传入数据不更改
3. 使用不易重复、随机的浮点数常量`NULLF`和空矩阵`NULLMatrix`来作为无法返回操作结果整数的错误结果
4. 矩阵行、列数、数据索引数使用`size_t`类型

### 实现方法：

* [Project3](../Project3)中的原有方法
* 使用最基础的`i-j-k`循环的无访存优化方法
* 使用`i-k-j`循环的简单访存优化方法
* 使用`k-i-j`循环的全面访存优化方法
* 通过随机种子生成相对固定的(随机)矩阵
* 通过时间种子生成(伪)随机矩阵



## 2. 代码运行

以矩阵操作系统(矩阵计算器)即测试文件的运行为例：

##### 通过命令行编译运行：

运行[TestForData.c](./src/TestForData.c)中的测试(或加上`-O3`优化)

```bash
gcc ./src/MatrixFunc.c ./src/MoreFunc.c ./src/TestForData.c -o TestForData -mavx2 && ./TestForData
```

```bash
gcc ./src/MatrixFunc.c ./src/MoreFunc.c ./src/TestForData.c -o TestForData -mavx2 -O3 && ./TestForData
```

运行[Test.c](./Test.c)中的测试(或加上`-O3`优化)

```bash
gcc ./src/MatrixFunc.c ./src/MoreFunc.c ./Test.c -o Test -mavx2 && ./Test
```

```bash
gcc ./src/MatrixFunc.c ./src/MoreFunc.c ./Test.c -o Test -mavx2 -O3 && ./Test
```



##### 运行测试：

使用`makefile`来编译并运行([TestForData.c](./src/TestForData.c)中的检测例子)：

```bash
make
```

示例参考报告第三部分。

## 3. 文件说明

| 文件名        | 内容解释                                    |
| ------------- | ------------------------------------------- |
| Matrix.h      | Project3-矩阵结构体、宏定义与函数头         |
| MoreFunc.h    | Project4-改进矩阵乘法、生成随机矩阵方法     |
| MatrixFunc.c  | Project3-矩阵结构体有关的函数               |
| MoreFunc.c    | Project4-改进矩阵乘法、生成随机矩阵方法     |
| TestForData.c | Project4-三种矩阵乘法耗时对比               |
| Test.c        | Project4-随机矩阵显示、两种矩阵乘法耗时对比 |
