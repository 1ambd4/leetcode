#include <iostream>
#include <vector>

#include "leetcode.h"

// 相信 flatten 可以将以 root 为根的二叉树拍平
// 那么，咱先把左右子树拍平喽
// 然后就考虑当前如何把左右子树按照题给要求挂到根的右子树上就好
void flatten(TreeNode *root)
{
    if (root == nullptr) return ;

    TreeNode *left = root->left;
    TreeNode *right = root->right;

    flatten(root->left);
    flatten(root->right);

    root->left = nullptr;

    if (left != nullptr) {
        root->right = left;
        TreeNode *tmp = left;
        while (tmp != nullptr && tmp->right != nullptr) {
            tmp = tmp->right;
        }
        tmp->right = right;
    } else {
        root->right = right;
    }
}

using std::vector;

int main () {
#ifdef LOCAL
    freopen("0114.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        TreeNode *root = build_tree(nums);
        flatten(root);
        traversal(root);
    }

    return 0;
}
