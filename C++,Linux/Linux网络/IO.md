IO
===========
### 阻塞IO /BIO
图片参考:[谈谈面试中常问的I/O模型](https://juejin.cn/post/6844904199868645383)
<br>

<img src="https://user-gold-cdn.xitu.io/2020/6/26/172ef17fc508d691?imageView2/0/w/1280/h/960/ignore-error/1" width="50%">

- 过程
    - 使用阻塞IO的系统调用，如果如法立即完成就会被OS挂起
    - 当kernel一直等到数据准备好了，它就会将数据从kernel中拷贝到用户内存，然后kernel返回结果，用户进程才解除block的状态，重新运行起来。
- 优点
    - 编程简单
    - 进程或线程在挂起的过程当中不消耗CPU
- 缺点
    - 这种模型基本上一个连接一个线程，系统内存开销很大，并且上下文切换开销很大
    - 并返回结果给用户线程，
    - 采用BIO做服务器，需要每个连接一个线程，很多的线程就会增加更多的上下文切换，这样很难达到**C10K**（concurrent 10K客户端），需要 NIO 
### 非阻塞IO/NIO
<img src="https://user-gold-cdn.xitu.io/2020/6/26/172ef222879861c5?imageView2/0/w/1280/h/960/ignore-error/1" width="50%">

- 过程
    - 使用非阻塞IO的系统调用，不会阻塞而是立刻受到一个结果
        - 回结果是一个error时，它就知道数据还没有准备好，可以再次尝试
        - 一旦数据准备好了，并且又再次收到了用户线程的请求，那么它马上就将数据拷贝到了用户内存，然后返回。
- 需求： 这样如果每次失败都重新尝试一下的话，那么就很耗费CPU，
    - 需要IO多路复用技术
    - 或者 SIGIO信号
        - TCP当中 使用SIGURG信号来通知是否有带外数据。使用SIGURG信号之前，必须设置connfd的进程组或者宿主进程
            - fcntl(conngf,F_SETDOWN,getpid())     
- 优点
    - 只是因为在高并发访问时，非阻塞IO能够一定程度上减少服务器瞬间的并发线程数，从而提高CPU执行效率
    - 本质是降低并发数量，提高了CPU效率

### 同步IO和 异步IO
<img src="https://user-gold-cdn.xitu.io/2020/6/26/172f11bf98cb22ae?imageView2/0/w/1280/h/960/ignore-error/1" width="50%">

- 区别
    - 异步是由内核来完成数据从内核区到用户区的转移
    - 同步不是由内核来完成
- 异步IO
    - Linux 2.6之后开始支持异步IO










