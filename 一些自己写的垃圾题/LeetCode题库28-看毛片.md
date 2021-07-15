[题目链接](https://leetcode-cn.com/problems/implement-strstr/)  

参考：  
https://www.cnblogs.com/dusf/p/kmp.html  
https://blog.csdn.net/v_july_v/article/details/7041827  

## 一些理解  
### 1. i和j指针的定义  
i指向主串中的某个字符，j指向模式串中的某个字符。  
![](https://images0.cnblogs.com/blog/416010/201308/17083647-9dfd3e4a709c40dd98d9817927651960.png)  
如果i和j指向的字符相等，那么i和j都后移。  
![](https://images0.cnblogs.com/blog/416010/201308/17083659-e6718026bf4f48a0be2d5d6076be4c55.png)  

### 2. 当i和j指向的字符不匹配时，j移动到哪里？（下标从0开始）
当匹配失败时，j要移动的下一个位置k。存在着这样的性质：最前面的k个字符和j之前的最后k个字符是一样的。  
即P[0 ~ k-1] == P[j-k ~ j-1]  
关于这个公式的理解：  
![](https://images0.cnblogs.com/blog/416010/201308/17084056-66930855432b4357bafbf8d6c76c1840.png)  
举例示意：  
1.
![](https://images0.cnblogs.com/blog/416010/201308/17083912-49365b7e67cd4877b2f501074dae68d2.png)  
最前面的1个字符和最后面的1个字符一样，所以移动到第1位。  
![](https://images0.cnblogs.com/blog/416010/201308/17083929-a9ccfb08833e4cf1a42c30f05608f8f5.png)  
2.  
![](https://images0.cnblogs.com/blog/416010/201308/17084030-82e4b71b85a440c5a636d57503931415.png)  
最前面的2个字符和最后面的2个字符一样，所以移动到第2位。  
![](https://images0.cnblogs.com/blog/416010/201308/17084037-cc3c34200809414e9421c316ceba2cda.png)  

### 3. Next数组
#### 计算某个字符对应的next值，就是看这个字符之前的字符串中有多大长度的相同前缀后缀。  
比如：  
![](https://img-blog.csdn.net/20140728110939595)  
这里的“最大长度值”，就是最长相等前后缀的长度。  
已知next[0]到next[j]，如何求出next[j + 1]?  
#### 1. 当j为0时，不匹配  
![](https://images0.cnblogs.com/blog/416010/201308/17084258-efd2e95d3644427ebc0304ed3d7adefb.png)  
j已经在最左边了，不可能再移动了，这时候要应该是i指针后移。所以next[0]=-1  
#### 2. j为1，不匹配  
![](https://images0.cnblogs.com/blog/416010/201308/17084310-29f9f8dbb6034151a383e7ccf6f5583e.png)  
j只能移到0，即next[1]=0  
#### 3. 匹配的情况
这里next[j] == k  
![](https://images0.cnblogs.com/blog/416010/201308/17084327-8a3cdfab03094bfa9e5cace26796cae5.png)![](https://images0.cnblogs.com/blog/416010/201308/17084342-616036472ab546c082aa991004bb0034.png)  
当P[k] == P[j]时，有next[j + 1] == next[j] + 1  
#### 4. 一般不匹配情况  
当P[k] != P[j]时  
要往前找一个k'，使得P[k'] = P[j]，并且P[0 ~ k'] = P[j-k' ~ j]  
用下面这个图来辅助理解。  
![](https://img-blog.csdn.net/20150812214857858)  
当P[k] != P[j]时：
由上面第3点得，图中两个大括号括起来的长度为k的区域是相等的。  
在图中画出黄色的P[next[k]]的位置，则蓝色的四块相等。  
如果P[next[k]] == P[j]，那么P[0 ~ j]的最长相等前后缀的长度就是next[k] + 1，否则就继续往前找。  
如果找不到这个k'，那么next[j + 1]就等于0  

