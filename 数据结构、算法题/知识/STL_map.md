Map
========

### multimap

- insert
```cgo
multimap<int,Node*>m;

void run(){
    Node *tem=new Node();
    int x=2;
    m.insert(pair<int,Node*>{x,tem});
    auto it =m.find(x);
    auto it=m.upper_bound(x);/// 大于x的第一个元素
    auto it=m.lower_bound(x);/// 不小于的第一个元素
    m.erase(it)//// 删除
    auto it =m.begin()/// 最小的
    {
        auto it=m.end();
        it--;// 现在指向的是最后一个元素    
    }    
    
}

```