#include <algorithm>
#include <iostream>
#include <array>
#include <vector>

using std::vector, std::array;

int longest_altrnating_subarray(vector<int>& nums, int t)
{
    int n = nums.size();
    int res = 0;

    // f[i][0]: nums[i] 结尾，且结尾为偶数的最大长度
    // f[i][1]: nums[i] 结尾，且结尾为奇数的最大长度
    //
    // 如果 nums[i] 为偶数，则 dp[i][0] = dp[i-1][1] + 1，dp[i][1] = 0
    array<int, 2> f{0, 0};

    for (int i = 0; i < n; ++i) {
        int x = nums[i];

        if (x > t) {
            f[0] = 0;
            f[1] = 0;
            continue;
        }

        // x&1       : 奇为0，偶为1
        // x & 1 ^ 1 : 奇为1，偶为0
        f[x & 1] = f[x & 1 ^ 1] + 1;
        f[x & 1 ^ 1] = 0;

        if (f[1] == 1) f[1] = 0;
        res = std::max(res, f[x & 1]);
    }

    return res;
}

// 分组循环
int _longest_altrnating_subarray(vector<int>& nums, int t)
{
    int n = nums.size();
    int res = 0;
    int l = 0;
    int r = 0;

    while (r < n) {
        if (nums[r] > t || nums[r] % 2) {
            r++;
            continue;
        }

        l = r;
        r++;
        while (r < n && nums[r] <= t && nums[r] % 2 != nums[r-1] % 2) {
            r++;
        }
        res = std::max(res, r - l);
    }

    return res;
}

int main () {
#ifdef LOCAL
    freopen("2760.in", "r", stdin);
#endif
    int n = 0, t = 0;
    while (std::cin >> n >> t) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        std::cout << longest_altrnating_subarray(nums, t) << std::endl;
    }

    return 0;
}
