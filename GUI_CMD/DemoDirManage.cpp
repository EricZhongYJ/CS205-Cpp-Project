#include "ReadDir.hpp"
#include <fstream>
#ifdef __linux__ // 不支持cd
#include <unistd.h>
#define __CLEAR "clear"
#define __mkdir "mkdir %s/%s"
#define __touch "touch %s/%s"
#define __cat "cat %s/%s"
#define __move "cd %s & mv %s %s"
#define __copy "cd %s & cp -r %s %s"
#define __vim "vim %s/%s"
#define __deldir "rm -r %s/%s"
#define __del "rm %s/%s"
#else // Windows只支持cd
#define __CLEAR "cls"
#define __mkdir "cd %s & mkdir %s"
#define __touch "cd %s & cd .>%s"
#define __cat "cd %s & type %s"
#define __move "cd %s & move %s %s"
#define __copy "cd %s & copy %s %s"
#define __vim "cd %s & notepad %s"
#define __deldir "cd %s & rmdir /s /q %s"
#define __del "cd %s & del %s"
#endif

#define __GetInp(str, var)                  \
    cout << "请输入" << str << ":" << endl; \
    cin.getline(var, 400);                  \
    if (var[0] == 'b' && var[1] == '\0')    \
        goto START;

#define __BySystem(str1, op)               \
    __GetInp(str1, tmp);                   \
    sprintf(inp, op, curStr.c_str(), tmp); \
    system(inp);                           \
    __Back

#define __BySystem2(str1, str2, op)              \
    __GetInp(str1, tmp);                         \
    __GetInp(str2, tmp2);                        \
    sprintf(inp, op, curStr.c_str(), tmp, tmp2); \
    system(inp);                                 \
    __Back

#define __Refresh                                \
    names.clear(), isDir.clear(), sizes.clear(); \
    ReadDir(curStr, names, isDir, sizes);        \
    fileN = int(names.size())

#define __Back                              \
    __Refresh;                              \
    printf("操作成功, 输入'b'返回:\n");     \
    scanf("%s", inp);                       \
    while (inp[0] != 'b' || inp[1] != '\0') \
    {                                       \
        printf("输入'b'返回:\n");           \
        scanf("%s", inp);                   \
    }                                       \
    goto START

using std::cin;
int main(int argc, char const *argv[])
{
    // 参数定义
    char curDir[201], inp[401], oup[401], tmp[401], tmp2[401];
    vector<string> names;
    vector<bool> isDir;
    vector<int> sizes;
    // 获取当前/指定文件夹下内容
    getcwd(curDir, 200);
    if (argc == 2 && argv[1])
        strcpy(curDir, argv[1]);
    for (int i = 0; curDir[i]; ++i)
        if (curDir[i] == '\\')
            curDir[i] = '/';
    string curStr = string(curDir);
    ReadDir(curStr, names, isDir, sizes);
    int fileN = int(names.size());
    // 进入交互
    size_t tempI;
    fstream fs;
    while (1)
    {
    START: // 清屏并输出提示
        system(__CLEAR);
        cout << "当前文件夹为:\n"
             << curStr << endl
             << "当前文件夹下文件/文件夹有" << fileN << "个:\n 文件名\t\t\t\t文件类型\t 文件大小(字节)" << endl;
        for (int i = 0; i < fileN; ++i)
        {
            strcpy(oup, "                               %s%18d\n\0");
            strcpy(oup, names[i].c_str()), oup[strlen(oup)] = ' ';
            printf(oup, isDir[i] ? "\t 文件夹" : "\t 文件  ", sizes[i]);
        }
        cout << "请输入指令(按错指令输入'b'返回, 对操作e:写入文件内容输入第二行后无效):" << endl
             << "\t1:进入文件夹\t\t2:返回上层文件夹" << endl
             << "\t3:转到文件夹\t\t4:运行文件/指令(绝对路径)" << endl
             << "\t5:新建文件夹\t\t6:新建文件" << endl
             << "\t7:重命名文件(夹)\t8:编译运行c++文件并删除可执行文件(多个文件从第二个起请输入绝对路径)" << endl
             << "\tq:退出\t\t\tw:查看文件" << endl
             << "\te:写入文件\t\tr:编辑文件TODO" << endl
             << "\tc:复制文件(夹)\t\tx:移动文件(夹)" << endl
             << "\tt:删除文件夹\t\ty:删除文件" << endl;
        // 输入与判断
        cin.getline(inp, 400);
        if (inp[1] == '\0')
            switch (inp[0])
            {
            case 'q':
                return 0;
            case '1': // 进入文件夹
                __GetInp("文件夹名称", inp);
                curStr.append("/").append(inp);
                __Back;
            case '2': // 返回上层文件夹
                tempI = curStr.find_last_of('/');
                curStr = curStr.substr(0, tempI);
                __Back;
            case '3': // 转到文件夹
                __GetInp("转到的绝对路径", inp);
                curStr.assign(inp);
                __Back;
            case '4': // 运行文件/指令
                __BySystem("文件/指令(cd无效)", "cd %s & %s");
            case '5': // 新建文件夹
                __BySystem("文件夹名称", __mkdir);
            case '6': // 新建文件
                __BySystem("文件名称", __touch);
            case '7': // 重命名文件(夹)=移动
                __BySystem2("文件(夹)名称", "更改后文件(夹)名称", __move);
            case '8': // 编译运行c++文件并删除可执行文件
                __GetInp("cpp文件名称", tmp);
                sprintf(inp, "g++ %s/%s -o %s/__temp.exe", curStr.c_str(), tmp, curStr.c_str());
                system(inp);
                sprintf(inp, "%s/__temp.exe", curStr.c_str());
                system(inp);
                sprintf(inp, __del, curStr.c_str(), "__temp.exe");
                system(inp);
                __Back;
            case 'w': // 查看文件
                __BySystem("文件名称", __cat);
            case 'c': // 复制文件(夹)
                __BySystem2("文件(夹)名称", "复制后文件(夹)名称(绝对路径)", __copy);
            case 'x': // 移动文件(夹)
                __BySystem2("文件(夹)名称", "移动后文件(夹)名称(绝对路径)", __move);
            case 'e': // 写入文件
                __GetInp("文件名称", tmp);
                __GetInp("文件内容(结束行写-1)", tmp2);
                inp[0] = '\0';
                fs = fstream(curStr + "/" + tmp, ios::out | ios::trunc);
                while (tmp2[0] != '-' || tmp2[1] != '1' || tmp2[2] != '\0')
                {
                    fs << tmp2 << endl;
                    cin.getline(tmp2, 400);
                }
                fs.close();
                __Back;
            case 'r': // 编辑文件
                __BySystem("文件名称", __vim);
            case 't': // 删除文件夹
                __BySystem("文件夹名称", __deldir);
            case 'y': // 删除文件
                __BySystem("文件名称", __del);
            }
    }
}
