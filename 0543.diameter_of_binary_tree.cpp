#include <iostream>
#include <vector>

#include "leetcode.h"

using std::vector;

int diameter_of_binary_tree(TreeNode *root)
{
    int res = 0;

    // DFS 的计算某一个方向上的节点数
    auto traversal = [&res](auto&& self, TreeNode *root) -> int {
        if (root == nullptr) {
            return 0;
        }

        // 那么，实际上要求的直径
        // 就是 left + right
        int left = self(self, root->left);
        int right = self(self, root->right);
        res = std::max(res, left + right);

        return 1 + std::max(left, right);
    };

    traversal(traversal, root);

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0543.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        TreeNode *root = build_tree(nums);
        std::cout << diameter_of_binary_tree(root) << std::endl;
    }

    return 0;
}
