
### cookie 和 session<br>
- 减轻服务器的压力应当使用cookie

### HTTP状态码<br>
- 200 OK
- 400
  - 客户端请求有误，不能被服务器理解
- 401
  - 请求未授权
- 403 
  - 服务器收到请求，但是拒绝提供服务。
- 404
  - 资源找不到，输入了错误的URL
- 500
  - 服务器发生不可预期的错误。
- 503
  - 服务器当前不能处理客户端请求一段时间后可能恢复正常。
 
### RESTFUL API<br>
- get
  - 向服务器索取数据（幂等）
- post
  - 创建
- put
  - 更新（幂等）
- delete
  - 幂等
  


### 浏览器输入URL发生了什么<br>
- DNS缓存
  - 浏览器缓存
  - 系统缓存
  - 路由器缓存  
  - IPS服务器缓存
  - 域名服务器缓存
  - 顶级域名服务器缓存
- TCP连接
- HTTP连接
- 服务器处理请求并返回HTTP报文
- 浏览器解析渲染网页
- 连接结束



## HTTPS<br>
[Wireshark抓包帮你理清HTTPS请求流程_非常全面！！！](https://cloud.tencent.com/developer/article/1644729)<br>
[HTTPS 为什么更安全，先看这些_讲得来由很清楚](https://zhuanlan.zhihu.com/p/25324735)<br>
[使用wireshark分析HTTPS流程的建立](https://my.oschina.net/u/2457218/blog/794322)<br>
### HTTP为什么安全<br>
#### 1.应该使用对称加密传输数据，那么如何获取对称加密的秘钥<br>
#### 2.使用非对称加密得到用于对称加密的秘钥，那么如何得到非对称加密的公钥<br>
#### 3.使用得到CA认可的公钥，那么去和确保这个确实是CA是真的CA<br>
#### 4.使用数字签名技术<br>
- 签字者发送
    - 数据
    - 加密（hash(数据)）
- 验证方
    - 对数据进行hash->h1
    - 对加密后的数据进行解密->h2
    - 如果h1==h2验证成功
<img src="https://pic2.zhimg.com/80/v2-e1819aed10962a9d148a8b4460d606b5_720w.png"  width="60%"/><br>

### 客户端是验证证书过程<br>
<img src="https://pic3.zhimg.com/80/v2-91a73cf1b4b72978a380fa08fc2fa6dd_720w.jpg"  width="40%"/><br>
- TCP three-way handshake
- client helo
  - ssl版本
  - 随机数
  - SessionID
  - 加密组件
  - 压缩方法
  - 等等
- server hello
  - ssl版本
  - 随机数
  - 加密组件(从clienthello报文中得到的)
  - 和上面对应上
- Certificate
- Server Key Exchange
- Sever Hello Done
-verify server certificate
  - 抽到数字证书
  - 使用相同的hash算法得到数字证书的hash值得到'H1'
  - 使用CA公钥来解密证书中的 certificate signature 得到 H2
  - 若H2==H1那么信任证书。 [参考](https://www.cnblogs.com/MR-Guo/p/11584730.html)

- Client key exchange
- Change Cipher Spec 
- Encrypted Handshake Message

- exchange messages with shared secret key

### 再详细的HTTPS呢
&emsp;&emsp;客户端得到证书并且验证成功之后，生成一个pre_master_key ,它将用来跟服务端和客户端在Hello阶段产生的随机数结合在一起生成 Master Secret 。在客户端使用服务端的公钥对PreMaster Secret进行加密之后传送给服务端，服务端将使用私钥进行解密得到PreMaster secret。也就是说服务端和客户端都有一份相同的PreMaster secret和随机数。PreMaster secret前两个字节是TLS的版本号，这是一个比较重要的用来核对握手数据的版本号，因为在Client Hello阶段，客户端会发送一份加密套件列表和当前支持的SSL/TLS的版本号给服务端，而且是使用明文传送的，如果握手的数据包被破解之后，攻击者很有可能串改数据包，选择一个安全性较低的加密套件和版本给服务端，从而对数据进行破解。所以，服务端需要对密文中解密出来对的PreMaster版本号跟之前Client Hello阶段的版本号进行对比，如果版本号变低，则说明被串改，则立即停止发送任何消息。<br>
&emsp;&emsp;Master secret<br>
&emsp;&emsp;上面已经提到，由于服务端和客户端都有一份相同的PreMaster secret和随机数，这个随机数将作为后面产生Master secret的种子，结合PreMaster secret，客户端和服务端将计算出同样的Master secret。<br>
&emsp;&emsp;Master secret是有系列的hash值组成的，它将作为数据加解密相关的secret的 Key Material 的一部分。Key Material最终解析出来的数据如下：<br>
       
<img src="https://pic3.zhimg.com/80/v2-65dcd5a595c7c03160ef74c79f470c5a_720w.jpg"  width="20%"/><br>

    在所有的握手阶段都完成之后，就可以开始传送应用数据了。应用数据在传输之前，首先要附加上MAC secret，然后再对这个数据包使用write encryption key进行加密。在服务端收到密文之后，使用Client write encryption key进行解密，客户端收到服务端的数据之后使
    用Server write encryption key进行解密，然后使用各自的write MAC key对数据的完整性包括是否被串改进行验证。

### 在HTTPS基础上客户端每次请求都需要SSL握手传递秘钥吗
        浏览器可以以sessionID为单位临时存储用来加密的key等关键参数
        在*TLS握手阶段*浏览器会把自己的session id发给服务器，若服务器中存在一个以sessionId为索引的数据结构的话，那么检查里面
        是否有 session key,有的话就不需要交换秘钥了，这样避免了大量的幂、指数运算，如果没有的话正常走最开始的流程

### HTTPS 的安全性/HSTS<br>

### SSL/TLS<br>
#### SSL是什么:<br>
&emsp;应用层和网络层之间的一种协议层。SSL通过相互认证数字签名保证完整性、使用加密确保私密性，实现
客户端和服务器之间的安全通讯。协议分成SSL记录协议和SSL握手协议。<br>
SSL协议可分为两层：<br>
SSL记录协议(SSL Record Protocol)：它建立在可靠的传输协议(如TCP)之上，为高层协议提供数据封装、压缩、加密等基本功能的支持。 SSL握手协议(SSL Handshake Protocol)：它建立在SSL记录协议之上，用于在实际的数据传输开始前，通讯双方进行身份认证、协商加密算法、交换加密密钥等。<br>
#### SSL作用:<br>
    1）认证用户和服务器，确保数据发送到正确的客户机和服务器；<br>
    2）加密数据以防止数据中途被窃取；<br>
    3）维护数据的完整性，确保数据在传输过程中不被改变。<br>

### TLS是什么:<br>
    用于两个应用程序之间提供保密性和数据完整性。该协议由两层组成：TLS记录协议和TLS握手协议。<br>


## SSL/TLS区别：
    Well, 'TLS is actually just a more recent version of SSL'. It fixes some security vulnerabilities in the earlier SSL protocols.
    
    

参考：
[SSL与TLS的区别以及介绍](https://www.cnblogs.com/susanhonly/p/7489532.html)


