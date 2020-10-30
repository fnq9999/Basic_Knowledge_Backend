

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
            - __stl_next_prime:二分查找下一个不小于x的质数
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
 
            
 