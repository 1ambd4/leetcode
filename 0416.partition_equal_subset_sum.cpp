#include <iostream>
#include <vector>

using std::vector;

// 这题题目太抽象了，换个说法会更好理解一些
// 记这些数字总和为 s，记 w = s / 2
// 如果 s 是奇数，那么必然不能平分
// 如果 s 是偶数，那么在不超过 w 的情况下，数字和最大是多少
// 如果上面求出的最大和是 w 的话，则表示可以平分
//
// 就是背包问题啊，给了这么一堆数字，背包体积为 w
// 问最多能装多少
bool can_partition(vector<int>& nums)
{
    int n = nums.size();

    int sum = 0;
    for (const auto num : nums) sum += num;
    if (sum % 2 != 0) return false;

    int w = sum / 2;
    vector<vector<int>> f(n+1, vector<int>(w+1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= w; ++j) {
            if (j - nums[i-1] < 0) {
                f[i][j] = f[i-1][j];
            } else {
                f[i][j] = std::max(f[i-1][j-nums[i-1]] + nums[i-1], f[i-1][j]);
            }
        }
    }

    return f[n][w] == w;
}

int main () {
#ifdef LOCAL
    freopen("0416.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        std::cout << can_partition(nums) << std::endl;
    }

    return 0;
}
