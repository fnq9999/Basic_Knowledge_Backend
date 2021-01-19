LRU使用场景
=========
### 内核中的LRU
参考：[Linux 2.6 中的页面回收与反向映射](https://www.ibm.com/developerworks/cn/linux/l-cn-pagerecycle/index.html)
- 页高速缓存的缓存回收算法(磁盘缓存)
    - 双链LRU
        - active 链表和 inactive 链表
    - 一个ZONE 一对这样的链表
    - 每个页面用两个标记标识 PG_active,PG_active
    - 操作如下:
        - mark_page_accessed()：当一个页面被访问时，则调用该函数相应地修改 PG_active 和 PG_referenced。
        - page_referenced()：当操作系统进行页面回收时，每扫描到一个页面，就会调用该函数设置页面的 PG_referenced 位。如果一个页面的 PG_referenced 位被置位，但是在一定时间内该页面没有被再次访问，那么该页面的 PG_referenced 位会被清除。
        - activate_page()：该函数将页面放到 active 链表上去。
        - shrink_active_list()：该函数将页面移动到 inactive 链表上去。
- 在系统内，一般每个zone会设置一条线，当空闲页框数量不满足这条线时，就会执行内存回收操作，而系统空闲页框数量满足这条线时，系统是不会进行内存回收操作的。
- 内存回收主要是针对匿名页和文件页进行的。
- <img src="https://www.ibm.com/developerworks/cn/linux/l-cn-pagerecycle/image001.jpg" width="50%">
- 更详细请看[linux内存源码分析 - 内存回收(整体流程)](https://www.cnblogs.com/tolimit/p/5435068.html)

### 处理器的LRU
- PLRU:[Cache replacement policies（缓存替换策略）/ LRU 和 LFU等算法](https://blog.csdn.net/weixin_40539125/article/details/104739835)[cache替换策略-PLRU【转](http://blog.sina.com.cn/s/blog_65a6c8eb0101ez8w.html)
    -  Tree-PLRU
    - <img src="https://img-blog.csdnimg.cn/20200308210810715.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MDUzOTEyNQ==,size_16,color_FFFFFF,t_70" width="50%">
    - <img src="https://img-blog.csdnimg.cn/20200308205508853.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MDUzOTEyNQ==,size_16,color_FFFFFF,t_70" width="50%">
    -  Bit-PLRU
        - 为每一个Cache Block设置一个MRU Bit
        - 存储器访问命中时，该位将设置为1，表示当前Cache Block最近进行过访问。当因为Cache Miss而进行Replacement时，将寻找为0的MRU Bit，在将其替换的同时，设置其MRU Bit为1。
        - 当将最后一个MRU bit置1时，需要将别的1都置0
    - - 缺点是，相比较于LRU命中率稍差，但是带来的好处是，更小的空间开销，稍稍更好的等待时间，比LRU消耗更少的功率以及更低的开销。
    - 处理器中 LRU 导致信息泄露 [Leaking Information Through Cache LRU States](https://arxiv.org/pdf/1905.08348.pdf)
        - 幽灵攻击  
### Redis 和 memcache
- [LRU和LFU算法以及其在Redis中的实现](https://my.oschina.net/lscherish/blog/4467394)
- 这里的LRU使用了采样的思想，并不是取全局的最近最少使用，而是采样中的。  
    - 随机采样+采样池，每次更新采样池，从池子里的idle time最大的进行淘汰（idle time 就是上次使用距离现在的时间    ）

