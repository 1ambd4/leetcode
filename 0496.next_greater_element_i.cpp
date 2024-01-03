#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>

#include "leetcode.h"

using std::vector, std::stack, std::unordered_map;

// 单调栈
vector<int> next_greater_element(vector<int>& nums1, vector<int>& nums2)
{
    int m = nums1.size();
    int n = nums2.size();
    unordered_map<int, int> mp;

    stack<int> stk;
    for (int i = n - 1; i >= 0; --i) {
        while (!stk.empty() && stk.top() <= nums2[i]) {
            stk.pop();
        }
        mp[nums2[i]] = stk.empty() ? -1 : stk.top();
        stk.emplace(nums2[i]);
    }

    vector<int> res;
    res.reserve(m);

    for (const auto num : nums1) {
        res.push_back(mp[num]);
    }

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0496.in", "r", stdin);
#endif
    int m = 0, n = 0;
    while (std::cin >> m >> n) {
        vector<int> nums1(m, 0);
        vector<int> nums2(n, 0);
        for (int i = 0; i < m; ++i) {
            std::cin >> nums1[i];
        }
        for (int i = 0; i < n; ++i) {
            std::cin >> nums2[i];
        }
        std::cout << next_greater_element(nums1, nums2) << std::endl;
    }

    return 0;
}
