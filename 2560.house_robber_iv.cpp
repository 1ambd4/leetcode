#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>

using std::vector;

// 参照 875.爱吃香蕉的珂珂
// 即最小化最大值（二分左边界
int min_capability(vector<int>& nums, int k)
{
    int n = nums.size();
    int left = *std::min_element(nums.begin(), nums.end());
    int right = *std::max_element(nums.begin(), nums.end());

    auto check = [&nums, n, k](int v) -> bool {
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            if (nums[i] <= v) {
                ++cnt;
                ++i;
            }
        }
        return cnt >= k;
    };

    while (left < right) {
        int mid = (left + right) >> 1;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return left;
}

// dp 很快啊，我是值 TLE
int _min_capability(vector<int>& nums, int k)
{
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(k, std::numeric_limits<int>::max()));

    // 这里需要注意的是 base case 的合法性
    // 习惯性的就初始化 dp[0..n][0] 和 dp[0][0..k] 了
    // 但其实 dp[0][1..k] 都是 invalid case，直接用初始化的 infinite 就好
    // for (int i = 0; i < n; ++i) dp[i][0] = 0;
    // for (int j = 1; j < k; ++j) dp[0][j] = nums[0];
    // for (int j = 2; j < k; ++j) dp[1][j] = std::min(nums[0], nums[1]);
    for (int i = 0; i < n; ++i) {
        dp[i][0] = *std::min_element(nums.begin(), nums.begin() + i + 1);
    }

    for (int i = 2; i < n; ++i) {
        for (int j = 1; j < k; ++j) {
            if (j > (i + 2) / 2) continue;
            dp[i][j] = std::min(dp[i-1][j], std::max(dp[i-2][j-1], nums[i]));
        }
    }

    return dp[n-1][k-1];
}

int main()
{
#ifdef LOCAL
    freopen("2560.in", "r", stdin);
#endif
    int n = 0, k = 0;
    while (std::cin >> n >> k) {
        std::vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        std::cout << min_capability(nums, k) << std::endl;
    }
    return 0;
}
