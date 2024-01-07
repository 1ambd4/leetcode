#include <iostream>
#include <queue>
#include <vector>

#include "leetcode.h"

using std::vector;

vector<vector<int>> level_order(TreeNode *root)
{
    vector<vector<int>> res;

    if (root == nullptr) return res;

    std::queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int n = q.size();
        res.push_back({});
        for (int i = 0; i < n; ++i) {
            TreeNode *cur = q.front();
            q.pop();
            res.back().push_back(cur->val);
            if (cur->left != nullptr) q.push(cur->left);
            if (cur->right != nullptr) q.push(cur->right);
        }
    }

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0102.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        TreeNode *root = build_tree(nums);
        vector<vector<int>> res = level_order(root);
        std::cout << res << std::endl;
    }

    return 0;
}
