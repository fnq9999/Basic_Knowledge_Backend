### select<br>

### poll<br>
  - poll()
    - 调整timeout参数
    - do_sys_poll()
      - 创建等待队列和内核空间
      - 数据从用户空间->内核空间
      - do_poll()：返回的是就绪的数量
        - 对每个fd做do_pollfd():return mask
          - 对fd调用相应的poll
            - __poll_wait()
              - 将fd挂到等待队列上
              - 将进程状态设置为interuptable (睡眠且接受信号)
        - 如果有就绪事件或者超时就跳出来
        - 如果没有就将当前进程suspend,等待有就绪的时候就再被唤醒并且再次遍历一遍所有的fd.
      - 数据从内核空间拷贝到用户空间
      - 释放内核空间，和poll等待队列
      
[Brief introduction of poll/epoll usage](https://www.programmersought.com/article/72415747853/)<br>
[Linux driver explanation (3): explanation of poll mechanism](https://www.programmersought.com/article/21054095639/)<br>
[Linux内核：poll机制](https://blog.csdn.net/jansonzhe/article/details/48576025)<br>

### epoll<br>
- epoll_create(int size)
  - eventpoll
  - epitem
- epoll_ctl(int size)
  - ep_insert
    - 申请epitem对象，并初始化
    - 调用该监听文件的poll接口  
      - 例如：tcp_poll
        - poll_wait
          - ep_ptable_queue_proc(),将当前epitem对象加到socket的等待队列上，并设置ep_poll_callback,当socket状态改变时,出发callback
            - 若有状态改变，将就绪的文件添加到eventpoll对象的就绪队列当中，唤醒在epoll_wait的进程
              - 状态改变是通过内核的中断处理函数知道的，来自网卡的硬件中断，及后续的软中断
    - 如果已经ready,就添加到就绪队列当中
    - 唤醒调用epoll_wait的进程，唤醒调用file->poll的进程
- epoll_wait
  - sys_epoll_wait
    - ep_poll
      - 如果没有就绪的事件，就将当前进程添加到epoll的等待队列，并睡眠
        - 有就绪，超时，信号，就停止睡眠
      - 有就绪事件ep_send_events()把就绪事件复制到events参数当中     
- LT,ET,EPOLLONESHOT




![](https://mmbiz.qpic.cn/mmbiz_jpg/ciab8jTiab9J7oou7m3TsR2NhOrHnNFqibIGW2VzT7Pqf5VIibN3QWj44htzkrvOfnTcJlzicg2Y3Hq220XSVEa3ibjg/640?wx_fmt=jpeg)<br>

[epoll内核源码详解+自己总结的流程 ](https://www.nowcoder.com/discuss/26226)<br>
[Epoll 如何工作的?](https://www.ershicimi.com/p/6754e4da3554da74821f8fd4a3a5bbb9)<br>
[epoll 的本质是什么？](https://my.oschina.net/editorial-story/blog/3052308)<br>
[源码解读epoll内核机制](http://gityuan.com/2019/01/06/linux-epoll/)


### 各自优缺点和应用场合对比<br>
- select
  - 缺点
    - select会修改传递进来的fd_sets，导致它们不能被复用。即使你不需要做任何改变，例如当一个描述符接收到数据后还需要接收更多的数据，整个集合都需要再次重新构建或者使用FD_COPY来从备份中恢复。并且每次调用select时都需要这些操作。
    - 找到是哪个描述符产生的事件，需要调用FD_ISSET遍历集合中的所有描述符。当你有2000个描述符时，并且只有一个产生了事件而且是最后一个，导致每次循环都会浪费大量CPU资源。
    - 我刚刚提到了2000个描述符吗？好吧select并不能支持这个多个描述符。至少在Linux上所支持的最大描述符数量是1024个，它保存在FD_SETSIZE常量中。有些操作系统允许你在包含sys/select.h头文件之前重新定义FD_SETSIZE的值，但是这就失去了可移植性。而且Linux会忽略它，保持原有的限制不变。
    - 当描述符在select中被监听时其他的线程不能修改它。假设你有一个管理线程检测到sock1等待输入数据的时间太长需要关闭它，以便重新利用sock1来服务其他工作线程。但是它还在select的监听集合中。如果此时这个套接字被关闭会发生什么？select的man手册中有解释：如果select正在监听的套接字被其他线程关闭，结果是未定义的。
    - 当填充描述符集合时，select会给你带来额外的负担，因为你需要计算描述符中的最大值并把它当作函数参数传递给select。
  - 优点
    - 可移植性好，定每个支持网络和非阻塞套接字的平台都会支持select
    - 超时时间可以精确到纳秒，对于桌面或者服务器系统来说没有任何区别，因为它们不会运行在纳秒精度的时钟上，但是在某些与硬件交互的实时嵌入式平台上可能是需要的。
- poll
  - 缺点
    - 和select一样必须通过遍历描述符列表来查找哪些描述符产生了事件。更糟糕的是在内核空间也需要通过遍历来找到哪些套接字正在被监听，然后在重新遍历整个列表来设置事件。
    - 和select一样它也不能在描述符被监听的状态下修改或者关闭套接字。
  - 优点
    - 它监听的描述符数量没有限制，可以超过1024。
    - 它不会修改pollfd结构体中传递的数据，因此可以复用只需将产生事件的描述符对应的revents成员置0。IEEE规范中规定：“poll()函数应该负责将每个pollfd结构体中revents成员清0，除非应用程序通过上面列出的事件设置对应的标记位来报告事件，poll()函数应该判断对应的位是否为真来设置revents成员中对应的位”。但是根据我的经验至少有一个平台没有遵循这个建议，Linux中的man 2 poll 就没有做出这样的保证。
    - 相比于select来说可以更好的控制事件。例如，它可以检测对端套接字是否关闭而不需要监听它的读事件。
    - 选择（相比epoll满足下面条件的话选择poll）
      - 你需要在不止Linux一个平台上运行，而且不希望使用epoll的封装库。例如libevent（epoll是Linux平台上特有的）。
      - 同一时刻你的应用程序监听的套接字少于1000（这种情况下使用epoll不会得到任何益处）
      - 同一时刻你的应用程序监听的套接字大于1000，但是这些连接都是非常短的连接（这种情况下使用epoll也不会得到任何益处，因为epoll所带来的加速都会被添加新描述符到集合中时被抵消）。
      - 你的应用程序没有被设计成在改变事件时而其他线程正在等待事件。
- epoll
  - 缺点(相比poll)
    - 改变监听事件的类型（例如从读事件改为写事件）需要调用epoll_ctl系统调用，而这在poll中只需要在用户空间简单的设置一下对应的掩码。如果需要改变5000个套接字的监听事件类型就需要5000次系统调用和上下文切换（直到2014年epoll_ctl函数仍然不能批量操作，每个描述符只能单独操作），这在poll中只需要循环一次pollfd结构体。
    - 每一个被accept()的套接字都需要添加到集合中，在epoll中必须使用epoll_ctl来添加–这就意味着每一个新的连接都需要两次系统调用，而在poll中只需要一次。如果你的服务有非常多的短连接它们都接受或者发送少量数据，epoll所花费的时间可能比poll更长。
    - epoll是Linux上独有的，虽然其他平台上也有类似的机制但是他们的区别非常大，例如边沿触发这种模式是非常独特的（FreeBSD的kqueue对它的支持非常粗糙）。
    - 高性能服务器的处理逻辑非常复杂，因此更加难以调试。尤其是对于边沿触发，如果你错过了某次读/写操作可能导致死锁。
  - 优点
    - epoll只会返回有事件发生的描述符，所以不需要遍历所有监听的描述符来找到哪些描述符产生了事件。
    - 你可以将处理对应事件的方法和所需要的数据附加到被监听的描述符上。在上面的例子中我们附加了一个类的指针，这样就可以直接调用处理对应事件的方法。
    - 你可以在任何时间添加或者删除套接字，即使有其他线程正在epoll_wait函数中。你甚至可以修改正在被监听描述符的事件，不会产生任何影响。这种行为是被官方支持的而且有文档说明。这样就可以使我们在写代码时有更大的灵活性。
    - 因为内核知道所有被监听的描述符，所以即使没有人调用epoll_wait()，内核也可以记录发生的事件，这允许实现一些有趣的特性，例如边沿触发，这将在另一篇文章中讲到。
    - epoll_wait()函数可以让多个线程等待同一个epoll队列而且推荐设置为边沿触发模式，这在其他轮询方式中是不可能实现的。
    - 选择 (满足下面条件选择epoll)
      - 你的程序通过多个线程来处理大量的网络连接。如果你的程序只是单线程的那么将会失去epoll的很多优点。并且很有可能不会比poll更好。
      - 你需要监听的套接字数量非常大（至少1000）；如果监听的套接字数量很少则使用epoll不会有任何性能上的优势甚至可能还不如poll。
      - 你的网络连接相对来说都是长连接；就像上面提到的epoll处理短连接的性能还不如poll因为epoll需要额外的系统调用来添加描述符到集合中。
      - 你的应用程序依赖于Linux上的其他特性（这样对于可移植性来说epoll就不是唯一障碍），或者你可以使用libevent这种包装库来屏蔽不同平台的差异。
      
[select poll epoll之间该如何决择](http://cxd2014.github.io/2018/01/10/epoll/)
