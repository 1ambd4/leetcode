#include <iostream>
#include <vector>
#include <unordered_map>

#include "leetcode.h"

using std::vector, std::unordered_map;

int rob(TreeNode* root)
{
    unordered_map<TreeNode*, int> memo;

    auto traverse = [&memo] (auto&& self, TreeNode *root) -> int {
        if (root == nullptr) {
            return 0;
        }
        if (memo.find(root) != memo.end()) {
            return memo[root];
        }

        // 选择 root 节点的话，那么需要跳过 root 的孩子节点
        int res = root->val;
        if (root->left != nullptr) {
            res += (self(self, root->left->left) + self(self, root->left->right));
        }
        if (root->right != nullptr) {
            res += (self(self, root->right->left) + self(self, root->right->right));
        }

        // 不选 root 节点，则计算 root 的孩子节点即可
        res = std::max(res, self(self, root->left) + self(self, root->right));
        memo[root] = res;

        return res;
    };

    return traverse(traverse, root);
}

int main()
{
#ifdef LOCAL
    freopen("0337.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        std::vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }

        TreeNode *root = build_tree(nums);
        std::cout << rob(root) << std::endl;
    }

    return 0;
}
