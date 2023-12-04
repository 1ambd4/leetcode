#include <iostream>
#include <vector>

#include "leetcode.h"

using namespace std;

TreeNode* bst_to_gst(TreeNode* root)
{
    int sum = 0;
    auto traverse = [&sum](auto&& self, TreeNode *root) -> void {
        if (root == nullptr || root->val == -1) {
            return ;
        }

        self(self, root->right);
        sum += root->val;
        root->val = sum;
        self(self, root->left);
    };

    traverse(traverse, root);

    return root;
}

int main () {
#ifdef LOCAL
    freopen("1038.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        std::vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        TreeNode *bst = build_tree(nums);
        traversal(bst);
        TreeNode *gst = bst_to_gst(bst);
        traversal(gst);
    }
    return 0;
}
