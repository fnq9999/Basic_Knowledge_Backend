### 本地向对方传<br>
    .\pscp.exe -P [port number] [file] [user_name]@[ip_add]:[file_add]
    例如：.\pscp.exe -P 22 tem_file/index2.html root@47.100.44.113:/root/tem_file/

### 下载对方文件<br>
    .\pscp.exe -P [port number] [user_name]@[ip_add]:[file] [file_addr] 
    例如：.\pscp.exe -P 22 root@47.100.44.113:/root/tem_file/index2.html /tem_file



### 前台后台<br>
    nohup ./xxx &
    将xxx命令 在(&)后台执行
    bg xxx   #xxx是PID
    将后台PID放到前台运行
