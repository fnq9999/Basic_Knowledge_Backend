Linux 中 TCP开销
================
参考:[Linux 中每个 TCP 连接最少占用多少内存？](https://zhuanlan.zhihu.com/p/25241630)

| struct           | size | slab cache name    |
| --- | ---- | --- |
| file             |  256 | "filp"             |
| dentry           |  192 | "dentry"           |
| socket_alloc     |  640 | "sock_inode_cache" |
| tcp_sock         | 1792 | "TCP"              |
| socket_wq        |   64 | "kmalloc-64"       |
| inet_bind_bucket |   64 | "tcp_bind_bucket"  |
| epitem           |  128 | "eventpoll_epi"    |
| tcp_request_sock |  256 | "request_sock_TCP" |

- 总和：256 + 192 + 640 + 1792 + 64 = 2944 字节<br>
- 但是这个数字冰不准，原因如下
### 不准的原因
- slab的额外开销
- BDP开销
- epoll中的 epitem开销



