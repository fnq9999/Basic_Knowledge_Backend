MAKEFILE
======
参考[Makefile 编写入门](https://blog.csdn.net/weixin_47221359/article/details/109068030)

[Learn Makefiles_With the tastiest examples](https://makefiletutorial.com/)
- extern
    - 函数的声明默认是extern
    - 变量声明必须使用extern
    
    
一段代码
```cgo
///main.c
#include<stdio.h>
int main()  
{  
    printf("hello world\n");  
    fun1();  
    fun2();  
}  
//a.c  
#include<stdio.h>
void fun1()  
{  
    printf("this is b\n");  
}  
//b.c  
#include<stdio.h>
void fun2()  
{  
    printf("this is fun2\n");  
}
```
上面可以直接使用，生成app 
```cgo
gcc main.c a.c b.c -o app
```
- 上面的命令如果使用g++就是错的，因为g++情况下没有隐式声明刚才那种用gcc只会出现warning，
- 如果在main.c当中添加了声明两个函数的头文件那么gcc不会warning，g++不会报错

## Make
- 如果遇到no separator，在/etc/vimrc当中记得设置set noexpandtab
```shell script

src=$(wildcard *.c)

midsrc=$(patsubst %.c,%.o,$(src))
target=app
cc=gcc

app: $(midsrc)
	$(cc) $(midsrc) -o $(target)
%.o : %.c
	$(cc) -c $< -o $@

.PHONY:clean
clean:
	rm -rf $(midsrc) $(target)

```
- wildcard:扩展通配符，用来搜索文件
- patsubst:替换通配符。按照制定规则进行替换
        
        $<：第一个依赖文件；
        $@：目标；
        $^：所有不重复的依赖文件，以空格分开

- 伪目标

&emsp;这样执行make clean 时，不用去考虑当前文件夹下时候有clean，直接执行clean的命令就行了

        .PHONY: clean  
        clean:  
            rm -rf $(obj) $(target)