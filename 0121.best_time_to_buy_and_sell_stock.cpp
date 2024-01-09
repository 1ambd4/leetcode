#include <iostream>
#include <limits>
#include <vector>
#include <stack>

using std::vector, std::stack;

int max_profit(vector<int>& prices)
{
    int n = prices.size();
    int min = prices[0];
    // dp[i]: 到 prices[i] 为至的最大收益
    vector<int> dp(n, 0);

    for (int i = 1; i < n; ++i) {
        min = std::min(min, prices[i]);
        dp[i] = std::max(dp[i-1], prices[i] - min);
    }

    return dp[n-1];
}

// 单调栈
int _max_profit(vector<int>& prices)
{
    stack<int> stk;
    int res = 0;
    for (auto price : prices) {
    if (stk.empty()) {
        stk.push(price);
            continue;
        }

        if (price <= stk.top()) {
            stk.push(price);
        } else {
            res = std::max(res, price - stk.top());
        }
    }
    return res;
}

// 贪心算法
int __max_profit(vector<int>& prices)
{
    int min = prices[0], res = 0;
    for (auto price : prices) {
        if (price < min) {
            min = price;
        } else {
            res = std::max(res, price - min);
        }
    }
    return res;
}


int main()
{
#ifdef LOCAL
    freopen("0121.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> prices(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> prices[i];
        }
        std::cout << max_profit(prices) << std::endl;
    }

    return 0;
}

