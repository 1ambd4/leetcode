#include <iostream>
#include <numeric>
#include <vector>

using std::vector;

// 那么倍增能不能求呢？
// 可以的，控制一下窗口大小不超过 n 即可

// 环形数组最大子数组和，但规定了每个数字只能出现一次
// 那么，可能有两种情况
// 一：最大子数组不跨越边界，那么此时当作普通的最大子数组和即可
// 二：最大子数组跨越边界，这种情况不好直接求
//     我最先想到倍增，但不行，因为需要考虑数字重复的情况
//     实际上，最大子数组跨越边界的情况下
//     两段子数组之间夹着的一整段构成了最小子数组和
//     那么，这种情况下的最大子数组和用总和减去最小子数组和即可
//
// 最后需要特判一下全为负数的情况
// 因为这时候总和等于最小子数组和，相减变成 0 了
// 显然不是我们想要的答案
int max_subarray_circular(vector<int>& nums)
{
    int n = nums.size();

    int mm = nums[0];
    int mn = nums[0];
    int sum = std::accumulate(nums.begin(), nums.end(), 0);

    vector<vector<int>> dp(n, vector<int>(2, 0));
    dp[0][0] = nums[0];
    dp[0][1] = nums[0];
    for (int i = 1; i < n; ++i) {
        dp[i][0] = std::max(dp[i-1][0] + nums[i], nums[i]);
        mm = std::max(mm, dp[i][0]);

        dp[i][1] = std::min(dp[i-1][1] + nums[i], nums[i]);
        mn = std::min(mn, dp[i][1]);
    }

    return mn == sum ? mm : std::max(mm, sum - mn);
}

int main()
{
#ifdef LOCAL
    freopen("0918.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        std::cout << max_subarray_circular(nums) << std::endl;
    }
}
