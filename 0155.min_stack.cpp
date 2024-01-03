#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

// O(1) 的实现最小栈的话
// 那么需要在每个节点上都保存最小值
class MinStack {
public:
    MinStack()
    {
        head = nullptr;
    }

    void push(int val)
    {
        if (head == nullptr) {
            head = new Node(val, val);
        } else {
            int min = std::min(val, head->min);
            head = new Node(val, min, head);
        }
    }

    void pop()
    {
        head = head->next;
    }

    int top()
    {
        return head->val;
    }

    int get_min()
    {
        return head->min;
    }
private:
    struct Node {
        int val;
        int min;
        Node* next;

        Node(int val, int min)
            : val(val), min(min)
        { }

        Node(int val, int min, Node *next)
            : val(val), min(min), next(next)
        { }
    };

    Node *head;
};

int main () {
#ifdef LOCAL
    freopen("0155.in", "r", stdin);
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
