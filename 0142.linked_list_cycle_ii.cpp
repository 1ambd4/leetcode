#include <iostream>
#include <vector>

#include "leetcode.h"

using std::vector;

// 思考有环的情况
// 记环的入口到链表头的距离为 a
// 记环上的节点数为 b
// 那么考虑快慢指针相遇时候走过的距离
// 有 f = 2s 和 f = s + nb
// 前面的好理解，快指针是慢指针速度的两倍
// 第二个式子的意思则是如果两者相遇
// 记相遇点 M，那么必然有快指针在环上一直绕圈圈
// 最后绕到了点 M，此时慢指针也恰好来到了点 M
// 记快指针在环上绕了 n 圈
// 那么就有 f = s + nb
//
// 从 f = 2s 和 f = s + nb
// 可解得 s = nb 和 f = 2nb
// 即快慢指针相遇时侯走的路程都是环上节点的整数倍
//
// 似乎完全没有什么用，确实是这样
// 要求的应该是这里的 a 啊
// 那么，如何才能够凑出这个 a 呢？
//
// 思考这么一种情况，快指针再一次来到了环的入口
// 那么这时候快指针走了多少距离呢？
// 显然应该是 a + mb
// 在这以后，快指针每再走 b 步，就又来到了环的入口
// 从前面知道，慢指针走了 nb 步
// 如果想让满指针走到环入口的话，还需要再走 a 步
//
// 如何走出 a 步呢？
// 那就轮到快慢指针了，慢指针走了 nb 步，快指针走了 2nb 步骤
// 如果这时候让慢指针回到原点，而快指针恢复正常速度
// 那么它们会在何处相遇呢？
// 很显然，正好是再 a 步后相遇
// 因为回到原点的慢指针在 a 步后刚好到达环的起点
// 而对于快指针而言，走 a 步后也刚好走出 a + 2nb 步，即也来到了环的入口
// 至此问题解决
ListNode *detect_cycle(ListNode *head)
{
    ListNode *slow = head;
    ListNode *fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            slow = head;
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            return slow;
        }
    }

    return nullptr;
}

int main () {
#ifdef LOCAL
    freopen("0142.in", "r", stdin);
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
