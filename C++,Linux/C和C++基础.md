
### C++和C的区别
- 是两门不同的语言
- C++面向对象，C面向过程的结构化编程语言
- C++具有封装继承多态
- C++相比C，增加许多类型安全的功能，比如强制类型转换
- C++支持范式编程、比如模板类、函数模板。
- new/delete 对比 malloc free

### struct 的size of大小<br>
- 结构体首地址与最宽类型对其
- 结构体总大小最宽类型整数倍
- 结构体每个成员相对于结构体首地址的偏移量是成员大小的整数倍

### define 和 inline区别
- define 就是简答的字符串替换，在预处理阶段完成，若是宏定义一个函数，那么它并不对参数做检验，并不安全。
- inline, 在编译阶段完成，由编译器决定时候将该函数嵌入到调用处，会进行参数校验，但是**并没有函数调用过程中的变量压栈，栈帧开辟销毁，和寄存器的保存和恢复。**
    - 通常情况下，内敛会使得可执行文件的空间变大，但是也有可能不会。[内联函数(inline) ，提高效率？](https://blog.csdn.net/baidu_35679960/article/details/80845681)
        - 如果被内联函数自己的函数体代码量比因为 函数调用的*准备与善后*工作引入的代码量大，内联后程序的代码量会变大；相反，当被内联函数的函数体代码量比因为函数调用的准备与善后工作引入的代码量小：[内联函数的优缺点](https://blog.csdn.net/andrew_yau/article/details/7687356)
    - 内敛后，代码的空间局部性提高了
    - 内敛后编译器，可能会对代码做更多的优化，因为调用出的代码会连城一片。
    - 默认构造函数、拷贝构造函数、析构函数、赋值运算符一般会被内敛化

### 重点掌握<br>
- 指针和引用的概念
  - 指针是一个指向其他变量地址的变量
  - 引用：没有空引用，必须在创建时初始化，之后不再修改,引用知识一个别名。
<br>

    int (*p) [n];
      p是指向数组的指针
    int* p [n];
      p 是指针数组的数组名
    int* (*p) [n];
      p是指向指针数组的指针。
- 引用底层
    - 存的是变量的地址，不过对引用变量取地址，是取不到引用变量的地址的，编译器会直接取得被引用的变量的地址
    - 编译器其实是将开发者对引用的操作翻译成了对指针的操作。
    - 从语言层面可以将引用理解为const指针
### 声明和定义


 


### const
- 变量:
    - C语言中，const表示只读的变量，存储在内存中，可以通过指针改变该存储空间中的值。
    - C++语言中，const被看做常量，编译器使用常数直接替换掉被const修饰的标识符的引用，并不会通过访问内存去读取数据，这一点类似C语言中的宏#define。
    - 总结：const在C语言中表示只读的变量，而在C++中对于内置类型表示一个常量，对于非内置类型表示只读的变量。    
    

- 指针
    - 指向const的指针 const int *p
    - const指针 int  *const p
    - 指向const 的const指针 const int *const p
- 引用
    - 指向const的引用 const int &b=2*3;（可以是右值）
    
- const成员函数，说明该成员函数内不能修改成员变量。
    - const成员只能调用const成员函数
    - const成员保证成员变量不被改变但是，不保证指针所指向的内容不被改变
    - const成员函数可以访问不管const还是非const对象的不管const还是非const的成员变量，非const函数只能访问非const对象的非const成员和const成员
    [C++的const类成员函数](https://blog.csdn.net/lihao21/article/details/8634876)<br>
- typedef的问题

### cast转换
- const_cast
    - 用来添加或删除const特性
- static_cast
    - 任何编译器的隐式转换都可以由static_cast显式完成，void*转具体指针，较大的算数类型转化较小的类型，编译器不会出警告。
- dynamic_cast
- reinterpret_cast
    - 为安全使用该转换，需要程序员完全理解所设计的数据类型，以及编译器实现强制的转换细节。
- 为什么不使用C的转换
- C的转换表面看起来功能强大什么都能转换，但是转化不够明确，不能进行错误检查，容易出错。

### 指针和引用
- 指针
    - 一个变量，指向一内存地址
        int a[4]={1,2,3,4};
        int *ptr=(int *)(&a+1):这个操作指的是a下一行，并不是a[1]这个元素.   

- 引用    
    - 一个变量的别名
- 区别
    - sizeof(ptr)=4 sizeof(引用)是引用对象的大小
    - 引用初始化必须是一个已有对象
    - 指针需要解引用才能操作对象
    - 有const指针，没有const引用
    - 指针可以改变指向谁，而引用不能
    - 指针可以有多级，引用只有一级
    - 如果返回动态内存分配的对象或者内存，必须使用指针，引用可能引起内存泄露。 
### 智能指针
[C++智能指针简单剖析](https://www.cnblogs.com/lanxuezaipiao/p/4132096.html)<br>

- auto_ptr
    - 在C++11中被弃用
    - 原因：
- unique_ptr
    - unique_ptr实现独占式拥有或严格拥有概念，保证同一时间内只有一个智能指针可以指向该对象。它对于避免资源泄露(例如“以new创建对象后因为发生异常而忘记调用delete”)特别有用。
        ```C++
          unique_ptr<string> p3 (new string ("auto"));   //#4
          unique_ptr<string> p4；                       //#5
          p4 = p3;//此时会报错！！
        ```

  - 其中#1留下悬挂的unique_ptr(pu1)，这可能导致危害。而#2不会留下悬挂的unique_ptr，因为它调用 unique_ptr 的构造函数，该构造函数创建的临时对象在其所有权让给 pu3 后就会被销毁。这种随情况而已的行为表明，unique_ptr 优于允许两种赋值的auto_ptr 
     ```c++
    unique_ptr<string> pu1(new string ("hello world"));
    unique_ptr<string> pu2;
    pu2 = pu1;                                      // #1 not allowed
    unique_ptr<string> pu3;
    pu3 = unique_ptr<string>(new string ("You"));   // #2 allowed
    ```
- shared_ptr
    - 多个智能指针可以指向相同对象，该对象和其相关资源会在“最后一个引用被销毁”reset时候释放。
    - 除了可以通过new来构造，还可以通过传入auto_ptr,unique_ptr,weak_ptr来构造
    - 对shared_ptr进行初始化时不能将一个普通指针直接赋值给智能指针，因为一个是指针，一个是类。可以通过make_shared函数或者通过构造函数传入普通指针。并可以通过get函数获得普通指针。
    - 使用make_shared来初始化
    - 使用场景
        - 通常使用在共享权不明的场景。有可能多个对象同时管理同一个内存时。
        - 对象的延迟销毁。陈硕在《Linux 多线程服务器端编程》中提到，当一个对象的析构非常耗时，甚至影响到了关键线程的速度。可以使用 BlockingQueue<std::shared_ptr<void>> 将对象转移到另外一个线程中释放，从而解放关键线程。
- weak_ptr
     - 不控制对象生命周期的智能指针
     - weak_ptr 设计的目的是为配合 shared_ptr 而引入的一种智能指针来协助 shared_ptr 工作, 它只可以从一个 shared_ptr 或另一个 weak_ptr 对象构造, 它的构造和析构不会引起引用记数的增加或减少。
     - 为了解决循环引用导致的内存泄漏，引入了weak_ptr弱指针，weak_ptr的构造函数不会修改引用计数的值，从而不会对对象的内存进行管理，其类似一个普通指针，但不指向引用计数的共享内存，但是其可以检测到所管理的对象是否已经被释放，从而避免非法访问。
     - weak_ptr是用来解决shared_ptr相互引用时的死锁问题,如果说两个shared_ptr相互引用,那么这两个指针的引用计数永远不可能下降为0,资源永远不会释放。
     - 不能通过weak_prt直接访问对象，要想使用应该将他转化为shared_ptr： shared_ptr=pa->pb_.lock();p->print()
     
- 智能指针细节
    - 引用变量保存在哪里
    - 引用计数是否线程安全


 ### 数组和指针区别
 | | 指针|数组|
 | --- | --- | --- |
 | 内容| 保存数据地址|保存数据|
 | 访问方法 |间接访问数据，首先获得指针的内容，然后将其作为地址，从该地址中提取数据|直接访问数据|
 | 数据形式|通常用于动态的数据结构|通常用于固定数目且数据类型相同的元素| 
 |创建和删除 |通过Malloc分配内存，free释放内存|隐式的分配和删除|
 | 指向|通常指向匿名数据，操作匿名函数|自身即为数据名|

 
### 链接指示 extern "C"{}
- 总结
    - 都是在C++的地方套上 #ifdef extern "C"
    - C++ 调用C库函数的时候,给C++调用处套上，这样才能找到C库的函数
    - C 调用 C++时。给C++套上，才能按照C的规则编译函数，C才能找到那个函数

&emsp;&emsp;用于CPP与C文件混用的时候，推荐使用条件编译
```c++
// demo.h文件
#program once

#ifdef __cplusplus
extern "C"{
#endif



int add(int a,int b);
#ifdef __cplusplus
}
#endif

```


```c++
// demo.c or demoa.cpp文件
#include"demo.h"
int add(int a,int b){
    return a+b;
}
```


```c++
//main.c or main.cpp
#ifdef __cplusplus 
#include<iostream>
using namepsace std;
#elseif
#include<stdlib.h>
#endif
#include"demo.h"

int main(){ 
    int a=add(3,4);
}


```
    
### 面向对象基础 
 
 
#### 封装

#### 继承
- 所有的私有成员都穿不下去
- 公有继承：保持原属性继承
- 私有继承：能传下去的都在子类当中变成私有属性
- 保护继承：都变保护属性
#### 多态
 
 
#### 虚函数
[C++虚函数的作用是什么——知乎](https://www.zhihu.com/question/23971699)
[C++中的虚函数(表)实现机制以及用C语言对其进行的模拟实现](https://blog.twofei.com/496/)

#### 虚函数总结
- 总结
    - 一个对象的内存最上方是虚函数指针
    - 一个带虚函数的类有一个虚函数表
    - 派生类继承基类的虚函数表，若重写虚函数那么虚函数表对应表项会重写
- 1、每一个类都有虚表。
- 2、虚表可以继承，如果子类没有重写虚函数，那么子类虚表中仍然会有该函数的地址，只不过这个地址指向的是基类的虚函数实现。如果基类3个虚函数，那么基类的虚表中就有三项(虚函数地址)，派生类也会有虚表，至少有三项，如果重写了相应的虚函数，那么虚表中的地址就会改变，指向自身的虚函数实现。如果派生类有自己的虚函数，那么虚表中就会添加该项。
- 3、派生类的虚表中虚函数地址的排列顺序和基类的虚表中虚函数地址排列顺序相同。


- 定义他为虚函数是为了允许用基类的指针来调用子类的这个函数。

- 纯虚函数
    - 让子类只是继承了父类的接口
    - 子类需要自己去定义自己的函数
    - 因为有一些父类中的那些函数存在性是不合理的，需要具体的被继承才有实际意义
    - 带有纯虚函数的类被称为抽象类
        - 抽象类不能定义对象
        - 如果派生类给出了基类纯虚函数的实现，那么派生类就不是抽象类了   

- 析构函数必须是虚函数
    - 将可能会被继承的父类的析构函数设置为虚函数，可以保证当我们new一个子类，然后使用基类指针指向该子类对象，释放基类指针时可以释放掉子类的空间，防止内存泄漏。 
    - C++默认的析构函数不是虚函数是因为虚函数需要额外的虚函数表和虚表指针，占用额外的内存。而对于不会被继承的类来说，其析构函数如果是虚函数，就会浪费内存。因此C++默认的析构函数不是虚函数，而是只有当需要当作父类时，设置为虚函数。 
    
- 虚函数的实现：在有虚函数的类中，类的最开始部分是一个虚函数表的指针，这个指针指向一个虚函数表，表中放了虚函数的地址，实际的虚函数在代码段(.text)中。当子类继承了父类的时候也会继承其虚函数表，当子类重写父类中虚函数时候，会将其继承到的虚函数表中的地址替换为重新写的函数地址。使用了虚函数，会增加访问内存开销，降低效率。

- 为什么构造函数不需要虚函数
    - 从语言的意义上来讲，C++的虚允许我们调用一个函数在只知道它的接口信息的情况下。构造一个对象，你需要全部的信息，所以你需要知道你现在构造的对象是什么类型的。
    - 从实际意义上看，当我们使用一个基类指针指向一个子类对象的时候，子类已经构造出来了，不需要构造上的多态。
    - 从实现上来看，从实现上看，vptr 指针在构造函数调用后才对其初始化，因而构造函数不可能成为虚函数  

#### 多态
- 多态[虚函数的文章](https://www.cnblogs.com/cxq0017/p/6074247.html)
    - 重载多态（静）：函数重载，运算法重载
    - 参数多态（静）：类模板，函数模板
    - 强制多态（动/静）：基本类型转换，自定义类型转换
    - 子类型多态（动）：虚函数
    - 静态多态
        - 静态多态主要是重载，在编译的时候就已经确定[C++函数重载的实现原理](https://blog.csdn.net/D_Guco/article/details/53267800)
        - 编译器对同名但是不同参数的函数在编译是给出不同的汇编实现，这样在调用时，相当于调用不同的函数
    - 动态多态
        - 动态多态是用虚函数机制实现的，在运行期间动态绑定。举个例子：一个父类类型的指针指向一个子类对象时候，使用父类的指针去调用子类中重写了的父类中的虚函数的时候，会调用子类重写过后的函数，在父类中声明为加了virtual关键字的函数，在子类中重写时候不需要加virtual也是虚函数。
        - 虚函数因为用了虚函数表机制，调用的时候会增加一次内存开销
        - 每一个含有虚函数的类都有虚表
            - 虚表是一个指向函数地址的一位数组
        - 子类若重写父类虚函数，虚函数表中，该函数的地址会被替换，对于存在虚函数的类的对象，在VS中，对象的对象模型的头部存放指向虚函数表的指针，通过该机制实现多态。 
    - 实现
        - 函数重载，重载在他的参数类型上
        - 运算法重载，非成员函数一般作为友元,算数操作符，相等，关系，位操作符都适合作为非成员函数进行重载，其它的都适合作为类成员进行重载
        - 类模板函数模板
        - 虚函数
        - 类型转换，自定义类型转换

- 常见多态问题
    - 菱形继承
    - 虚表结构 参考[C/C++杂记：深入虚表结构](https://www.cnblogs.com/malecrab/p/5573368.html)
        - offset to top”是指到对象起始地址的偏移值，只有多重继承的情形才有可能不为0，单继承或无继承的情形都为0。
        - RTTI information”是一个对象指针，它用于唯一地标识该类型。（注：本系列博文后续会有详细讨论。）
        - 虚函数表，存放着虚函数指针列表
        - 多继承时，会有主虚表和次虚表
            - <img src="https://images2015.cnblogs.com/blog/898333/201606/898333-20160610105059136-1190031454.png" width="70%"> 

### 泛型

- 什么是泛型
    - STL是泛型编程思想的集中体现
    - 函数模板和类模板
    - STL 是C++标准库的一部分
- 泛型作用
    - 代码重用，泛型定义一次，就可以对不同类型实例化
    - 属于静态多态，效率高，
    - 目标文件会很大，
    
- 重载和泛型的关系

- STL六大部件
    - 容器
        - 序列容器：array,vector,deque,list,forward_list
            - deque:存储元素的地址一直不变，没有copy这步骤
        - 关联式容器:
        
    - 算法
    - 迭代器
    - 仿函数
    - 适配器
    - 空间配置器

### RTTI 运行时类型识别
- dynamic_cast
- typeid
- type_info
  
### 内存释放回收

- ptmalloc<br>
[malloc和free的实现原理解析](https://jacktang816.github.io/post/mallocandfree/)<br>
[Understanding glibc malloc](https://sploitfun.wordpress.com/2015/02/10/understanding-glibc-malloc/)<br>
[理解 glibc malloc](https://wizardforcel.gitbooks.io/sploitfun-linux-x86-exp-tut/content/understanding-glibc-malloc.html)<br>
[glibc ptmalloc 内存管理详解_csdn_还算令人满意的解释](https://blog.csdn.net/lclfans1983/article/details/106578895)<br>
[华庭的glibc ptmalloc源码分析]()
- 设计假设
    - 大的生命周期长的
    - 特别大的
    - 短声明周期的
    - 只缓存临时使用的小的内存块，大的内存释放直接还给操作系统
    - 收缩堆的条件是当前 free 的块大小加上前后能合并 chunk 的大小大于 64KB、，并且
    堆顶的大小达到阈值，才有可能收缩堆，把堆最顶端的空闲内存返回给操作系统。
    - 需要保持长期存储的程序不适合用 ptmalloc 来管理内存。
    - 为了支持多线程，多个线程可以从同一个分配区（arena）中分配内存，ptmalloc
      假设线程 A 释放掉一块内存后，线程 B 会申请类似大小的内存，但是 A 释放的内
      存跟 B 需要的内存不一定完全相等，可能有一个小的误差，就需要不停地对内存块
      作切割和合并，这个过程中可能产生内存碎片。
      
- 主分配去和非主分配区
- chunk
- 空闲chunk容器
    - fastbin
    - smallbin
    - largebin
    - topchunk
- 分配算法流程：
    - 小于等于64字节的 
    - 小于128K的
        - index=floor(size/8),看看smallbins[index]是否有空闲chunk，小于512字节的直接返回，大于的找第一个大小合适的
        - 没有的话
            - 遍历unsorted_list，如果找到合适的返回
            - 没找到将unsorted_list中的chunk都归类到各自的smallbins当中
            - index++ 从更大的链表当中开始找，知道找到合适的为止，将剩余部分归到unsorted_list当中
            - 上面还不行的话，就会用到top_chunk
                - 主分配区:
                    - 主分配区可以访问进程的 heap 区域和 mmap 映射区域，也就是说主分配区可以使用 sbrk 和 mmap 向操作系统申请虚拟内存。
                - 非主分配区
                    - 而非主分配区只能访问进程的 mmap 映射区域，非主分配区每次使用 mmap () 向操作系统“批发” HEAP_MAX_SIZE （ 32 位系统上默认为 1MB ， 64 位系统默认为 64MB ）大小的虚拟内存，当用户向非主分配区请求分配内存时再切割成小块“零售”出去 .
                    
            - 还不行，就用到mmap，得到mmaped chunk，释放时解除映射直接返回给操作系统
    - 大于128K的
        - 没开启mmap分配阈值的动态调整机制：直接调用mmap
        - 大于等于mmap分配阈值的才直接mmap
    - fastbins
    - mmaped chunk
    - Last remainder chunk
    - 分配流程总结：根据用户请求分配的内存的大小，ptmalloc 有可能会在两个地方为用户
             分配内存空间。在第一次分配内存时，一般情况下只存在一个主分配区，但也有可能从
             父进程那里继承来了多个非主分配区，在这里主要讨论主分配区的情况，brk 值等于
             start_brk，所以实际上 heap 大小为 0，top chunk 大小也是 0。这时，如果不增加 heap
             大小，就不能满足任何分配要求。所以，若用户的请求的内存大小小于 mmap 分配阈值，
             则 ptmalloc 会初始 heap。然后在 heap 中分配空间给用户，以后的分配就基于这个 heap
             进行。若第一次用户的请求就大于 mmap 分配阈值，则 ptmalloc 直接使用 mmap()分配
             一块内存给用户，而 heap 也就没有被初始化，直到用户第一次请求小于 mmap 分配阈 值的内存分配。第一次以后的分配就比较复杂了，简单说来，ptmalloc 首先会查找 fast bins，
             如果不能找到匹配的 chunk，则查找 small bins。若还是不行，合并 fast bins，把 chunk
             加入 unsorted bin，在 unsorted bin 中查找，若还是不行，把 unsorted bin 中的 chunk 全
             加入 large bins 中，并查找 large bins。在 fast bins 和 small bins 中的查找都需要精确匹配，
             而在 large bins 中查找时，则遵循“smallest-first，best-fit”的原则，不需要精确匹配。
             若以上方法都失败了，则 ptmalloc 会考虑使用 top chunk。若 top chunk 也不能满足分配
             要求。而且所需 chunk 大小大于 mmap 分配阈值，则使用 mmap 进行分配。否则增加
             heap，增大 top chunk。以满足分配要求。
- free
- new
- delete

- 首先，new/delete是C++的关键字，而malloc/free是C语言的库函数，后者使用必须指明申请内存空间的大小，对于类类型的对象，后者不会调用构造函数和析构函数
- malloc与new区别 
    - malloc需要给定申请内存的大小，返回的指针需要强转。
    - new会调用构造函数，不用指定内存大小，返回的指针不用强转。
- jemalloc
- tcmalloc
- stl allocator
- 内存泄露
    - 一般都是分配了一对象或者一组对象但是没有正确调用delete
        - 忘记delete 
        - 在delete 之前程序崩溃
        - delete的内容 是错误的
            - 在子函数当中对一个指针进行malloc,这个函数没有使用 f(int *&p)这种结构 
            - 对于数组对象没有delete[]
            - 对于void*指针指向的对象调用delete，使得没有调用对象的析构函数
            - 析构函数没有使用虚函数，使用基类指针调用了子对象的析构函数
            
    - 堆内存泄露
    - 系统内存泄露
    
    
### C语言中的volatile [volatile](https://en.wikipedia.org/wiki/Volatile_(computer_programming))
&emsp;A volatile specifier is a hint to a compiler that an object may change its value in ways not specified by the language so that aggressive optimizations must be avoided.<br>
- 背景: 应用于仿真编译器和CPU过度优化，导致无法读到内存处的值得一种标识符，
需要读到内存处的值得例子就比如
    - allow access to memory mapped devices
    - allow uses of variables between setjmp and longjmp
    - allow uses of sig_atomic_t variables in signal handlers.
但是他不能阻止CPU改变指令执行顺序，
  - 一个能反映该问题的经典例子是一个单例模式实现
    - ![](.C和C++基础_images/ea9a8902.png)
        - barrier可以阻止之前的指令交换到之后
  
- volatile 关键字是一种类型修饰符，用它声明的类型变量表示可以被某些编译器未知的因素更改，比如：操作系统、硬件或者其它线程等。遇到这个关键字声明的变量，编译器对访问该变量的代码就不再进行优化，从而可以提供对特殊地址的稳定访问。声明时语法：int volatile vInt; 当要求使用 volatile 声明的变量的值的时候，系统总是重新从它所在的内存读取数据，即使它前面的指令刚刚从该处读取过数据。而且读取的数据立刻被保存
参考：[C/C++ 中 volatile 关键字详解](https://www.runoob.com/w3cnote/c-volatile-keyword.html)
- volatile对象只能调用volatile成员函数类似于const修饰符
- 实现原理 [C/C++ Volatile关键词深度剖析](https://stephan14.github.io/2020/04/14/in-depth-analysis-of-volatile-keywords/)
    - ~~多核CPU其中一个核修改cache中的数据，还要改写内存中的数据，这样别的核的cache就会失效，进而他们读到的就是内存中的数据~~
    - 防止编译器对变量的优化，避免绕开内存操作数据
    - 还可以阻止编译器对volatile变量间操作的指令顺序交换，但是CPU怎样执行控制不了

### 内存屏障
- 背景:是一类同步屏障指令，它使得 CPU 或编译器在对内存进行操作的时候,
  严格按照一定的顺序来执行, 也就是说在memory barrier 之前的指令
  和memory barrier之后的指令不会由于系统优化等原因而导致乱序
- 实现:
    - 常见的x86/x64，通常使用lock指令前缀加上一个空操作来实现
      当然不能真的是nop指令，但是可以用来实现空操作的指令其实是很多的
    - ```asm
      addl $0, 0 (%esp)
     ```
### 什么时候产生coredump
参考：APUE<br>
产生coredump条件：一般系统处理信号的默认动作终止+core<br>

- SIGABRT：异常终止
- SIGBUS：硬件故障
- SIGEMT：硬件故障
- SIGFPE：算术异常
- SIGINFO：键盘状态请求
- SIGJVM1：Java虚拟机内部使用
- SIGQUIT：终端退出符
- SIGSEGV：无效内存引用
- SIGSTKFLT：协处理器栈故障？
- SIGSYS：无效系统调用
- SIGTRAP：硬件故障
- SIGXCPU： 超过CPU限制
- SIGXFZ:超过文件长度限制

- 1.内存访问越界
- 2.多线程使用线程不安全函数
- 3.非法指针
    - 1.空指针
    - 2.野指针
- 4.栈溢出