#include <iostream>
#include <vector>

#include "leetcode.h"

using std::vector;

int kth_smallest(TreeNode *root, int k)
{
    int res = 0;

    auto traversal = [&res, &k](auto&& self, TreeNode *root) -> void {
        if (root == nullptr) return ;

        self(self, root->left);
        --k;
        if (k == 0) res = root->val;
        self(self, root->right);
    };

    traversal(traversal, root);

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0230.in", "r", stdin);
#endif
    int n = 0, k = 0;
    while (std::cin >> n >> k) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        TreeNode *root = build_tree(nums);
        std::cout << kth_smallest(root, k) << std::endl;
    }

    return 0;
}
