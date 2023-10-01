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
    stack<int> s;
    int res = 0;
    for (auto e : prices) {
        if (s.empty()) {
            s.push(e);
            continue;
        }

        if (e <= s.top()) {
            s.push(e);
        } else {
            res = std::max(res, e - s.top());
        }
    }
    return res;
}

int __max_profit(vector<int>& prices)
{
    int min = prices[0], res = 0;
    for (auto e : prices) {
        if (e < min) {
            min = e;
        } else {
            res = std::max(res, e - min);
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

