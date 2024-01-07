#include <iostream>
#include <vector>
#include <stack>

#include "leetcode.h"

using std::vector, std::stack;

vector<int> inorder_traversal(TreeNode *root)
{
    vector<int> res;
    stack<TreeNode*> stk;

    while (root != nullptr || !stk.empty()) {
        while (root != nullptr) {
            stk.push(root);
            root = root->left;
        }
        root = stk.top();
        stk.pop();
        res.push_back(root->val);
        root = root->right;
    }

    return res;
}

vector<int> _inorder_traversal(TreeNode *root)
{
    vector<int> res;

    auto traversal = [&res](auto&& self, TreeNode *cur) -> void {
        if (cur == nullptr) return ;

        self(self, cur->left);
        res.push_back(cur->val);
        self(self, cur->right);
    };

    traversal(traversal, root);

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0094.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        TreeNode *head = build_tree(nums);
        vector<int> res = inorder_traversal(head);
        std::cout << res << std::endl;
    }

    return 0;
}
