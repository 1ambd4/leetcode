#include <iostream>
#include <vector>

#include "leetcode.h"

using std::vector;

vector<int> two_sum(vector<int>& nums, int target)
{
    // [l, r] 二分查找 t
    auto search = [&nums](int l, int r, int t) -> int {
        while (l < r) {
            int m = (l + r + 1) >> 1;
            if (nums[m] <= t) l = m;
            else r = m - 1;
        }
        if (nums[l] != t) return -1;
        return l;
    };

    int n = nums.size();
    for (int i = 0; i < n; ++i) {
        int t = target - nums[i];
        int j = search(i+1, n-1, t);
        if (j != -1) {
            return {i + 1, j + 1};
        }
    }

    return { };
}

int main () {
#ifdef LOCAL
    freopen("0167.in", "r", stdin);
#endif
    int n = 0, t = 0;
    while (std::cin >> n >> t) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        std::cout << two_sum(nums, t) << std::endl;
    }

    return 0;
}
