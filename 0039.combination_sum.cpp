#include <algorithm>
#include <iostream>
#include <vector>

#include "leetcode.h"

using std::vector;

vector<vector<int>> combinatioin_sum(vector<int>& candidates, int t)
{
    vector<vector<int>> res;
    vector<int> path;
    int n = candidates.size();

    auto backtracking = [&candidates, &res, &path, n, t](auto&& self, int s, int k) -> void {
        if (s > t) return ;
        if (s == t) {
            res.push_back(path);
            return ;
        }

        // 这题元素可以重复，那么有两种思路
        // 一种是每次都是 [0, n-1] 的遍历所有的元素
        // 另一种思路则是下一次仍旧从当前元素开始遍历
        // 使用前者的一个缺点是可能出现重复的 path，比如 [2, 2, 3] 和 [2, 3, 2]
        // 那么就需要排序再去重，明显麻烦很多
        // 而方法二，因为不可能出现相同的路径
        // 那么自然不可能出现重复的结果
        for (int i = k; i < n; ++i) {
            path.push_back(candidates[i]);
            s += candidates[i];
            self(self, s, i);
            s -= candidates[i];
            path.pop_back();
        }
    };

    backtracking(backtracking, 0, 0);

    return res;
}

vector<vector<int>> _combinatioin_sum(vector<int>& candidates, int t)
{
    vector<vector<int>> res;
    vector<int> path;
    int n = candidates.size();

    // 用 path 的话，如何去重呢？
    auto backtracking = [&candidates, &res, &path, n, t](auto&& self, int s) -> void {
        if (s > t) return ;
        if (s == t) {
            // 不能直接修改原来的数组
            // std::sort(path.begin(), path.end());

            // 排序后去重
            vector<int> temp(path.begin(), path.end());
            std::sort(temp.begin(), temp.end());
            if (std::find(res.begin(), res.end(), temp) == res.end()) {
                res.push_back(temp);
            }
            return ;
        }

        for (int i = 0; i < n; ++i) {
            path.push_back(candidates[i]);
            s += candidates[i];
            self(self, s);
            s -= candidates[i];
            path.pop_back();
        }
    };

    backtracking(backtracking, 0);

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0039.in", "r", stdin);
#endif
    int n = 0, t = 0;
    while (std::cin >> n >> t) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        vector<vector<int>> res = combinatioin_sum(nums, t);
        std::cout << res << std::endl;
    }

    return 0;
}
