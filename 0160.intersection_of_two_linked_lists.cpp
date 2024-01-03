#include <iostream>
#include <vector>

#include "leetcode.h"

using std::vector;

ListNode* get_intersection_node(ListNode* ha, ListNode* hb)
{
    ListNode *la = ha, *lb = hb;
    while (la != lb) {
        if (la != nullptr) la = la->next;
        else la = hb;

        if (lb != nullptr) lb = lb->next;
        else lb = ha;
    }

    return la;
}

int main () {
#ifdef LOCAL
    freopen("0160.in", "r", stdin);
#endif

    return 0;
}
