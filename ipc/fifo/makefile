# 获取所有.c源文件并生成对应的目标可执行文件名
src=$(wildcard *.c)
targets=$(patsubst %.c,%,$(src))

# 定义编译器和编译选项
CC=gcc
CFLAGS=-g -Wall -Wextra # 添加更多的警告信息

# 默认目标，构建所有可执行文件
all: $(targets)

# 模式规则，用于从.c文件构建可执行文件
%: %.c
	$(CC) $(CFLAGS) $< -o $@

# 清理生成的文件
clean:
	-rm -f $(targets)

.PHONY: all clean