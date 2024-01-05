#include <iostream>
#include <vector>

#include "leetcode.h"

ListNode* swap_pairs(ListNode *head)
{
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    ListNode *next = head->next;
    head->next = swap_pairs(next->next);
    next->next = head;

    return next;
}

ListNode* _swap_pairs(ListNode *head)
{
    // ListNode *dummy = new ListNode(-1, head);
    // ListNode *cur = dummy, *temp = nullptr;
    //
    // auto swap = [](ListNode *head) -> ListNode* {
    //
    // };
    //
    // // 如果有两个节点的话，那么交换这两个
    // // cur 是当前节点的前驱，实际要交换的是 cur->next 和 cur->next->next
    // if (cur != nullptr && cur->next != nullptr && cur->next->next != nullptr) {
    //     temp = cur->next;
    //     cur->next = cur->next->next;
    //     temp->next = cur->next->next;
    //     cur->next->next = temp;
    // } else if (cur != nullptr && cur->next != nullptr && cur->next->next == nullptr) {
    //     // 如果只有一个节点的话，不需要交换了啊
    // }
    //
    // return dummy->next;
}

using std::vector;

int main () {
#ifdef LOCAL
    freopen("0024.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        ListNode *head = build_list(nums);
        ListNode *res = swap_pairs(head);
        show_list(res);
    }

    return 0;
}
