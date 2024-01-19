#include <iostream>
#include <vector>
#include "leetcode.h"

using std::vector;

// 更好理解的版本，把是否在某棵子树上拆分出来
bool find(TreeNode* root, TreeNode* t)
{
    if (root == nullptr) return false;
    if (root == t) return true;

    return find(root->left, t) || find(root->right, t);
}

// 递归函数的定义，在树 root 中搜索节点 p 和节点 q 的lca
// 容易想到，如果节点 p 和节点 q 分属两边，那么 lca 就是树根
// 否则，就需要在左右两侧递归查找
// 这时候发现其实就是子问题，递归求解即可
TreeNode* lowest_common_ancestor(TreeNode* root, TreeNode* p, TreeNode* q)
{
    if (root == nullptr) return nullptr;
    if (p == root || q == root) return root;

    // 如果 p、q 在左子树，那么公共祖先要在左子树查找
    if (find(root->left, p) && find(root->left, p)) {
        return lowest_common_ancestor(root->left, p, q);
    }
    // 如果 p、q 在右子树，那么公共祖先要在右子树查找
    if (find(root->right, p) && find(root->right, p)) {
        return lowest_common_ancestor(root->right, p, q);
    }
    // 如果 p、q 分别在左右子树，那么根节点即为公共祖先
    return root;
}


// 递归函数的定义：返回 p、q、lca 或者 nullptr
// 在树 root 中，找到节点 p 和节点 q 的最近公共祖先
// 这个版本就不是那么好理解，因为把求 lca 和搜索节点 p 和 节点 q 的代码混在一起了
// 因为 lowest_common_ancestor 函数本身不止一个功能
TreeNode* _lowest_common_ancestor(TreeNode* root, TreeNode* p, TreeNode* q)
{
    // 如果树为空，那么最近公共祖先不存在，直接返回
    if (root == nullptr) return nullptr;
    // 如果节点之一是根节点，那么直接返回
    // 因为如果再递归下去，必然就不会是这个节点的祖先了
    if (p == root || q == root) return root;

    // 否则的话，去左右子树中找
    TreeNode* left = lowest_common_ancestor(root->left, p, q);
    TreeNode* right = lowest_common_ancestor(root->right, p, q);

    // 如果左右子树都找到了，说明 q 和 p 分别在左右两颗子树上
    // 所以此时最近公共祖先是 root
    if (left != nullptr && right != nullptr) {
        return root;
    }
    // 如果左右子树都没找到，说明没有
    if (left == nullptr && right == nullptr) {
        return nullptr;
    }

    // 否则的话，q 和 p 在树的同一侧，那么返回那一侧
    return left == nullptr ? right : left;
}

void traversal(TreeNode* root, int v, TreeNode*& k)
{
    if (root == nullptr) return ;

    if (root->val == v) {
        k = root;
        return ;
    }
    traversal(root->left, v, k);
    traversal(root->right, v, k);

    return ;
}

int main () {
#ifdef LOCAL
    freopen("0236.in", "r", stdin);
#endif
    int n = 0, a = 0, b = 0;
    while (std::cin >> n >> a >> b) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        TreeNode* tree = build_tree(nums);
        TreeNode* p = nullptr;
        TreeNode* q = nullptr;
        traversal(tree, a, p);
        traversal(tree, b, q);
        TreeNode* res = lowest_common_ancestor(tree, p, q);
        traversal(res);
    }

    return 0;
}
