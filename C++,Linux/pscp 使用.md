### 本地向对方传<br>
    .\pscp.exe -P [port number] [file] [user_name]@[ip_add]:[file_add]
    例如：.\pscp.exe -P 22 tem_file/index2.html root@47.100.44.113:/root/tem_file/

### 下载对方文件<br>
    .\pscp.exe -P [port number] [user_name]@[ip_add]:[file] [file_addr] 
    例如：.\pscp.exe -P 22 root@47.100.44.113:/root/tem_file/index2.html ./tem_file

### scp密码问题
- scp传输前，需要提供远端机器root的密码
- 不希望提供密码，可以生成公钥私钥对，然后将所有的公钥传递给每台机器，
  用cat命令把id_ras.pub 追加到目标机器的authorized_keys文件内
    - 原理:
        - Server A 向 Server B 发送一个连接请求
        - Server B 得到 Server A 的信息后，在 authorized_key 中查找，如果有相应的用户名和 IP，则随机生成一个字符串，并用 Server A 的公钥加密，发送给 Server A；
        - Server A 得到 Server B 发来的消息后，使用私钥进行解密，然后将解密后的字符串发送给 Server B。Server B 进行和生成的对比，如果一致，则允许免密登录。

### 前台后台<br>
    nohup ./xxx &
    将xxx命令 在(&)后台执行
    bg xxx   #xxx是PID
    将后台PID放到前台运行
