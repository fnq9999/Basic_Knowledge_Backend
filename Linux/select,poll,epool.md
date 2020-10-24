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

[Brief introduction of poll/epoll usage](https://www.programmersought.com/article/72415747853/)
[Linux driver explanation (3): explanation of poll mechanism](https://www.programmersought.com/article/21054095639/)
[Linux内核：poll机制](https://blog.csdn.net/jansonzhe/article/details/48576025)

### epoll<br>
