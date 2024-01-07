#include <iostream>
#include <limits>
#include <vector>

#include "leetcode.h"

bool is_valid_bst(TreeNode *root)
{
    bool res = true;
    if (root == nullptr) return true;

    // 怪了，力扣 pre 没用引用就报错了
    // 但本地答案是正确的，啥原因啊？
    // 我能大概猜到是 19 行递归进去的时候，没更新 pre？
    // 但为啥前两个例子都能过？本地测试也能过？
    auto valid = [&res](auto&& self, TreeNode *cur, long& pre) -> void {
        if (cur == nullptr) return ;

        self(self, cur->left, pre);
        if (cur->val <= pre) res = false;
        pre = cur->val;
        self(self, cur->right, pre);
    };

    long pre = std::numeric_limits<long>::min();
    valid(valid, root, pre);
    return res;
}

using std::vector;

int main () {
#ifdef LOCAL
    freopen("0098.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        TreeNode *root = build_bst(nums);
        std::cout << is_valid_bst(root) << std::endl;
    }

    return 0;
}
