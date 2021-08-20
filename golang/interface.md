interface
======


- iface
    - 带有一组方法
- eface
    - 不带有任何方法
  

- 作用
  - 任何类型的对象实现interface所包含的全部方法，则表明该类型实现了该接口
  - 还可以作为一中通用的类型，其他类型变量可以给interface声明的变量赋值
  

- interface 类型变量的转换
  - ```cgo
    //方法一
    val, ok := i.(Animal)
    if !ok {
        fmt.Println("no")
    } else {
        fmt.Println(val.GetAge())
    }
    switch val := i.(type) {
      case string:
      fmt.Println(val)
      case int:
      fmt.Println(val)
      default:
      fmt.Println(val)
    }
    // 方法三 通过反射
    typename := reflect.TypeOf(i)
    fmt.Println(typename)
    ```
    
- 小问题
  - 当使用指针类型实现一个接口时，只有指针类型的变量才实现了该方法。