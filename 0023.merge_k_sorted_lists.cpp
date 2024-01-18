#include <iostream>
#include <queue>
#include <vector>

#include "leetcode.h"

using std::vector;

ListNode* merge_k_lists(vector<ListNode*>& lists)
{
    ListNode *dummy = new ListNode(-1, nullptr);
    ListNode *cur = dummy;

    // priority_queue 的写法和其他的 cmp 反着来了么？
    auto cmp = [](ListNode* a, ListNode* b) -> bool {
        return a->val > b->val;
    };

    std::priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> q(cmp);
    for (const auto& list : lists) {
        if (list != nullptr) q.push(list);
    }

    while (!q.empty()) {
        ListNode *tmp = q.top();
        q.pop();
        cur->next = tmp;
        cur = cur->next;
        if (tmp->next != nullptr) {
            q.push(tmp->next);
        }
    }

    return dummy->next;
}

int main () {
#ifdef LOCAL
    freopen("0023.in", "r", stdin);
#endif
    int n = 0, t = 0;
    while (std::cin >> n) {
        vector<ListNode*> lists;
        for (int i = 0; i < n; ++i) {
            std::cin >> t;
            vector<int> nums(t, 0);
            for (int j = 0; j < t; ++j) {
                std::cin >> nums[j];
            }
            ListNode *tmp = build_list(nums);
            lists.push_back(tmp);
        }
        ListNode *res = merge_k_lists(lists);
        show_list(res);
    }

    return 0;
}
