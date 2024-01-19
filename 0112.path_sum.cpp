#include <iostream>
#include <vector>
#include "leetcode.h"

using std::vector;

bool has_path(TreeNode* root, int t)
{
    bool res = false;

    auto backtracking = [&res, t](auto&& self, TreeNode* root, int c) {
        if (root == nullptr) return ;
        // 因为 root->val 可能有负值，所有不能用 c > t 来剪枝
        // if (c > t) return ;

        c += root->val;
        if (c == t && root->left == nullptr && root->right == nullptr) {
            res = true;
            return ;
        }

        self(self, root->left, c);
        self(self, root->right, c);
    };

    backtracking(backtracking, root, 0);

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0112.in", "r", stdin);
#endif
    int n = 0, t = 0;
    while (std::cin >> n >> t) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        TreeNode *root = build_tree(nums);
        std::cout << has_path(root, t) << std::endl;
    }

    return 0;
}
