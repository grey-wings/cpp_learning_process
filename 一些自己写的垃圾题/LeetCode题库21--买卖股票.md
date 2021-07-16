[题目链接：买卖股票的最佳时机（单次）](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/)  

单调栈解法：  
```cpp
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
```
