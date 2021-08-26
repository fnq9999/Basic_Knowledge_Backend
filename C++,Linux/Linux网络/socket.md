socket
====

### listenfd
- 最好使用LT，因为ET会使得在高并发的情况下有的客户端连接不上，非要ET那么一定whlie ET
### connfd
- LT模式下
    - 阻塞和非阻塞效果一样，建议非阻塞
- ET模式下
    - 必须使用非阻塞IO，并且一次性读写完整数据
  
### C 实现的socket通信全过程



### 连接队列和半连接队列
- ![](.socket_images/fc23805c.png)
  - 参考[TCP 半连接队列和全连接队列满了会发生什么？又该如何应对？](https://www.cnblogs.com/xiaolincoding/p/12995358.html)
  - 不管是连接队列还是半连接队列，都有最大长度限制，超过限制时，
    内核会直接丢弃，或返回 RST 包。










