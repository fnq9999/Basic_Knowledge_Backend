参考:[leetcode 一些快慢指针题](https://blog.csdn.net/m0_43602209/article/details/109643329)
### leetcode 142[环形链表](https://leetcode-cn.com/problems/linked-list-cycle-ii/)
&emsp;题意是找环的第一个入口
&emsp;思路如下，快慢指针都指向头结点，一个两步一个一步，当两者相遇，将其中一个放到头结点，两个一起一步一步走，当相遇是就是入口节点。
- <img src="https://img-blog.csdnimg.cn/20201111190016428.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQyNTc2Njg3,size_16,color_FFFFFF,t_70#pic_center" width="50%">

```cgo
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *x) {
        if(!x)return NULL;
        ListNode *p1=x,*p2=x;
        while(p2 and p2->next){
            p2=p2->next->next;
            p1=p1->next;
            if(p2==p1){
                p2=x;
                while(p1!=p2){
                    p1=p1->next;
                    p2=p2->next;
                }
                return p1;
            }
        }
        return NULL;
    }
};
```

[leetcode 287寻找重复数](https://leetcode-cn.com/problems/find-the-duplicate-number/)
&emsp;给定一个包含 n + 1 个整数的数组 nums，其数字都在 1 到 n 之间（包括 1 和 n），可知至少存在一个重复的整数。假设只有一个重复的整数，找出这个重复的数。

```cgo
class Solution {
public:
    int findDuplicate(vector<int>& a) {
        int ind1=0,ind2=0;
        while(1){
            ind1=a[ind1];
            ind2=a[ind2];
            ind2=a[ind2];
            if(ind1==ind2){
                ind2=0;
                while(ind1!=ind2){
                    ind1=a[ind1];
                    ind2=a[ind2];
                }
                return ind1;
            }
        }
        return 0;
    }
};
```


[leetcode 876. 链表的中间结点](https://leetcode-cn.com/problems/middle-of-the-linked-list/)
&emsp; 给定一个头结点为 head 的非空单链表，返回链表的中间结点。如果有两个中间结点，则返回第二个中间结点。
```cgo
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode *p1=head,*p2=head;
        while(p2 and p2->next){
            p1=p1->next;
            p2=p2->next->next;
        }
        return p1;
    }
};
```


[leetcode 234 回文联表](https://leetcode-cn.com/problems/palindrome-linked-list/submissions/)
&emsp;题意：判断链表是不是回文联表
&emsp;解：在链表前面增加两个虚节点，然后双指针向后找，找到的节点就是中间节点的前一个。将后面的链表进行翻转，然后对比一下

```cgo
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        ListNode *tem1=new ListNode();
        ListNode *ans=new ListNode();
        tem1->next=head;
        ans->next=tem1;
        ListNode *p1=ans,*p2=ans;
        while(p2 and p2->next){
            p1=p1->next;
            p2=p2->next->next;
        }
        ListNode *p1_next=p1->next;
        p1->next=NULL;
        ListNode *cur=NULL,*pre=p1_next;
        while(pre){
            ListNode *tem=pre->next;
            pre->next=cur;
            cur=pre;
            pre=tem;
        }
        p1=ans->next->next;
        p2=cur;
        while(p1 and p2){
            if(p1->val!=p2->val)return false;
            p1=p1->next;
            p2=p2->next;
        }
        return true;
    }
};

```

