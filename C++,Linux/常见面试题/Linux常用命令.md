
### 分割与合并
参考:[Linux split 大文件分割与 cat合并文件](https://itbilu.com/linux/man/Nkz2hoeNm.html)
- 分割文件
    - split -c 100M xxx.txt after_name :按大小分割 
    - split -l 1000 xxx.txt after_name：按行分割
- 合并文件
    - cat after_name* > xxx.txt
### 日志
- 实时查看日志
    - tail -f xxx.log
  

### 其他
- top
- netstat