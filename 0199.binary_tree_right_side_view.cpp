#include <iostream>
#include <queue>
#include <vector>

#include "leetcode.h"

using std::vector;

vector<int> right_side_view(TreeNode *root)
{
    vector<int> res;
    if (root == nullptr) return res;

    std::queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int n = q.size();
        for (int i = 0; i < n; ++i) {
            TreeNode *cur = q.front();
            q.pop();

            // 虽然可以通过把 cur 移到 for 外面的方式
            // 直接在 for 循环结束后拿到最后一个节点
            // 但，感觉写出来没有现在好看捏
            if (i == n - 1) {
                res.push_back(cur->val);
            }

            if (cur->left != nullptr) q.push(cur->left);
            if (cur->right != nullptr) q.push(cur->right);

        }
    }

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0199.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        TreeNode *root = build_tree(nums);
        vector<int> res = right_side_view(root);
        std::cout << res << std::endl;
    }

    return 0;
}
