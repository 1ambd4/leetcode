#include <iostream>
#include <vector>

#include "leetcode.h"

using std::vector;

// 鸽笼原理，原地计数
// 如果某个数字出现了，就把其对应的位置上的数字变为负数
// 这样并不会影响到原来在该位置上的数字，因为题给都是正数
// 想要获取到原数字，直接取绝对值即可
vector<int> find_disappeared_numbers(vector<int>& nums)
{
    int n = nums.size();

    for (auto num : nums) {
        nums[std::abs(num)-1] = -std::abs(nums[std::abs(num)-1]);
    }

    vector<int> res;
    for (int i = 0; i < n; ++i) {
        if (nums[i] > 0) {
            res.push_back(i+1);
        }
    }
    return res;
}

// 蠢比计数
vector<int> _find_disappeared_numbers(vector<int>& nums)
{
    int n = nums.size();
    vector<int> cnt(n+1, 0);
    for (auto num : nums) {
        cnt[num]++;
    }

    vector<int> res;
    for (int i = 1; i <= n; ++i) {
        if (cnt[i] == 0) {
            res.push_back(i);
        }
    }
    return res;
}

int main () {
#ifdef LOCAL
    freopen("0448.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        vector<int> res = find_disappeared_numbers(nums);
        std::cout << res << std::endl;
    }

    return 0;
}
