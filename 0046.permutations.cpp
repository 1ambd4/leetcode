#include <algorithm>
#include <iostream>
#include <vector>

#include "leetcode.h"

using std::vector;

vector<vector<int>> permute(vector<int>& nums)
{
    int n = nums.size();
    vector<vector<int>> res;
    vector<int> vis(n, 0);
    vector<int> path;

    if (n == 0) return res;

    auto backtracking = [&res, &vis, &nums, n](auto&& self, vector<int>& path) -> void {
        if (path.size() == n) {
            res.push_back(path);
            return ;
        }

        for (int i = 0; i < n; ++i) {
            if (vis[i] == 1) continue;
            vis[i] = 1;
            path.push_back(nums[i]);
            self(self, path);
            path.pop_back();
            vis[i] = 0;
        }
    };

    backtracking(backtracking, path);
    return res;
}

int main () {
#ifdef LOCAL
    freopen("0046.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        vector<vector<int>> res = permute(nums);
        std::cout << res << std::endl;
    }

    return 0;
}
