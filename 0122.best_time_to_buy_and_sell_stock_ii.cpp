#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

// dp[i][j]: 在第 i 天进行 j 交易操作后的最大收益
// 其中，j = 0 表示卖出，j = 1 表示买入
int max_profit(vector<int>& prices)
{
    int n = prices.size();

    vector<vector<int>> dp(n, vector<int>(2, 0));
    dp[0][0] = 0;
    dp[0][1] = prices[0];

    for (int i = 1; i < n; ++i) {
        dp[i][0] = std::max(dp[i-1][0], prices[i] - dp[i-1][1]);
        dp[i][1] = std::min(dp[i-1][1], prices[i] - dp[i-1][0]);
    }

    return dp[n-1][0];
}

// 贪心，只要股价高于昨天就卖出（这里暗含了在昨天买入的过程）
int _max_profit(vector<int>& prices)
{
    int res = 0;

    for (int i = 1, n  = prices.size(); i < n; ++i) {
        if (prices[i] > prices[i-1]) {
            res += prices[i] - prices[i-1];
        }
    }

    return res;
}

int main()
{
#ifdef LOCAL
    freopen("0122.in", "r", stdin);
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

