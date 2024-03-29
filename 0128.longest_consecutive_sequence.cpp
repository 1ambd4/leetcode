#include <iostream>
#include <unordered_map>
#include <vector>

using std::vector;

int longest_consecutive(vector<int>& nums) {
    // m[i]: 表示到第 i 个数字时候的最长连续序列
    std::unordered_map<int, int> m;
    for (const auto x : nums) m[x] = 0;

    int res = 0;
    for (const auto x : nums) {
        if (m[x] == 0) {
            int l = m[x-1];
            int r = m[x+1];
            int d = l + 1 + r;
            m[x-l] = d;
            m[x+r] = d;
            // m[x] = std::max(l, r) + 1;
            // 我感觉还是写成 m[x] = d 更好一些
            // 首先，直接 m[x] = std::max(l, r) + 1，感觉就是错的吧
            // 因为这时候考虑的是 x 作为连续区间的某个端点
            // 但 x 完全可以作为连续区间的中间
            // 再看 m[x] = d 的写法
            // 如果 x 是某个区间的端点，必然有 l == 0 或者 r == 0
            // 这时候 m[x] = d = l + 1 + r
            // 是涵盖了 x 作为连续区间端点的情况的
            // 当然，如果把 m[x] 定义为以 x 为端点的最长连续区间，那没问题
            m[x] = d;
            if (res < d) res = d;
        }
    }

    return res;
}

int _longest_consecutive(vector<int>& nums)
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

int __longest_consecutive(vector<int>& nums)
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
