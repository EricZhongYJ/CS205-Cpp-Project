# CS205 C/C++ Programming - Project 2

**Name:** 钟元吉(Zhong Yuanji)

**SID:** 12012613

[TOC]

## Part 1 - Analysis

> This project to implement a much better calculator than that in the last project, which can support addition, substaction, prodction, division and other math function 





## Part 2 - Code

由于代码较长，这里仅放置输入字符串的分析部分，其他函数简介请参考源文件[`Main.cpp`](./src/Main.cpp)或函数头文件[`FunHead.hpp`](./inc/FunHead.hpp)，结构体简介请参考函数头文件[`StructHead.hpp`](./inc/StructHead.hpp)

```c++
// Analyse function for input string
void analyse(char *str)
{
    // Variables about input string
    int len = strlen(str), Id, lastId = 0;
    int dot = -1, e = -1;
    bool isNum = false, numEnd = false;
    // Variables about calculate stack
    numPt = -1, opPt = -1;
    numSet = new Number[len];
    opSet = new char[len];
    priorSet = new char[len];
    // Analyse every char of input
    for (Id = 0; Id < len && !error[0]; ++Id)
    {
        char now = str[Id];
        // It is not a number char
        if (now < '0' || now > '9')
        {
            bool cmp = false;
            // Compare to variables name
            for (int j = 0; j <= varId; ++j)
                if (strncasecmp(&(str[Id]), varName[j], strlen(varName[j])) == 0)
                {
                    addNumBVar;
                    numSet[++numPt] = varVal[j].copy();
                    Id += strlen(varName[j]) - 1;
                    goto NEXT_CHAR;
                }
            // Compare to functions name
            for (int j = 0; j < 12; ++j)
                if (strncasecmp(&(str[Id]), FUN_STR[j], strlen(FUN_STR[j])) == 0)
                {
                    addNumBVar;
                    isNum = false;
                    addOp(j, 5);
                    Id += strlen(FUN_STR[j]) - 1;
                    goto NEXT_CHAR;
                }
            // Compare to operators name
            for (int j = 0; j < 8 && !cmp; ++j)
                if (now == OP_SG[j])
                {
                    // '(' is special
                    if (now == '(')
                    {
                        addNumBVar;
                        isNum = false;
                    }
                    else
                    {
                        addNumBOp;
                        if (now == ')')
                            isNum = true, numEnd = true, str[Id] = ')';
                    }
                    addOp(now, OP_PRIOR[j]);
                    goto NEXT_CHAR;
                }
            // Compare to pi
            if ((now == 'p' || now == 'P') && (str[Id + 1] == 'i' || str[Id + 1] == 'I'))
            {
                addNumBVar;
                ++Id;
                numSet[++numPt] = constPi;
                goto NEXT_CHAR;
            }
            // Compare to 'e' / 'E'
            if (now == 'e' || now == 'E')
            {
                if (Id == 0 || str[Id - 1] == '\0' || str[Id - 1] == ')' || (str[Id + 1] != '-' && (str[Id + 1] < '0' || str[Id + 1] > '9')))
                {
                    addNumBVar;
                    numSet[++numPt] = constE;
                    str[Id] = '0';
                }
                else if (e >= 0)
                {
                    error[0] = 11, error[1] = Id;
                    return;
                }
                else
                    e = Id - lastId;
                goto NEXT_CHAR;
            } // Compare to '-'
            if (now == '-')
            {
                // As a minus signal
                if (Id != 0 && str[Id - 1] != '\0' && str[Id - 1] != 'e')
                {
                    addNumBOp;
                    addOp('-', 1);
                }
                // As an oppsite signal
                else if (!isNum)
                {
                    isNum = true, numEnd = false, lastId = Id;
                    dot = -1, e = -1;
                }
                goto NEXT_CHAR;
            } // Compare to '.'
            if (now == '.')
            {
                // Check if more than one dots or float exponent
                if (dot >= 0 || e >= 0)
                {
                    error[0] = 9 + (e >= 0), error[1] = Id;
                    return;
                }
                if (!isNum)
                    isNum = true, lastId = Id, e = -1;
                dot = Id - lastId;
                goto NEXT_CHAR;
            }
            // There is invalid char in the input
            error[0] = 4, error[1] = Id;
            return;
        NEXT_CHAR:
            continue;
        }
        // It is a number char
        else
        {
            // Last char is not number
            if (!isNum)
                lastId = Id, dot = -1, e = -1;
            else if (numEnd)
            {
                error[0] = 7, error[1] = Id;
                return;
            }
            isNum = true;
            numEnd = false;
        }
    }
    // Pick up the Number and finish the rest calculate in the end
    if (isNum && !numEnd)
        addstrNum(&(str[lastId]), dot, e);
    while (opPt >= 0 && priorSet[opPt] >= 0 && !error[0])
        calculate();
    // Save answer
    if (numPt == 0)
    {
        varVal[0].del();
        varVal[0] = numSet[numPt--];
    }
    else
        error[0] = 6;
    return;
}
```



## Part 3 - Result & Verification

#### Test case #1: 基本要求的实现

注：程序中统一采用科学计数法进行输出

```
Input: cmake . & make
Input: ./Project2.out
Input: 2+3
Output: 5
```

```
Input: 5+2*3
Output: 1.1e1
```

```
Input: (5+2)*3
Output: 2.1e1
```

```
Input: x=3
Output: 3
Input: y=6
Output: 6
Input: x+2*y
Output: 1.5e1
```

```
Input: sqrt(3.0)
Output: 1.73205080756887729366
```

注：第一个数包含30个9和10个2

```
Input: 999999999999999999999999999999.2222222222 + 1.0
Output: 1.0000000000000000000000000000002222222222e30
```

<img src="C:\Users\钟元吉\AppData\Roaming\Typora\typora-user-images\image-20221016185249147.png" alt="image-20221016185249147" style="zoom: 80%;" />



#### Test case #2: 对错误输入的判断

对于**错误的具体位置**，程序会在告知错误前标明。

##### 格式错误：

```
Input: 
Output: There is no input. Please try again.
```

```
Input: =2+3
Output: The input cannot start with equal sign. Please try again.
```

```
Input: 3a=5-2
Output: The variable name on the left of equal sign is invalid. Please try again.
```

```
Input: 3+4_3
Output: There is invalid char in the input. Please try again.
```

```
Input: (3+4))
Output: The number of '(' and ')' are different. Please try again.
```

```
Input: pi2
Output: The numbers cannot follow a variable. Please try again.
```

```
Input: 2//2
Output: The operator cannot follow a operator. Please try again.
```

```
Input: *5
Output: The input starts with a operator. Please try again.
```

<img src="C:\Users\钟元吉\AppData\Roaming\Typora\typora-user-images\image-20221016191638184.png" alt="image-20221016191638184" style="zoom:80%;" />



#### Test case #3: 对错误输入的判断

##### 数字输入错误：

```
Input: 1..2
Output: There are more than one dots in a number. Please try again.
```

```
Input: 1e3.2
Output: The exponene cannot be a float. Please try again.
```

##### 计算错误：

```
Input: 1/(pi-pi)
Output: The divider cannot be zero. Please try again.
```

先使用`ans = 2`初始化，然后重复进行以下运算：

```
Input: ans = 2 ^ ans
...
Input: ans = 2 ^ ans
Output: There might be inf or nan in the expression. Please try again.
```

![image-20221016193100040](C:\Users\钟元吉\AppData\Roaming\Typora\typora-user-images\image-20221016193100040.png)



#### Test case #4: 程序特色功能

具体实现功能参考[`README.md`](./README.md)

1. 函数中**可以不使用括号**，常数`pi`与`e`有100位小数的精度

    ```
    Input: cos pi
    Output: -1
    ```

    ```
    Input: log e
    Output: 1
    ```

    ```
    Input: floor 2.5
    Output: 2
    ```

    ```
    Input: asin(sin1)
    Output: 1
    ```

2. 数字与(参数、函数)、(参数、函数)与(参数、函数)之间的乘法**可以不写乘号**（但**数字与数字之间的乘号不可省略**）

    ```
    Input: pipi
    Output: 9.86960440108935861883449099987615113531369940724079062641334937622004482241920524300177340371855223130787426358085020916660983542837326159522602261817033881496242667944434304721741925322332314849321041
    ```

    ```
    Input: 1e10e (指1*10^10*e)
    Output: 2.7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274e10
    ```

3. 答案储存

    ```
    Input: ans/10 (与之前的结果有关)
    Output: 2.7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274e9
    ```

![image-20221016194903609](C:\Users\钟元吉\AppData\Roaming\Typora\typora-user-images\image-20221016194903609.png)



#### Test case #6: 快速幂与大数高精度运算

```
Input: 1.01^365
Output: 3.77834343328871588776166047964976054602711354915910020033039338936944429521985938119356394368891387529472302574666529669502629377987451723330150792223386242861468254168061525314439691945569427765172479400629582021756049578068333205496182837603299207844744407482328235228487747766633770985176342589180922492753550477517091097005631516167068563291706799691430311198414361019873036106650322537359629007153203447726710947463422439807472885377480448108054315136562847283771508607255440695157041803096694610715506272162550832009596805587673299977392564252990182309681081837907828344511223413916990267287188096706758684949418018001480436953222549187146770721139550421573105249454013216994798432008271425308713028897301180251050440194336501e1
```

```
Input: floor ans
Output: 3.7e1
```

```
Input: (1/3)^900000
Output: 7.4259548402552191399719913072941387394587499435154491166054648102227326374817733075302197612687770945627026374595747759244...e-429410 (输出中共1500位有效数字)
```

```
Input: (1e10000-1)(1e10000-1)
Output: 9.9999999999...9999998000000...0001e19999 (输出中共19999位有效数字)
```

```
Input: ans-1+2e10000
Output: 1e20000
```

![image-20221016201137641](C:\Users\钟元吉\AppData\Roaming\Typora\typora-user-images\image-20221016201137641.png)

注：中间部分的部分9和0被长截图拼合时吞了



## Part 4 - Difficulties & Solutions

#### 问题1：



## Part 5 - Summary



以上是本次Report的所有内容，感谢您的阅读！