#include <iostream>
#include <vector>

#include "leetcode.h"

using std::vector;

// ListNode* reverse(ListNode* head)
// {
//     if (head == nullptr || head->next == nullptr) {
//         return head;
//     }
//
//     ListNode *cur = head;
//     head = reverse(cur->next);
//     cur->next->next = cur;
//     cur->next = nullptr;
//
//     return head;
// }
//
// ListNode *succ = nullptr;
//
// ListNode* reverse_n(ListNode* head, int n)
// {
//     if (n == 1) {
//         succ = head->next;
//         return head;
//     }
//
//     ListNode *last = reverse_n(head->next, n - 1);
//     head->next->next = head;
//     head->next = succ;
//
//     return last;
// }

ListNode* reverse_between(ListNode* head, int left, int right)
{
    ListNode *dummy = new ListNode(-1, head);
    ListNode *pre = dummy;
    ListNode *cur = head;
    ListNode *nxt = nullptr;
    ListNode *til = nullptr;

    int cnt = 1;
    while (cnt < left) {
        pre = pre->next;
        cur = cur->next;
        ++cnt;
    }

    cnt = right - left;
    nxt = cur->next;
    til = cur;
    for (int i = 0; i < cnt; ++i) {
        pre->next = nxt;
        til->next = nxt->next;
        // cur->next = til;
        nxt->next = cur;

        cur = nxt;
        nxt = til->next;
    }

    return dummy->next;
}

// ListNode* reverse_between(ListNode* head, int left, int right)
// {
//     ListNode *dummy = new ListNode(-1, head);
//     ListNode *pre = dummy;
//     ListNode *cur = head;
//     ListNode *nxt = nullptr;
//
//     int cnt = 1;
//     while (cnt < left) {
//         pre = pre->next;
//         cur = cur->next;
//         ++cnt;
//     }
//
//     cnt = right - left;
//     nxt = cur->next;
//     for (int i = 0; i < cnt; ++i) {
//         pre->next = nxt;
//         cur->next = nxt->next;
//         nxt->next = cur;
//         pre = pre->next;
//         nxt = cur->next;
//     }
//
//     return head;
// }

int main () {
#ifdef LOCAL
    freopen("0092.in", "r", stdin);
#endif
    int n = 0;
    int left = 0, right = 0;
    while (std::cin >> n) {
        std::cin >> left >> right;
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        ListNode *tree = build_list(nums);
        ListNode *res = reverse_between(tree, left, right);
        show_list(res);
    }

    return 0;
}
