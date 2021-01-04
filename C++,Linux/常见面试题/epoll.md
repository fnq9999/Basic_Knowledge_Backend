

### epoll为什么使用红黑树不用哈希表
- 1.epoll的使用场合是动态数据，多少不确定。红黑树更适合
- 2.哈希表适合静态数据，一开始数据多少就确定了，因为哈希表rehash要浪费时间，
- 3.并且哈希表在装在系数小于1的情况下 内存开销要大很多。

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
            - 若有状态改变，将就绪的文件添加到eventpoll对象的rdllist当中，唤醒在epoll_wait的进程
              - 状态改变是通过内核的中断处理函数知道的，来自网卡的硬件中断，及后续的软中断
    - 如果已经ready,就添加到rdllist当中?
    - 唤醒调用epoll_wait的进程，唤醒调用file->poll的进程
- epoll_wait
  - sys_epoll_wait
    - ep_poll
      - 如果没有就绪的事件，就将当前进程添加到epoll的等待队列，并睡眠
        - 有就绪，超时，信号，就停止睡眠
      - 有就绪事件ep_send_events()把就绪事件复制到events参数当中     
- LT,ET,EPOLLONESHOT
  - epoll_wait()
    - ep_poll()
      -  ep_send_events()
        - ep_scan_ready_list()
          - 将epollevent对象的所有就绪对象都链接到txlist上，rdllist清空
          - ep_send_events_proc()
            - 扫描整个链表
            - 对事件再次做poll()，虽然已经在callback的时候已经poll过，是为了得到最新的数据，并且有的驱动程序没有把events返回，
            - 如果revents有，放入用户空间
              - 如果EPOLLONESHOT,那么对epi->event.events &= EP_PRIVATE_BITS;
              - 如果ET,不放入ep的rdllist
              - LT,放入rdllist.
            - 返回放入用户空间的数量
- epitem放入到rdllist的情况：（LT和ET的重点就在rdllist）
    - **epoll_wait只会检查rdllist中的epitem**
    - ep_poll_callback,由软中断来调用该函数，该函数将epitem放入rdllist
    - epoll_insert函数，如果直接检测到就绪，那么也放入rdllsit,并且唤醒epoll_wait的进程
    - epoll_modify也会检测到就绪就放入rdllist，并且唤醒
- epoll对于 多个进程监听同一个sockfd的问题，以至于每次会唤醒多个进程来处理同一时间，导致CPU空转
    - 可以使用 so_reuseport来解决惊群问题，支持多个进程线程绑定到同一个端口，由内核来完成多个进程中fd的协调问题
    - 只会唤醒一个进程
    
- epoll 惊群问题
    - 在2.6.18内核中accept的惊群问题已经被解决了，但是在epoll中仍然存在惊群问题，表现起来就是当多个进程/线程调用epoll_wait时会阻塞等待，当内核触发可读写事件，所有进程/线程都会进行响应，但是实际上只有一个进程/线程真实处理这些事件。
    - 在epoll官方没有正式修复这个问题之前，Nginx作为知名使用者采用全局锁来限制每次可监听fd的进程数量，每次只有1个可监听的进程，后来在Linux 3.9内核中增加了SO_REUSEPORT选项实现了内核级的负载均衡，Nginx1.9.1版本支持了reuseport这个新特性，从而解决惊群问题。
        - 参考:[Linux 最新SO_REUSEPORT特性](https://www.cnblogs.com/anker/p/7076537.html)
        - so_reuseport支持多个进程或者线程绑定到同一个端口。
            - 允许多个套接字bind()/listen同一个TCP/UDP端口，每个线程都拥有了服务器套接字，并且没有锁的竞争
            - 内核层面上负载均衡
            - 安全层面，监听同一个端口的套接字只能位于同一个用户下面
        - 实现方法
            - 扩展socket option 增加 该选项
            - 修改bind系统调用，以便可以绑定到相同的IP和端口
            - 修改处理新建连接的实现，查找listener的时候，能够支持在监听相同IP和端口的多个sock之间负载均衡
            
        
    - EPOLLEXCLUSIVE是在2016年Linux 4.5内核新添加的一个 epoll 的标识，Ngnix 在 1.11.3 之后添加了NGX_EXCLUSIVE_EVENT选项对该特性进行支持。EPOLLEXCLUSIVE标识会保证一个事件发生时候只有一个线程会被唤醒，以避免多侦听下的惊群问题。
    
![](https://mmbiz.qpic.cn/mmbiz_jpg/ciab8jTiab9J7oou7m3TsR2NhOrHnNFqibIGW2VzT7Pqf5VIibN3QWj44htzkrvOfnTcJlzicg2Y3Hq220XSVEa3ibjg/640?wx_fmt=jpeg)<br>

[epoll内核源码详解+自己总结的流程 ](https://www.nowcoder.com/discuss/26226)<br>
[Epoll 如何工作的?](https://www.ershicimi.com/p/6754e4da3554da74821f8fd4a3a5bbb9)<br>
[epoll 的本质是什么？](https://my.oschina.net/editorial-story/blog/3052308)<br>
[源码解读epoll内核机制](http://gityuan.com/2019/01/06/linux-epoll/)
[从linux源码看epoll_图多](https://my.oschina.net/alchemystar/blog/3008840)