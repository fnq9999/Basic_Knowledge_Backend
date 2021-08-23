HTTP常见面试题
======

### HTTP 传输文本和传输图片和传视频区别
- 主题过程基本类型，区别在于Content-type不同
    - 文本
    - 图片
    - 其实就算响应报文当中的Content-type写错了，也没关系，浏览器会纠正
      
- 为什么有的图片是一点点加载的
    - 这是因为整个图片是多个小图片组装起来的，也就是说这里面有多对HTTP请求和HTTP响应
  

- 传视频
  - Content-Type:video/mp4
  - 请求header:Range:(unit=first byte pos)-[last byte pos]
  - 响应报文Header:Content-Range:Content-Range: bytes (unit first byte pos) - [last byte pos]/[entity legth]    :应用于断点传输
  - status code:206
### 断点传输
