

### listenfd
- 最好使用LT，因为ET会使得在高并发的情况下有的客户端连接不上，非要ET那么一定whlie ET
### connfd
- LT模式下
    - 阻塞和非阻塞效果一样，建议非阻塞
- ET模式下
    - 必须使用非阻塞IO，并且一次性读写完整数据