#include <iostream>
#include <vector>

#include "leetcode.h"

using std::vector;

ListNode* add_two_numbers(ListNode *l1, ListNode *l2)
{
    ListNode *dummy = new ListNode(-1, nullptr);
    ListNode *cur = dummy;

    int sum = 0;
    int carry = 0;

    while (l1 != nullptr && l2 != nullptr) {
        sum = l1->val + l2->val + carry;
        carry = sum / 10;
        sum = sum % 10;
        cur->next = new ListNode(sum, nullptr);
        cur = cur->next;
        l1 = l1->next;
        l2 = l2->next;
    }

    ListNode **res = (l1 != nullptr ? &l1 : &l2);
    while (*res != nullptr) {
        sum = (*res)->val + carry;
        carry = sum / 10;
        sum = sum % 10;
        cur->next = new ListNode(sum, nullptr);
        cur = cur->next;
        *res = (*res)->next;
    }

    if (l1 == l2 && carry) {
        cur->next = new ListNode(carry, nullptr);
    }

    return dummy->next;
}

ListNode* _add_two_numbers(ListNode *l1, ListNode *l2)
{
    ListNode *dummy = new ListNode(-1, nullptr);
    ListNode *cur = dummy;

    int sum = 0;
    int carry = 0;

    while (l1 != nullptr && l2 != nullptr) {
        sum = l1->val + l2->val + carry;
        carry = sum / 10;
        sum = sum % 10;
        cur->next = new ListNode(sum, nullptr);
        cur = cur->next;
        l1 = l1->next;
        l2 = l2->next;
    }

    while (l1 != nullptr) {
        sum = l1->val + carry;
        carry = sum / 10;
        sum = sum % 10;
        cur->next = new ListNode(sum, nullptr);
        cur = cur->next;
        l1 = l1->next;
    }

    while (l2 != nullptr) {
        sum = l2->val + carry;
        carry = sum / 10;
        sum = sum % 10;
        cur->next = new ListNode(sum, nullptr);
        cur = cur->next;
        l2 = l2->next;
    }

    if (carry != 0) {
        cur->next = new ListNode(carry, nullptr);
    }

    return dummy->next;
}

int main () {
#ifdef LOCAL
    freopen("0002.in", "r", stdin);
#endif
    int m = 0, n = 0;
    while (std::cin >> m >> n) {
        vector<int> nums1(m, 0);
        vector<int> nums2(n, 0);
        for (int i = 0; i < m; ++i) {
            std::cin >> nums1[i];
        }
        for (int i = 0; i < n; ++i) {
            std::cin >> nums2[i];
        }
        ListNode *l1 = build_list(nums1);
        ListNode *l2 = build_list(nums2);
        ListNode *res = add_two_numbers(l1, l2);
        show_list(res);
    }

    return 0;
}
