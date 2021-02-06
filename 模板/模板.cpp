//
// Created by ZHK on 2021/2/2.
//
#include <bits/stdc++.h>
/* 宏 */
#define fu(i,r,t) for(int i=r;i<=t;i++)
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(V) V.begin(),V.end()
#define print(i) cout<<(i)<<endl;

/* 定义 */
typedef queue<int> QUEUEINT;
typedef list<int> LISTINT;
typedef set<int> SETINT;

/* STL */
1.vector
二维vector:vector<vector<int>> a(n)

2.list
typedef list<int> LISTINT;
LISTINT sb;
LISTINT ::iterator iter;(迭代器)

/* 算法 */
1.二分
二分模板1:(由中间向下取)
//注意!最后输出的l并不一定在初始的l-r之间,即最终的l可以>r!!
//多少多
int l=0,mid,r=n;
bool can(int x)
{
    int num=0;
    fun(i)num+=max((int)0,a[i]-x);
    return num>=m;
}
while(l<=r)
{
mid=(l+r)/2;
//mid=l+r>>1;
if(can(mid))//答案在中间以下
{
r=mid-1;
}else{
l=mid+1;
}
}
cout<<l;

r多（多少多）l少（少多少）
即r>l

//少多少
二分模板2:
//注意!最后二分出的l并不一定在初始的l-r之间,即最终的l可以>r!!
//所以如果要判断l是否合理还要加上 if(l<=begin_r && can(l))..
int l=0,mid,r=n;//注意,此时r不能=LLONG_MAX,因为下面会加一爆出去,所以最多LLONG_MAX-1;
while (l < r)
{
mid = l + r + 1 >> 1;
if (can(mid)) l = mid;//答案在中间以上,即第一个满足条件的传入值
else r = mid - 1;
}
cout<<l;

2.树状数组
计算a[x]管理几个数
int lowbit(int x)
{
    // 算出x二进制的从右往左出现第一个1以及这个1之后的那些0组成数的二进制对应的十进制的数
    return x & -x;
}

3.高精度
//compare比较函数：相等返回0，大于返回1，小于返回-1
int compare(string str1,string str2)
{
    if(str1.length()>str2.length()) return 1;
    else if(str1.length()<str2.length())  return -1;
    else return str1.compare(str2);
}
//高精度加法
//只能是两个正数相加
string add(string str1,string str2)//高精度加法
{
    string str;
    int len1=str1.length();
    int len2=str2.length();
    //前面补0，弄成长度相同
    if(len1<len2)
    {
        for(int kk=1;kk<=len2-len1;kk++)
            str1="0"+str1;
    }
    else
    {
        for(int kk=1;kk<=len1-len2;kk++)
            str2="0"+str2;
    }
    len1=str1.length();
    int cf=0;
    int temp;
    for(int kk=len1-1;kk>=0;kk--)
    {
        temp=str1[kk]-'0'+str2[kk]-'0'+cf;
        cf=temp/10;
        temp%=10;
        str=char(temp+'0')+str;
    }
    if(cf!=0)  str=char(cf+'0')+str;
    return str;
}
//高精度减法
//只能是两个正数相减，而且要大减小
string sub(string str1,string str2)//高精度减法
{
    string str;
    int tmp=str1.length()-str2.length();
    int cf=0;
    for(int kk=str2.length()-1;kk>=0;kk--)
    {
        if(str1[tmp+kk]<str2[kk]+cf)
        {
            str=char(str1[tmp+kk]-str2[kk]-cf+'0'+10)+str;
            cf=1;
        }
        else
        {
            str=char(str1[tmp+kk]-str2[kk]-cf+'0')+str;
            cf=0;
        }
    }
    for(int kk=tmp-1;kk>=0;kk--)
    {
        if(str1[kk]-cf>='0')
        {
            str=char(str1[kk]-cf)+str;
            cf=0;
        }
        else
        {
            str=char(str1[kk]-cf+10)+str;
            cf=1;
        }
    }
    str.erase(0,str.find_first_not_of('0'));//去除结果中多余的前导0
    return str;
}
//高精度乘法
//只能是两个正数相乘
string mul(string str1,string str2)
{
    string str;
    int len1=str1.length();
    int len2=str2.length();
    string tempstr;
    for(int kk=len2-1;kk>=0;kk--)
    {
        tempstr="";
        int temp=str2[kk]-'0';
        int t=0;
        int cf=0;
        if(temp!=0)
        {
            for(int jj=1;jj<=len2-1-kk;jj++)
              tempstr+="0";
            for(int jj=len1-1;jj>=0;jj--)
            {
                t=(temp*(str1[jj]-'0')+cf)%10;
                cf=(temp*(str1[jj]-'0')+cf)/10;
                tempstr=char(t+'0')+tempstr;
            }
            if(cf!=0) tempstr=char(cf+'0')+tempstr;
        }
        str=add(str,tempstr);
    }
    str.erase(0,str.find_first_not_of('0'));
    return str;
}
//高精度除法
//两个正数相除，商为quotient,余数为residue
//需要高精度减法和乘法
void div(string str1,string str2,string &quotient,string &residue)
{
    quotient=residue="";//清空
    if(str2=="0")//判断除数是否为0
    {
        quotient=residue="ERROR";
        return;
    }
    if(str1=="0")//判断被除数是否为0
    {
        quotient=residue="0";
        return;
    }
    int res=compare(str1,str2);
    if(res<0)
    {
        quotient="0";
        residue=str1;
        return;
    }
    else if(res==0)
    {
        quotient="1";
        residue="0";
        return;
    }
    else
    {
        int len1=str1.length();
        int len2=str2.length();
        string tempstr;
        tempstr.append(str1,0,len2-1);
        for(int ii=len2-1;ii<len1;ii++)
        {
            tempstr=tempstr+str1[ii];
            tempstr.erase(0,tempstr.find_first_not_of('0'));
            if(tempstr.empty())
              tempstr="0";
            for(char ch='9';ch>='0';ch--)//试商
            {
                string str,tmp;
                str=str+ch;
                tmp=mul(str2,str);
                if(compare(tmp,tempstr)<=0)//试商成功
                {
                    quotient=quotient+ch;
                    tempstr=sub(tempstr,tmp);
                    break;
                }
            }
        }
        residue=tempstr;
    }
    quotient.erase(0,quotient.find_first_not_of('0'));
    if(quotient.empty()) quotient="0";
}
