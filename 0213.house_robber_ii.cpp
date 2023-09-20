#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>

using std::vector;

int rob(vector<int>& nums)
{
    int n = nums.size();
    int res = 0;
    if (n == 1) return nums[0];
    if (n == 2) return std::max(nums[0], nums[1]);

    vector<int> dp(n, 0);

    dp[0] = nums[0];
    dp[1] = std::max(nums[0], nums[1]);
    for (int i = 2; i < n - 1; ++i) {
        dp[i] = std::max(dp[i-1], dp[i-2] + nums[i]);
    }
    res = std::max(res, dp[n-2]);

    dp[0] = 0;
    dp[1] = nums[1];
    dp[2] = std::max(nums[1], nums[2]);
    for (int i = 3; i < n; ++i) {
        dp[i] = std::max(dp[i-1], dp[i-2] + nums[i]);
    }
    res = std::max(res, dp[n-1]);

    return res;
}

int main()
{
#ifdef LOCAL
    freopen("0213.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        std::vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }

        int res = rob(nums);
        std::cout << res << std::endl;
    }

    return 0;
}
