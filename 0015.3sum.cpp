#include <algorithm>
#include <cstdio>
#include <functional>
#include <iostream>
#include <vector>

using std::vector;

// 找nums[0] + nums[1] + nums[2] == 0 的所有三元组
vector<vector<int>> tree_sum(vector<int>& nums)
{
    int n = nums.size();
    std::sort(nums.begin(), nums.end(), std::less<int>());

    auto bs = [&nums](int v) -> int {
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            int m = (l + r + 1) >> 1;
            if (nums[m] <= v) l = m;
            else r = m - 1;
        }
        if (nums[l] != v) return -1;
        return l;
    };

    vector<vector<int>> res;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int m = bs(0 - nums[i] - nums[j]);
            if (m != -1 && m > j) {
                res.push_back(vector<int>{nums[i], nums[j], nums[m]});
            }
            while (j + 1 < n && nums[j+1] == nums[j]) {
                ++j;
            }
        }
        while (i + 1 < n && nums[i+1] == nums[i]) {
            ++i;
        }
    }

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0015.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        vector<vector<int>> res = tree_sum(nums);
        if (res.size() != 0) {
            for (const auto& es : res) {
                std::cout << "[";
                for (int i = 0; i < 3; ++i) {
                    printf(",%d" + !i, es[i]);
                }
                std::cout << "]" << std::endl;
            }
        } else {
            std::cout << "[]" << std::endl;
        }
    }

    return 0;
}
