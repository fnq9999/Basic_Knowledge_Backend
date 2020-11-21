

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



![](https://mmbiz.qpic.cn/mmbiz_jpg/ciab8jTiab9J7oou7m3TsR2NhOrHnNFqibIGW2VzT7Pqf5VIibN3QWj44htzkrvOfnTcJlzicg2Y3Hq220XSVEa3ibjg/640?wx_fmt=jpeg)<br>

[epoll内核源码详解+自己总结的流程 ](https://www.nowcoder.com/discuss/26226)<br>
[Epoll 如何工作的?](https://www.ershicimi.com/p/6754e4da3554da74821f8fd4a3a5bbb9)<br>
[epoll 的本质是什么？](https://my.oschina.net/editorial-story/blog/3052308)<br>
[源码解读epoll内核机制](http://gityuan.com/2019/01/06/linux-epoll/)
