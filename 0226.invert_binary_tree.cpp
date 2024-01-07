#include <iostream>
#include <vector>

#include "leetcode.h"

using std::vector;

TreeNode* invert_tree(TreeNode *root)
{
    if (root == nullptr) return root;

    std::swap(root->left, root->right);
    invert_tree(root->left);
    invert_tree(root->right);

    return root;
}

TreeNode* _invert_tree(TreeNode *root)
{
    if (root == nullptr) return root;

    auto invert = [](auto&& self, TreeNode *root) {
        if (root == nullptr) return ;
        std::swap(root->left, root->right);
        self(self, root->left);
        self(self, root->right);
    };

    invert(invert, root);

    return root;
}

int main () {
#ifdef LOCAL
    freopen("0226.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        TreeNode *root = build_tree(nums);
        TreeNode *res = invert_tree(root);
        traversal(root);
    }

    return 0;
}
