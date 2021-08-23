
RMQ
=====

### 基本组件
- Name Svr
  - 保存broker的meta信息，为producer和consumer查找broker使用
    提供路由信息,broker会和每一台 name server建立长连接
  - 可横向扩展，节点之间无通信  
- broker
  
- producer : 生产消息 发送到 broker
  
- consumer
    - 拉去型消费者：主动消费类型
    - 推送型消费者:
  
- 消息message
    - topic
    - tag
    - queue
  
- 采用拉模式：消费者从broker那里拉取消息

### 场景

### 功能

- 延迟消息:不会被立即消费的消息
- 事务消息
- 消息回溯:消费某个topic在某个时间段下的历史消息
- 死信队列:没有正常消费的消息首先会被重试，当达到重试次数之后，仍然失败，rmq不会立即
丢掉消息，而是把消息放入死信队列，放入死信队列的消息会在3天到期，需要及时处理
