零拷贝
=======
[零拷贝技术](https://www.cnblogs.com/xiaolincoding/p/13719610.html)

- 是什么:就是不需要CPU的数据传输方式，需要网卡支持SG-DMA
    - ![](.IO优化_images/bf79cebd.png)
    - Linux 2.4之后的 sendfile函数
  
- 背景 


