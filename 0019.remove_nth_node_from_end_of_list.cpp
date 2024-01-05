#include <iostream>
#include <vector>

#include "leetcode.h"

using std::vector;

ListNode* remove_nth_from_end(ListNode *head, int n)
{
    ListNode *dummy = new ListNode(-1, head);
    ListNode *left = dummy;
    ListNode *right = dummy;

    while (n-- >= 0) {
        right = right->next;
    }
    while (right != nullptr) {
        left = left->next;
        right = right->next;
    }
    left->next = left->next->next;

    return dummy->next;
}

int main () {
#ifdef LOCAL
    freopen("0019.in", "r", stdin);
#endif
    int n = 0, k = 0;
    while (std::cin >> n >> k) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        ListNode *list = build_list(nums);
        ListNode *res = remove_nth_from_end(list, k);
        show_list(res);
    }

    return 0;
}
