TCP 介绍
=================
### TCP 概念<br>
- TCP可靠性
  - 滑动窗口
  - 超时重传
    - RTT：加权平均来计算
    - RTO：由上面的RTT+4RTT_D
    - RTT_D：RTT偏差的加权平均
  - SACK
    - 指明SACK需要1字节，说明SACK选项长度需要1字节
    - 一个段需要两个数据，每个数据4字节。
    - 会在TCP的首部开销很大

### 三报文握手<br>
<img src="https://raw.githubusercontent.com/fnq9999/Basic_Knowledge_Backend/master/%E8%AE%A1%E7%BD%91/image/%E4%B8%89%E6%AC%A1%E6%8F%A1%E6%89%8B.png" width="50%" /><br>
<img src="https://raw.githubusercontent.com/fnq9999/Basic_Knowledge_Backend/master/%E8%AE%A1%E7%BD%91/image/%E5%9B%9B%E6%AC%A1%E6%8F%A1%E6%89%8B.png" width="50%" /><br>




### TCP 滑动窗口<br>
- 可靠传输
  - 以字节为单位
  - 以报文形式发送
  - 三个指针  p1 p2 p3 
    - p1 滑动窗口开始节点
    - p2 未发送开始点
    - p3 窗口外第一点
  - 确认
    - 双方同时通信可采用捎带确认的方式
    - 延迟确认不允许超过0.5s,超长报文应该及时确认
-   - 发送方收到确认之后，调整滑动窗口，再进行发送
- 流量控制





