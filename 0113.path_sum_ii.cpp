#include <iostream>
#include <vector>
#include "leetcode.h"

using std::vector;

vector<vector<int>> path_sum(TreeNode *root, int t)
{
    vector<vector<int>> res;
    vector<int> path;

    // path 用引用，因而需要手动 pop_back()
    auto backtracking = [&res, &path, t](auto&& self, TreeNode *root, int c) {
        if (root == nullptr) return ;

        c += root->val;
        path.push_back(root->val);
        if (c == t && root->left == root->right) {
            res.push_back(path);
            path.pop_back();
            c -= root->val;
            return ;
        }

        self(self, root->left, c);
        self(self, root->right, c);
        path.pop_back();
        c -= root->val;
    };

    backtracking(backtracking, root, 0);

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0113.in", "r", stdin);
#endif
    int n = 0, t = 0;
    while (std::cin >> n >> t) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        TreeNode *root = build_tree(nums);
        vector<vector<int>> res = path_sum(root, t);
        std::cout << res << std::endl;
    }

    return 0;
}
