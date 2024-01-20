#include <iostream>
#include <limits>
#include <vector>

#include "leetcode.h"

using std::vector;

// 对于最大路径和，可能有三种情况
// 1.根节点 + 左子树最大路径和 + 右子树最大路径和
// 2.根节点 + 左子树最大路径和
// 3.根节点 + 右子树最大路径和
//
// 因为需要知悉左右子树的情况的，所以应该是后序遍历
int max_path_sum(TreeNode* root)
{
    int res = std::numeric_limits<int>::min();

    // dfs：计算以 root 为根节点的子树中，路径和的最大值
    auto dfs = [&res](auto&& self, TreeNode* root) {
        if (root == nullptr) return 0;
        int left = self(self, root->left);   // 左子树
        int right = self(self, root->right); // 右子树
        res = std::max(res, left + right + root->val); // 根节点 + 左右子树
        return std::max(std::max(left, right) + root->val, 0);
    };

    dfs(dfs, root);
    return res;
}

int main () {
#ifdef LOCAL
    freopen("0124.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        TreeNode *root = build_tree(nums);
        std::cout << max_path_sum(root) << std::endl;
    }

    return 0;
}
