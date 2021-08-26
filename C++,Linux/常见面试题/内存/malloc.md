ptmalloc
====================
参考：华庭 Ptmalloc2 源代码分析<br>

### 流程
- 将用户需要的空间转化为相应的chunksize
- 小于maxfast(默认 64B)从fastbin当中分配，否则跳到下一步
- 大于从smallbins（默认最大512B）当中遍历，没有的话
    - 遍历fastbin,将fastbin当中能合并的合并，都放到unsorted bin当中
    - 遍历unsorted bin,
        - if 1chunk and 这个chunk上次分配使用过？ and chunk>=need 
            - 对该chunk分割来进行分配，多余的放入small or large bins当中
- 上面都不行就从large bins当中寻找
    - 按照smallest-first,best-fit原则，找到一个合适的chunk。切下来一部分，剩下的还给bins。
- 到top chunk当中查找
- top chunk也不行，就增大top chunk
    - 在主分配区，就sbrk()增大topchunk
    - 非主分配区，使用mmap分配一个sub-heap，增大top chunk大小
- 大于等于mmap分配阈值，则直接mmap
### heap的收缩
- free之后，当高地址空闲空间超过一定界限之后，heap会收缩。



    
    
    