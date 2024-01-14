#include <iostream>
#include <vector>

using std::vector;

// 和 39.combination-sum 一样啊
// 都是重复元素之和
// 不同的是，这里递归会 TLE
// 因为 t 都到 9864 了
int coin_change(vector<int>& coins, int t)
{
    if (t == 0) return 0;

    int res = t + 1;
    // 用前 k 个元素构建和为 s 的个数为 c
    auto recursive = [&coins, &res, t](auto&& self, int s, int k, int c) {
        if (s > t) return ;
        if (s == t) {
            res = std::min(res, c);
            return ;
        }

        for (int i = k; i < coins.size(); ++i) {
            s += coins[i];
            ++c;
            self(self, s, i, c);
            --c;
            s -= coins[i];
        }
    };

    recursive(recursive, 0, 0, 0);

    return res == t + 1 ? -1 : res;
}

int _coin_change(vector<int>& coins, int t)
{
    if (t == 0) return 0;

    vector<int> f(t + 1, t + 1);
    f[0] = 0;

    // 这就直接越界了啊
    // 1 1
    // 10
    // for (const auto coin : coins) {
    //     f[coin] = 1;
    // }

    for (int i = 1; i <= t; ++i) {
        for (const auto coin : coins) {
            if (i - coin < 0) continue;
            f[i] = std::min(f[i], f[i-coin] + 1);
        }
    }

    return f[t] == t + 1 ? -1 : f[t];
}

int main () {
#ifdef LOCAL
    freopen("0322.in", "r", stdin);
#endif
    int n = 0, t = 0;
    while (std::cin >> n >> t) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        std::cout << coin_change(nums, t) << std::endl;
    }

    return 0;
}
