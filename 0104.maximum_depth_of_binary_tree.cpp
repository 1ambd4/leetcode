#include <iostream>
#include <vector>
#include <queue>

#include "leetcode.h"

using std::vector, std::queue;

int _max_depth(TreeNode *root)
{
    if (root == nullptr) return 0;

    queue<TreeNode*> q;
    q.push(root);

    int res = 0;
    while (!q.empty()) {
        ++res;
        int n = q.size();
        for (int i = 0; i < n; ++i) {
            TreeNode *cur = q.front();
            q.pop();

            if (cur->left != nullptr) q.push(cur->left);
            if (cur->right != nullptr) q.push(cur->right);
        }
    }

    return res;
}

int max_depth(TreeNode *root)
{
    if (root == nullptr) return 0;

    int left = max_depth(root->left);
    int right = max_depth(root->right);

    return std::max(left, right) + 1;
}

int main () {
#ifdef LOCAL
    freopen("0104.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        TreeNode *head = build_tree(nums);
        std::cout << max_depth(head) << std::endl;
    }

    return 0;
}
