sticky session
=====================

### 为什么需要 session persistence
- 负载均衡时，可能会把一个客户的请求一次传给 serverA ,一会儿serverB。局部性原理没有充分利用。
### 有哪些方式
参考:[Sticky Session](https://www.imperva.com/learn/availability/sticky-session-persistence-and-cookies/)
- 基于client ip的
- 基于 cookie的
    - Duration-based session persistence: balancer有会话表和定时器，定时器超时这个会话过期，session 不再sticky
    - Application-controlled session persistence  :你的应用来控制duration,balancer同样会加上他自己的session cookie,但是他现在听应用cookie的duration
