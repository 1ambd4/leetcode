#include <iostream>
#include <vector>

// 背包问题
int num_rolls_to_target(int n, int k, int t)
{
    constexpr int MOD = 1e9l + 7;
    std::vector<std::vector<int>> f(n+1, std::vector<int>(t+1, 0));
    f[0][0] = 1;

    // f[i][j]: 用前 i 个骰子，扔出 j 的方案数
    // 以此枚举：物品组 -> 容量 -> 决策
    // 转移方程：f[i][j] = ∑f[i-1][j-r] (for r in 1..=k)
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= t; ++j) {
            for (int r = 1; r <= k; ++r) {
                if (j >= r) {
                    f[i][j] = (f[i][j] + f[i-1][j-r]) % MOD;
                }
            }
        }
    }

    return f[n][t];
}

int main()
{
#ifdef LOCAL
    freopen("1155.in", "r", stdin);
#endif
    int n = 0, k = 0, t = 0;
    while (std::cin >> n >> k >> t) {
        std::cout << num_rolls_to_target(n, k, t) << std::endl;
    }
    return 0;
}
