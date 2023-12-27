#include <iostream>
#include <unordered_map>
#include <vector>

using std::vector;

int longest_consecutive(vector<int>& nums)
{
    // m[x]: x 作为一个端点时，最长的连续区间的长度
    // 这里将 m[x] 更新为 std::max(l, r) + 1
    // 使得 m[x] 的意义统一了
    std::unordered_map<int, int> m;
    for (const auto x : nums) m[x] = 0;

    int res = 0;
    for (const auto x : nums) {
        if (m[x] == 0) {
            int l = m[x - 1];
            int r = m[x + 1];
            int d = l + 1 + r;
            m[x - l] = d;
            m[x + r] = d;
            m[x] = std::max(l, r) + 1;
            if (res < d) res = d;
        }
    }

    return res;
}

int _longest_consecutive(vector<int>& nums)
{
    // 用到的方法类似区间合并了
    // 遍历到该元素的时候
    // 如果 key 是某个连续区间的左右端点
    // 则 value 为该连续区间的长度
    // 否则 value 无意义
    std::unordered_map<int, int> m;
    int l = 0, r = 0;
    int len = 0, res = 0;

    for (const auto num : nums) {
        if (!m[num]) {
            l = m[num - 1];
            r = m[num + 1];
            len = l + r + 1;
            if (res < len) {
                res = len;
            }
            m[num] = len;
            m[num - l] = len;
            m[num + r] = len;
        }
    }

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0128.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        std::cout << longest_consecutive(nums) << std::endl;
    }

    return 0;
}
