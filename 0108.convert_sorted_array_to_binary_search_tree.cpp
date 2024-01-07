#include <iostream>
#include <vector>

#include "leetcode.h"

using std::vector;

// 已经升序了，如果我常用的建二叉搜索树的方式
// 大概就变成单链表了
// 这里为了平衡，直接分割区间
// 只要区间分得均匀，那么就能够保证最后的二叉树是平衡的
TreeNode* sorted_array_to_bst(vector<int>& nums)
{
    int n = nums.size();

    auto build = [&nums](auto&& self, int left, int right) -> TreeNode* {
        if (left > right) return nullptr;

        int mid = left + (right - left) / 2;
        TreeNode *root = new TreeNode(nums[mid]);
        root->left = self(self, left, mid - 1);
        root->right = self(self, mid + 1, right);

        return root;
    };

    return build(build, 0, n - 1);
}

int main () {
#ifdef LOCAL
    freopen("0108.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        TreeNode *root = sorted_array_to_bst(nums);
        traversal(root);
    }

    return 0;
}
