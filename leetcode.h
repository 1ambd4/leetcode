#ifndef LEETCODE_H_
#define LEETCODE_H_

#include <cstdio>
#include <queue>
#include <vector>
#include <iostream>


#define LOG(x, ...) \
    std::cout << __FUNCTION__ << " " << __LINE__  << ": " << #x << " = " << x << std::endl;


struct ListNode {
    public:
        ListNode() : val(0), next(nullptr) { }
        ListNode(int x) : val(x), next(nullptr) { };
        ListNode(int x, ListNode *next) : val(x), next(next) { };

        int val;
        ListNode *next;
};

ListNode* build_list(std::vector<int> nums)
{
    ListNode *head = new ListNode();
    ListNode *cur = head;
    for (const int& num : nums) {
        ListNode *temp = new ListNode(num);
        cur->next = temp;
        cur = cur->next;
    }
    return head->next;
}

void show_list(ListNode *head)
{
    while (head != nullptr) {
        std::cout << head->val << " ";
        head = head->next;
    }
    std::cout  << std::endl;
}

std::ostream& operator << (std::ostream& os, ListNode *head)
{
    while (head != nullptr) {
        std::cout << head->val << " ";
        head = head->next;
    }
    return os;
}


struct TreeNode {
    public:
        TreeNode() : val(0), left(nullptr), right(nullptr) { }
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) { }
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) { }

        int val;
        TreeNode *left, *right;
};

// 1, null, 2, 3 层次遍历建树
TreeNode* build_tree(std::vector<int>& nums)
{
    if (nums.size() == 0) return nullptr;
    TreeNode *head = new TreeNode(nums[0]), *cur = head, *temp;
    std::queue<TreeNode*> q;
    q.push(cur);
    for (int i = 1; i < nums.size(); i+=2) {
        cur = q.front();
        q.pop();
        if (i < nums.size()) {
            if (nums[i] != -1) {
                temp = new TreeNode(nums[i]);
                cur->left = temp;
                q.push(temp);
            } else {
                cur->left = nullptr;
            }
        }
        if (i+1 < nums.size()) {
            if (nums[i+1] != -1) {
                temp = new TreeNode(nums[i+1]);
                cur->right = temp;
                q.push(temp);
            } else {
                cur->right = nullptr;
            }
        }
    }
    return head;
}

// 层序遍历
void traversal(TreeNode *head)
{
    if (head == nullptr) return ;
    TreeNode *cur;
    std::queue<TreeNode*> q;
    q.push(head);
    std::cout << head->val << " ";
    while (!q.empty()) {
        cur = q.front();
        q.pop();
        if (cur->left != nullptr) {
            q.push(cur->left);
            std::cout << cur->left->val << " ";
        } else {
            std::cout << "null ";
        }
        if (cur->right != nullptr) {
            q.push(cur->right);
            std::cout << cur->right->val << " ";
        } else {
            std::cout << "null ";
        }
    }
    std::cout << std::endl;
}


TreeNode* build_bst(std::vector<int>& nums)
{
    int n = nums.size();
    if (n == 0) return nullptr;

    TreeNode *root = new TreeNode(nums.front()), *cur = root;

    for (int i = 1; i < n; ++i) {
        cur = root;
        while (true) {
            if (nums[i] < cur->val) {
                if (cur->left != nullptr) {
                    cur = cur->left;
                } else {
                    cur->left = new TreeNode(nums[i]);
                    break;
                }
            } else {
                if (cur->right != nullptr) {
                    cur = cur->right;
                } else {
                    cur->right = new TreeNode(nums[i]);
                    break;
                }
            }
        }
    }

    return root;
}

void traverse_bst(TreeNode *root)
{
    // if (root == nullptr) return ;

    // traverse_bst(root->left);
    // std::cout << root->val << " ";
    // traverse_bst(root->right);

    // l...lisp?
    auto traverse = [](auto&& self, TreeNode *root) {
        if (root == nullptr) return ;

        self(self, root->left);
        std::cout << root->val << " ";
        self(self, root->right);
    };

    traverse(traverse, root);
    std::cout << std::endl;
}

void addnode_bst(TreeNode *root, int val)
{
    auto addnode = [](auto&& self, TreeNode *root, int val) {
        if (root == nullptr) return ;

        if (val < root->val) {
            if (root->left != nullptr) {
                self(self, root->left, val);
            } else {
                root->left = new TreeNode(val);
                return ;
            }
        } else {
            if (root->right != nullptr) {
                self(self, root->right, val);
            } else {
                root->right = new TreeNode(val);
                return ;
            }
        }
    };

    addnode(addnode, root, val);
}


class Node {
public:
    int val;
    std::vector<Node*> children;

    Node() { }
    Node(int val) : val(val) { }
    Node(int val, std::vector<Node*> child) : val(val), children(child) { }
};

Node *build_nbt(std::vector<int> nums)
{
    int n = nums.size();
    if (n == 0) return nullptr;

    Node *root = new Node(nums.front()), *cur = root;
    std::queue<Node*> q;
    q.push(cur);

    for (int i = 1; i < n; ++i) {
        if (nums[i] == -1) {
            cur = q.front();
            q.pop();
        } else {
            Node *tmp = new Node(nums[i]);
            cur->children.push_back(tmp);
            q.push(tmp);
        }
    }

    return root;
}

void traverse_nbt(Node *root)
{
    auto traverse = [](auto&& self, Node *root) {
        if (root == nullptr) return ;
        std::cout << root->val << " ";

        for (const auto& child : root->children) {
            self(self, child);
        }
    };

    traverse(traverse, root);
    std::cout << std::endl;
}


template <typename T>
std::ostream& operator << (std::ostream& os, std::vector<T> v)
{
    for (const auto& e : v) {
        os << e << ' ';
    }
    return os;
}

template <typename T>
std::ostream& operator << (std::ostream& os, std::vector<std::vector<T>> vs)
{
    os << '[';
    for (const auto& v : vs) {
        int n = v.size();

        os << '[';
        for (int i = 0; i < n; ++i) {
            std::printf(",%d" + !i, v[i]);
        }
        os << ']';
    }
    os << ']';
    return os;
}

#endif  // LEETCODE_H
