UUID
====
### 四个版本

- 基于时间
    - 时间戳、随机数和机器MAC地
- 基于DEC安全
    - 安全的UUID和基于时间的UUID算法相同，
      但会把时间戳的前4位置换为POSIX的UID或GID。这个版本的UUID在实际中较少用到
- 基于名字
    - 名字空间是一个维度，名字是一个维度，两者只要有一个不一样那么就可以说是不同的
- 随机