
### STL基本组件
- 六大组件
    - 容器：容纳一组元素的对象。
    - 迭代器
    - 算法：包括查找算法、排序算法等等。
    - 函数对象：一种类似于函数指针的可回调机制，用于算法中的决策处理。涉及：策略模式，模板方法。
    - 适配器：用来修饰容器等，STL中的stack，queue通过双端队列deque适配实现，map，set通过RB-Tree适配实现。涉及适配器模式。
    - 空间配置器：负责空间配置和管理。
- 空间配置器
    - new 运算
        - (1)调用::operator new配置内存
        - (2)调用对象构造函数构造对象内容
    - delete 运算
        - (1)调用对象希构函数
        - (2)调用::operator delete释放内存 
    - 为了精密分工，STL allocator将两个阶段操作区分开来：内存配置有alloc::allocate()负责，内存释放由alloc::deallocate()负责；对象构造由::construct()负责，对象析构由::destroy()负责。 
    - 两级配置器
        - 一级配置器（分配空间大于128B）
            - malloc()、realloc()、free()函数进行内存空间的分配和释放
        - 二级配置器（分配空间小于128B）
            - 采用了内存池技术，通过空闲链表来管理内存。
 
 
### 迭代器

### 序列容器
- vector
    - 底层：数组
- array

- deque
- list
    - 底层：双向链表
- forward_list
 
 
 ### 关联容器
 - 红黑树底层的
    - map and multimap
    - set and mutiset
- hashtable
    - bucket
        - resize
            - 若resize的大小大于当前大小就rehash
                - 新建vector<Node*,A>tmp(new_size(),(Node*)0);
                - 对于原来buckets中的所有i,将原来bucket[i]中的链表的每一项重新计算hash值new_bucket_n分别放到各自的tmp[new_bucket_n]中
                    - 那条链表上的元素会分家就是了
                - 最终buckets.swap(tmp)
            - __stl_next_prime:二分查找下一个不小于x的质数    
                - 首先来说假如关键字是随机分布的，那么无所谓一定要模质数。但在实际中往往关键字有某种规律，例如大量的等差数列，那么公差和模数不互质的时候发生碰撞的概率会变大，而用质数就可以很大程度上回避这个问题。
        - insert_unique
            - 先resize
            - insert_unique_noresize
                - 遇到重复的key就返回false
        - insert_equal
            - resize
            - insert_equal_noresize
                - 遇到重复的紧跟着那个元素在下面插入
        - bkt_num，算出key的落脚点
        - copy_from
        - clear
    - unordered_map and unordered_set
        - 占用内存比map高
 
### 红黑树
#### 介绍
&emsp;&emsp;红黑树是二叉查找树，每个节点要么红要么黑。它确保没有一条路径会比其他路径长两倍。红黑树是一种弱平衡树，相对于要求严格的AVL树，旋转次数少。
- 性质
    - 每个节点要么红要么黑
    - 根节点是黑色
    - 每个叶节点是黑色的
    - 一个节点是红色的，那么儿子节点都是黑色的
    - 每个节点到其任意子孙节点的路径上黑色节点的数目一样
#### 为什么有了AVL还要有红黑树
- AVL性质是平衡树要求每个节点的左子树和右子树的高度差至多等于1
- AVL在频繁插入删除的情况下都要不断左旋右旋的调整来维护平衡性
- 红黑树可以保证在最坏情况下，log(n)查找到某个节点
- 单单对于查找来说，还是AVL快





 