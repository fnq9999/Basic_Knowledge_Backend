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
![](https://mmbiz.qpic.cn/mmbiz_jpg/ciab8jTiab9J7oou7m3TsR2NhOrHnNFqibIGW2VzT7Pqf5VIibN3QWj44htzkrvOfnTcJlzicg2Y3Hq220XSVEa3ibjg/640?wx_fmt=jpeg)<br>



[epoll内核源码详解+自己总结的流程 ](https://www.nowcoder.com/discuss/26226)<br>
[Epoll 如何工作的?](https://www.ershicimi.com/p/6754e4da3554da74821f8fd4a3a5bbb9)<br>
[epoll 的本质是什么？](https://my.oschina.net/editorial-story/blog/3052308)<br>
[源码解读epoll内核机制](http://gityuan.com/2019/01/06/linux-epoll/)
