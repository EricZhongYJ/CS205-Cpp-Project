#pragma once
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
// using std::cout;
// using std::endl;
// using std::string;
// using std::vector;

//返回指定目录下的文件(夹)信息
#ifndef __linux__ // Windows
#include <io.h>
void ReadDir(string &path, vector<string> &names, vector<bool> &isDir, vector<int> &sizes)
{
    // 用来存储文件信息的结构体
    struct _finddata_t fInfo;
    // 第一次查找，与检查是否无文件
    intptr_t fId = _findfirst((path + "/*").c_str(), &fInfo);
    if (fId == -1)
        return;
    do // 后续查找
    {
        if (strcmp(fInfo.name, ".") && strcmp(fInfo.name, ".."))
        {
            names.push_back(fInfo.name);               // 保存文件名
            isDir.push_back(fInfo.attrib & _A_SUBDIR); // 是否为文件夹
            sizes.push_back(int(fInfo.size));          // 保存大小
            // times.push_back(fInfo.time_write);        // 保存时间 time_t
        }
    } while (_findnext(fId, &fInfo) == 0);
    // 结束查找
    _findclose(fId);
}

#else // Linux
#include <dirent.h>
#include <sys/stat.h>
void ReadDir(string &path, vector<string> &names, vector<bool> &isDir, vector<int> &sizes)
{
    DIR *pDir;           // 目录指针
    struct dirent *fPtr; // 文件指针
    // 检查无法打开文件夹
    if (!(pDir = opendir(path.c_str())))
        return;
    while ((fPtr = readdir(pDir)) != 0)
        if (strcmp(fPtr->d_name, ".") && strcmp(fPtr->d_name, ".."))
        {
            names.push_back(fPtr->d_name);      // 保存文件名
            isDir.push_back(fPtr->d_type == 4); // 是否为文件夹
            struct stat fInfo;
            stat((path + "/" + fPtr->d_name).c_str(), &fInfo);
            sizes.push_back(int(fInfo.st_size)); // 保存大小
            // times.push_back(fInfo.st_mtim);     // 保存时间 timespec
        }
    closedir(pDir);
}
#endif

// int main(int argc, char *argv[])
// {
//     string file_path = "/mnt/d/VScodeProjects/CppClass";
//     vector<string> names;
//     vector<bool> isDir;
//     vector<int> sizes;

//     ReadDir(file_path, names, isDir, sizes);
//     for (int i = 0; i < int(names.size()); ++i)
//     {
//         cout << names[i] << endl;
//         cout << isDir[i] << endl;
//         cout << sizes[i] << endl;
//     }
//     return 0;
// }
