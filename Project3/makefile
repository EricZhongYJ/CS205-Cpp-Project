# This file is a makefile file for building and running.
# Author: 12012613 Zhong Yuanji钟元吉
# Encode: UTF-8
# Version: GNU Make 4.3
# Date: 2022/10/23

# 在终端输入make即可编译并运行文件
CXX = gcc # 使用gcc编译C文件
CFLAGES = -c -Wall # Wall显示警告

SRC_DIR = ./src
INC = -I./inc # 寻找inc所有文件
SRC = $(wildcard $(SRC_DIR)/*.c) # 寻找文件
OBJS = $(patsubst  %.c,  %.o, $(SRC)) # 代替代码
TARGET = CTask # 生成文件名

$(TARGET) : $(OBJS)
	$(CXX) -o $@ $(OBJS) # 编译
	./$(TARGET) # 运行
	rm -f $(SRC_DIR)/*.o # 删除.o文件
%.o : %.c # 编译
	$(CXX) $(CFLAGES) $< -o $@ $(INC)

# 防止make将虚假目标与文件名混淆
.PHONY : clean
clean : # 删除.o文件和可执行文件
	rm -f $(SRC_DIR)/*.o $(TARGET)