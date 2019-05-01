.PHONY: run clean

CC = gcc
LIB = -lpthread
# fname = 需编译的文件名

# 存放头文件目录
Code = ../../code

vpath % $(Code) # Make查找依赖文件

# 头文件所在目录
Hfile = -I$(Code)

Csapp = $(Code)/csapp.c

do: test
	@./test

test: $(fname) $(Csapp)
	$(CC) $(Hfile) -o test $(fname) $(Csapp) $(LIB)

clean: test
	@rm test
