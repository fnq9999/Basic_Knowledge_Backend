Docker
========

## Docker容器网络

#### 网络模式
- bridge桥接
![](.docker_images/3d27ccf3.png)
    - DNAT：用于 正在监听的容器接受请求时，将请求的ip和port替换
    - SNAT：对容器向外的主动请求，将ip替换成宿主机ip
- host模式
![](.docker_images/9b51d021.png)<br>
    - 该模式下，容器和宿主机共享网络命名空间
    - 缺点就是缺少了隔离，造成端口资源的竞争
- other container
![](.docker_images/8df4f2a2.png)
    - 隔离性在bridge和host之间
    - 牺牲隔离性带来了容器间互访简约网络配置以及高效的传输效率，增容器之间的网络黏性
- none
    - 没有网络资源，只有loopback网络接口
