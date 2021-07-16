[题目链接：买卖股票的最佳时机（单次）](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/)  

单调栈解法：  
```cpp
#include <bits/stdc++.h>
using namespace std;
#define fu(i,r,t) for(int i=r;i<=t;i++)
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(V) V.begin(),V.end()
#define print(i) cout<<(i)<<endl;
#define ll long long
#define ull unsigned long long
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty() or prices.size() == 1)
            return 0;
        stack<int> a;
        int ans = 0, head, tail, bottom = prices[0];
        a.push(bottom);
        for (int i = 1;i < prices.size();i++){
            if (prices[i] > a.top())
                a.push(prices[i]);
            else if (prices[i] == a.top())
                continue;
            else {
                if (prices[i] < bottom){
                    tail = a.top();
                    while (a.size() > 1)
                        a.pop();
                    head = a.top();
                    a.pop();
                    ans = max(ans, tail - head);
                    a.push(prices[i]);
                    bottom = prices[i];
                }
            }
        }
        ans = max(ans, a.top() - bottom);
        return ans;
    }
};
int main() {
    Solution sl;

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0;i < n;i++){
        cin >> a[i];
    }
    cout << sl.maxProfit(a);
    return 0;
}

```
