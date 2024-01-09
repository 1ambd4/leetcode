#include <iostream>
#include <vector>

#include "leetcode.h"

using std::vector;

vector<vector<int>> subset(vector<int>& nums)
{
    int n = nums.size();
    vector<vector<int>> res;
    vector<int> path;

    if (n == 0) return res;

    auto backtracking = [&nums, &res, n](auto&& self, vector<int>& path, int t) -> void {
        res.push_back(path);

        for (int i = t; i < n; ++i) {
            path.push_back(nums[i]);
            self(self, path, i + 1);
            path.pop_back();
        }
    };

    backtracking(backtracking, path, 0);

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0078.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        vector<vector<int>> res = subset(nums);
        std::cout << res << std::endl;
    }

    return 0;
}
