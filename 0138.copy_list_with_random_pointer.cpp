#include <iostream>
#include <vector>
#include <unordered_map>

using std::vector, std::unordered_map;

class Node {
public:
    int val;
    Node *next;
    Node *ramdom;

    Node(int val)
        : val(val), next(nullptr), ramdom(nullptr)
    { }
};

// 先拷贝 next 域，等整个链表建好了再拷贝 random 域？
// 为了 random 域连接的时候方便
// 干脆 next 创建的时候把地址扔 map 里存着
//
// 看错题了捏，直接给的是链表啊
// Node* copy_random_list(Node *head)
// {
//     if (head == nullptr) return nullptr;
//
//     unordered_map<int, Node*> m;
//     Node *res = new Node(head->val);
//
//     Node *cur = head;
//
// }

// 如果不限制空间的话
// 那么，我直接 mappig Node -> Node
Node* copy_random_list(Node *head)
{
    unordered_map<Node*, Node*> m;

    // mapping
    Node *cur = head;
    while (cur != nullptr) {
        m[cur] = new Node(cur->val);
        cur = cur->next;
    }

    // modify
    cur = head;
    while (cur != nullptr) {
        m[cur]->next = m[cur->next];
        m[cur]->ramdom = m[cur->ramdom];
        cur = cur->next;
    }

    return m[head];
}

// 倍增复制之后分裂？
Node* _copy_random_list(Node *head)
{
    if (head == nullptr) return nullptr;

    Node *cur = head, *tmp = nullptr;
    while (cur != nullptr) {
        tmp = new Node(cur->val);
        tmp->next = cur->next;
        cur->next = tmp;
        // 这里不对劲儿，需要整条链表都建好了才能复制 random 域的
        // tmp->ramdom = cur->ramdom->next;
        cur = cur->next->next;
    }

    cur = head, tmp = nullptr;
    while (cur != nullptr) {
        if (cur->ramdom != nullptr) {
            cur->next->ramdom = cur->ramdom->next;
        }
        cur = cur->next->next;
    }

    // 分裂
    Node *res = head->next;
    cur = head, tmp =res;

    while (cur != nullptr) {
        cur->next = cur->next->next;
        if (cur->next != nullptr) {
            tmp->next = cur->next->next;
        } else {
            tmp->next = nullptr;
        }
        cur = cur->next;
        tmp = tmp->next;
    }

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0138.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
    }

    return 0;
}
