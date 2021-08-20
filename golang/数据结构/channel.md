Channel
======
- channel是一个fifo


```cgo

type hchan struct {
	qcount   uint           // total data in the queue
	dataqsiz uint           // size of the circular queue
	buf      unsafe.Pointer // points to an array of dataqsiz elements
	elemsize uint16
	closed   uint32
	elemtype *_type // element type
	sendx    uint   // send index
	recvx    uint   // receive index
	recvq    waitq  // list of recv waiters
	sendq    waitq  // list of send waiters

	// lock protects all fields in hchan, as well as several
	// fields in sudogs blocked on this channel.
	//
	// Do not change another G's status while holding this lock
	// (in particular, do not ready a G), as this can deadlock
	// with stack shrinking.
	lock mutex
}
```


- 发送
    - 如果revq非空，直接发送
    - 否则，如果缓冲区没满，写入缓冲区
    - 否则
        - 如果非阻塞发送
            - return false
        - 如果阻塞发送
            - 阻塞等待，放入sendq当中
- 接受
    - 如果sendq非空，直接接受
    - 否则，如果缓冲区没空，直接读缓冲区
    - 否则
        - 如果非阻塞接受
            - return flase
        - 如果阻塞接受
            - 阻塞等待
- 关闭
    - 对一个nil的channel close 会panic
    - 对一个已经close 的 channel close 也会 panic
    - 做了什么
        - channel关闭之后，会将两个等待队列中的goroutine都塞入一个列表
        - 如果缓冲区当中有数据，那么接受者继续接受数据
        - 数据接受完了，接受者收到false 表示关闭

