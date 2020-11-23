HTTP报文解析
===============
### 为什么用状态机？
- 提高效率
    - 有了状态的概念，在解析HTTP报文时，可以分阶段来读取内容，而不是对于TCP这种基于字节流的传输每次都从头到尾来解析这个报文。一个简单的例子就是 费波那契的计算，我们可以利用之前的状态来到达现在的状态，而不是每次都从头开始计算。当然，如果是UDP这种基于报文的传输协议，每次从头到尾读一遍还是可以的
- 可维护性强
- 解耦
- 扩展性强，可以分成一个模块一个模块进行优化
- 对程序员要求高，如果对状态的错误理解，错误的分割，只会让程序晦涩难懂，好的状态分割使得程序扩展性强，容易维护，容易找Bug
    
### 状态机工作原理
- 从状态机:parse_line
    - 总共三个line_status：
        - line_open:没读完，返回NO_REQUST等待后继的读入内容
        - line_bad：这一行已经出错,返回NO_REQUST,交给主线程继续读入内容
        - line_ok：成功读取一行，进行逻辑处理
- 主状态机
    - 不断调用从状态机来读取每一行，在每个状态中
    - 三个状态
        - CHECK_STATE_REQUSTLINE
            - 调用 pase_requst_line：解析出method,url,version
        - CHECK_STATE_LINE
            - 调用 pase_headers:解析首部（知道客户要求什么）
                - 如果首部没有内容，并且content没有内容，那么直接返回url中内容(调度do_request)
                - 如果首部没有内容，但是content有内容进入到最后一个状态
        - CHECK_STATE_CONTENT 
            - 调用 pase_content()
                - 如果read_idx<check_idx+m_content_length,那么返回NO_REQUEST,主线程继续读入
                - 处理content
            




