## HTTP/HTTPS<br>

### 客户端是验证证书过程<br>
<img src="https://pic3.zhimg.com/80/v2-91a73cf1b4b72978a380fa08fc2fa6dd_720w.jpg"  width="40%"/><br>

- three-way handshake
- client helo
  - ssl版本
  - 加密组间
    - 加密算法
    - 秘钥长度
- server hello
  - ssl版本
  - 加密组件(从clienthello报文中得到的)
-verify server certificate
  - 抽到数字证书
  - 使用相同的hash算法得到数字证书的hash值得到'H1'
  - 使用CA公钥来解密证书中的 certificate signature 得到 H2
  - 若H2==H1那么信任证书。 [参考](https://www.cnblogs.com/MR-Guo/p/11584730.html)

- Client key exchange
- send client certificate
- clinet "finished"
- server "finished"
- exchange messages

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
