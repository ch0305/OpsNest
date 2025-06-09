# 定义编译器
CC = gcc

# 定义编译选项
CFLAGS = -Wall -g 

# 定义目标文件名字
TARGET = run

# 定义源文件和目标文件
SRCS = main.c
OBJS = $(SRCS:.c=.o)

# 默认目标
all: $(TARGET)

# 构建目标文件
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lmysqlclient

# 构建对象文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理生成的文件
clear:
	rm -f $(OBJS) $(TARGET)
