# 源文件和目标文件的模式替换
src=$(wildcard *.c)
obj=$(patsubst %.c,%.o,$(src))

target=out

# 定义编译器和编译选项
CC=gcc
CFLAGS=-g -Wall -Wextra # 添加更多的警告信息

# 默认目标
ALL: $(target)

$(target): $(obj)
	$(CC) $^ -o $@

# 编译 .c 文件到 .o 文件的规则
$(obj): %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理生成的文件
clean:
	-rm -rf $(obj) $(target)

.PHONY: clean ALL
