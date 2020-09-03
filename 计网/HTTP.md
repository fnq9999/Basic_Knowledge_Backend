## HTTP/HTTPS<br>
### SSL/TLS<br>
#### SSL是什么:<br>
&emsp;应用层和网络层之间的一种协议层。SSL通过相互认证数字签名保证完整性、使用加密确保私密性，实现
客户端和服务器之间的安全通讯。协议分成SSL记录协议和SSL握手协议。<br>
SSL协议可分为两层：<br>
&emsp;SSL记录协议(SSL Record Protocol)：它建立在可靠的传输协议(如TCP)之上，为高层协议提供数据封装、压缩、加密等基本功能的支持。 SSL握手协议(SSL Handshake Protocol)：它建立在SSL记录协议之上，用于在实际的数据传输开始前，通讯双方进行身份认证、协商加密算法、交换加密密钥等。

### TLS:<br>
&emsp;用于两个应用程序之间提供保密性和数据完整性。该协议由两层组成：TLS记录协议和TLS握手协议。




<br>
参考：[SSL与TLS的区别以及介绍](https://www.cnblogs.com/susanhonly/p/7489532.html)
