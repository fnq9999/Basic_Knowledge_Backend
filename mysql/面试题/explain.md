explain
=======

### 每个字段的含义

|Column |	含义|
| --- | ---  |
|id	|查询序号|
| select_type| 查询类型|
|table|	表名
|partitions|	匹配的分区
|type	|join类型
|prossible_keys	|可能会选择的索引
|key	|实际选择的索引
|key_len	|索引的长度
|ref	|与索引作比较的列
|rows	|要检索的行数(估算值)
|filtered	|查询条件过滤的行数的百分比
|Extra	|额外信息


- partitions:当前查询匹配记录的分区。对于未分区的表，返回null