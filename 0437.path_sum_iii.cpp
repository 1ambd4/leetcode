#include <iostream>
#include <unordered_map>
#include <vector>
#include "leetcode.h"

using std::vector;

// 这题麻烦在于多起点，即路径起点不一定是根节点
// 那么朴素的做法是搜索以每个节点为根的所有路径
// 并对路径总和为 target 的路径进行累积统计
// 使用 dfs1 来搜索所有节点，复杂度为 O(n)
// 在 dfs1 中，对于每个当前节点，使用 dfs2 搜索以其为根的所有路径
// 同时累加路径和为 target 的情况，复杂度为 O(n)
// dfs2 就变成了 0112.path_sum 差不多的问题了
// 不同的是，0112 只问有没有，故而 dfs2 里找到了就可以 return
// 但这里要求的是路径条数，且存在负数，所以需要一直递归到叶节点
// 不能提前 return
int path_sum(TreeNode* root, int t)
{
    int ans = 0;

    auto dfs2 = [&ans, t](auto&& self, TreeNode* root, long long c) {
        if (root == nullptr) return ;

        // if (c == t) ans++;
        //
        // if (root->left != nullptr) {
        //     c += root->left->val;
        //     self(self, root->left, c);
        //     c -= root->left->val;
        // }
        //
        // if (root->right != nullptr) {
        //     c += root->right->val;
        //     self(self, root->right, c);
        //     c -= root->right->val;
        // }

        // if (c == t) ans++;
        //
        // if (root->left != nullptr) {
        //     self(self, root->left, c + root->left->val);
        // }
        // if (root->right != nullptr) {
        //     self(self, root->right, c + root->right->val);
        // }

        c += root->val;
        if (c == t) ans++;

        self(self, root->left, c);
        self(self, root->right, c);
    };

    // 遍历整棵树
    // 求解以当前节点为根的树，存在多少条路径，其路径和为 target
    auto dfs1 = [&dfs2](auto&& self, TreeNode* root) {
        if (root == nullptr) return ;
        // dfs2(dfs2, root, root->val);
        dfs2(dfs2, root, 0);
        self(self, root->left);
        self(self, root->right);
    };

    dfs1(dfs1, root);
    return ans;
}

// https://leetcode.cn/problems/path-sum-iii/solutions/596361/dui-qian-zhui-he-jie-fa-de-yi-dian-jie-s-dey6
// 将两个节点间的路径和转换为两个节点的路径差
int _path_sum(TreeNode* root, int t)
{
    // 保存前缀树
    std::unordered_map<long long, int> m;
    m[0] = 1;  // 前缀为 0 的路径至少一条

    // 到达节点 root 时，当前路径和为 c，路径和为 t 的有多少条
    // 测试数据里前缀和会爆 int，所以得用 long long 存
    auto dfs = [&m, t](auto&& self, TreeNode* root, long long c) -> int {
        if (root == nullptr) return 0;

        int ans = 0;

        c += root->val;     // 得到当前前缀和
        ans += m[c - t];    // 查询表里当前前缀和等值的有多少个
        m[c] += 1;          // 当前前缀和添加到表里
        ans += self(self, root->left, c);   // 左右子树
        ans += self(self, root->right, c);
        m[c] -= 1;          // 回溯

        return ans;
    };

    return dfs(dfs, root, 0);
}

// 错误示范，WA 警告
int __path_sum(TreeNode* root, int t)
{
    int res = 0;
    // root 中找路径和为 t 的
    auto backtracking = [&res, t](auto&& self, TreeNode *root, int& c) -> void {
        if (root == nullptr) return ;
        // 有负数，所以不要想着剪枝来优化
        // if (c > t) return ;

        if (c == t) {
            res++;
            // return ;
        }

        // 对于当前节点来说，共有四种可能的状态转移
        // 因为有左右两个子树，且每个节点可以有选择或者不选两种情况
        // 故而 2 × 2 - 4

        // 思路错在保存的状态信息太少了
        // 仅仅一个 c，首先不说别的
        // 你知道你这个 c 是不是连续路径上的路径和么？
        self(self, root->left, c);
        self(self, root->right, c);

        c += root->val;
        self(self, root->left, c);
        self(self, root->right, c);
        c -= root->val;
    };

    int c = 0;
    backtracking(backtracking, root, c);

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0437.in", "r", stdin);
#endif
    int n = 0, t = 0;
    while (std::cin >> n >> t) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        TreeNode *tree = build_tree(nums);
        std::cout << path_sum(tree, t) << std::endl;
    }

    return 0;
}
