#include <iostream>
#include <vector>

#include "leetcode.h"

bool is_symmetric(TreeNode *root)
{
    if (root == nullptr) return true;

    auto traversal = [](auto&& self, TreeNode *left, TreeNode *right) -> bool {
        if (left == right) return true;
        if (left == nullptr || right == nullptr) return false;
        if (left->val != right->val) return false;

        return self(self, left->left, right->right) && self(self, left->right, right->left);
    };

    return traversal(traversal, root->left, root->right);
}

using std::vector;

int main () {
#ifdef LOCAL
    freopen("0101.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        TreeNode *root = build_tree(nums);
        std::cout << is_symmetric(root) << std::endl;
    }

    return 0;
}
