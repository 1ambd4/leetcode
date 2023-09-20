#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>

using std::vector;

int rob(vector<int>& nums)
{
    int n = nums.size();
    if (n == 0) return nums[0];

    vector<int> dp(n, 0);

    dp[0] = nums[0];
    dp[1] = std::max(nums[1], nums[0]);

    for (int i = 2; i < n; ++i) {
        dp[i] = std::max(dp[i-1], dp[i-2] + nums[i]);
    }

    return dp[n-1];
}

int main()
{
#ifdef LOCAL
    freopen("0198.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        std::vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        std::cout << rob(nums) << std::endl;
    }
    return 0;
}
