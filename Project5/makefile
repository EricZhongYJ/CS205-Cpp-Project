# This file is a makefile file for building and running.
# Author: 12012613 Zhong Yuanji钟元吉
# Encode: UTF-8
# Version: GNU Make 4.3
# Date: 2022/12/18

# 在终端输入make即可编译并运行文件
CXX = g++
CFLAGES = -c -w

SRC_DIR = ./src
# 包含inc所有文件
INC = -I./inc
SRC = $(SRC_DIR)/Test0.cpp
OBJS = $(patsubst %.cpp, %.o, $(SRC))
# 生成文件名
TARGET = CppTask

# Linux:======
$(TARGET) : $(OBJS)
	$(CXX) -o $@ $(OBJS)
	./$(TARGET)
	rm -f $(SRC_DIR)/*.o
%.o : %.c # 编译
	$(CXX) $(CFLAGES) $< -o $@ $(INC)

.PHONY : clean
clean : # 删除.o文件和可执行文件
	rm -f $(SRC_DIR)/*.o $(TARGET)

# # Windows:======
# $(TARGET) : $(OBJS)
# 	$(CXX) -o $@ $(OBJS)
# 	.\$(TARGET)
# 	del .\src\*.o
# %.o : %.c
# 	$(CXX) $(CFLAGES) $< -o $@ $(INC)

# .PHONY : clean
# clean : # 删除.o文件和可执行文件
# 	del .\$(TARGET).exe .\src\*.o