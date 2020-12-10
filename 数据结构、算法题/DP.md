

### [leetcode_10_正则表达式匹配](https://leetcode-cn.com/problems/regular-expression-matching/)<br>
        
        给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。
        
            '.' 匹配任意单个字符
            '*' 匹配零个或多个前面的那一个元素
        
        所谓匹配，是要涵盖 整个 字符串 s的，而不是部分字符串。

```cgo
class Solution {
public:
    bool isMatch(string s, string p) {
        int n=s.size(),m=p.size();
        int f[n+1][m+1];
        memset(f,0,sizeof(f));
        f[0][0]=1;
        auto mat=[&](int i,int j){
            if(i==0)return false;
            if(p[j-1]=='.')return true;//// 随便匹配
            return s[i-1]==p[j-1];
        };
        for(int j=1;j<=m;++j){
            if(p[j-1]=='*'){
                f[0][j]|=f[0][j-2];
            }
        }
        for(int i=1;i<=n;++i){
            for(int j=1;j<=m;++j){
                if(p[j-1]=='*'){
                    f[i][j]|=f[i][j-2];///// ‘*'前面的字符当成0个
                    if(mat(i,j-1)){   ///// ‘*’代表了多个j-1位置的字符
                        f[i][j]|=f[i-1][j];
                    }
                }else{
                    if(mat(i,j)){//// 
                        f[i][j]|=f[i-1][j-1];
                    }
                }
            }
        }
        return f[n][m];
    }
};

```