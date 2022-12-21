# CS205 C/C++ Programming - 2022 Fall - Project4

**Name:** 钟元吉(Zhong Yuanji)

**SID:** 12012613

## 1. 项目内容与实现

### 要求：

仅通过C++语言建立对不同数据格式的、支持行列与通道数的矩阵类，实现矩阵软拷贝和硬拷贝的内存管理，实现运算符重载和矩阵类型转换。

**注意**： 

1. 内置宏定义名称均使用双下划线`__`开始
2. 由于使用类模板定义矩阵类，并将类模板函数定义与声明分离，为了避免在关联时无法实例化类模板下的函数，通过直接导入[`Matrix.cpp`](./src/Matrix.cpp)并直接编译运行来调用。
3. 当传入的矩阵类函数中的矩阵参数为空矩阵或不符合运算要求时，通过`cerr`打印对应错误，**不终止程序**，返回空矩阵或值0。
4. 通过圆括号进行索引，索引值为2个(默认为第一个通道0)或3个，索引值不能为负数，索引值越界时返回0，并通过`cerr`打印对应错误。

### 实现方法：

按头文件[`Matrix.hpp`](./inc/Matrix.hpp)中的函数顺序，详细函数头请参考[头文件](./inc/Matrix.hpp)。

* 通过给定行数、列数、一维数据指针(必须是使用new、malloc、calloc创建的)与通道数(默认为1)来构造矩阵类对象
* 数据类型仅支持：bool, char, unsigned char, short, unsigned short, int, unsigned int, long, unsigned long, long long, unsigned long long, float, double, long double.
* 通过`Matrix<int>()`来构造空矩阵(`int`可以换为其他类型)
* 通过含`[ ,;]`的**字符数组**来构造矩阵类对象，例如：

```cpp
Matrix<long> mat = "[1,2;3 4]";
```

* 删除矩阵类对象`.clear()`：根据引用数将**安全释放该矩阵类对象的数据**并将该矩阵类对象**置为空矩阵**
* 软拷贝：直接赋值、使用同类构造函数、使用`sub()`取子矩阵
* 硬拷贝：使用`.copy()`函数拷贝、**隐式转换为不同数据类型的矩阵**、使用`.subCopy()`取子矩阵
* 返回矩阵私有参数：通过`.getRow()`返回行数、`.getCol()`返回列数、`.getChannel()`返回通道数、`.getChannelMat()`返回软拷贝指定通道的矩阵、`(row,col,channel=1)`用圆括号索引矩阵的元素。
* 取**余子式矩阵**：即不包括指定行和列的矩阵(硬拷贝)
* 矩阵与矩阵的比较，支持：==，!=，<，>，<=，>=.
* 矩阵与矩阵、矩阵与数字、数字与矩阵的和、差、积、商，其中矩阵与矩阵的商定义为右乘其逆矩阵。
* **方阵与整数的幂次**，例如：`mat^2 = mat * mat`，`mat^0 = Id`，`mat^(-2) = mat.inv() * mat.inv()`，其中`mat`不是方阵时报错(不退出程序返回空矩阵)
* 矩阵的最小、最大值：`.min()`，`.max()`
* 矩阵的**行列式**`.det()`与**逆矩阵**`.inv()`
* 矩阵的**转置**`.transpose()`与**旋转90度**`.rotate90()`



## 2. 代码运行

##### 运行测试：

使用`makefile`来编译并运行([Test0.cpp](./src/Test0.cpp)中的检测例子，相当于上面第一个操作)：

```bash
make
```

或使用命令行直接编译运行[`Test0.cpp`](./src/Test0.cpp)、[`Test1.cpp`](./src/Test1.cpp)、[`Test2.cpp`](./src/Test2.cpp)：

```bash
g++ ./src/Test0.cpp -o Test1 -w & ./Test0
g++ ./src/Test1.cpp -o Test1 -w & ./Test1
g++ ./src/Test2.cpp -o Test2 -w & ./Test2
```

示例参考报告第三部分。



## 3. 文件说明

| 文件名     | 内容解释                     |
| ---------- | ---------------------------- |
| Matrix.hpp | 矩阵类及其函数头、友元函数头 |
| Matrix.cpp | 矩阵类函数定义、友元函数定义 |
| Test0.cpp  | 测试文件 - 基本要求的实现    |
| Test1.cpp  | 测试文件 - 对错误类型的检查  |
| Test2.cpp  | 测试文件 - 其他特殊功能      |



## 4. 报错系统

程序对以下错误进行检查：

| 错误类型                                       | 相关函数                                                     |
| ---------------------------------------------- | ------------------------------------------------------------ |
| 使用Matrix<_T>中不允许的模板数据类型(编译报错) | 错误类名                                                     |
| 构造指针为0的矩阵                              | 构造函数                                                     |
| 传入矩阵为空矩阵                               | 括号索引、+-*/^运算、sub()、subCopy()、cofactorMatrix()      |
| 传入矩阵为空矩阵                               | det()、inv()、min()、max()、transpose()、rotate90()、getChannelMat() |
| 传入行、列、通道数越界                         | 括号索引、sub()、subCopy()、cofactorMatrix()、getChannelMat() |
| 运算中矩阵行数和列数不匹配                     | +-*/运算                                                     |
| 运算中矩阵不是方阵                             | ^运算、det()、inv()                                          |
| 运算中矩阵不可逆                               | inv()                                                        |

报错格式为打印错误提示、主函数文件位置、报错位置、报错函数，报错文件地址使用`vscode`可识别的字符串，可以通过`Ctrl+左键点击`定位文件及报错位置。例如：

```
Error: The fisrt Matrix is an empty Matrix when using 'operator()'.
	/mnt/d/VScodeProjects/CppClass/Project5/src/Test1.cpp
	/mnt/d/VScodeProjects/CppClass/Project5/src/Matrix.cpp:243 : operator()
```
