#include <iostream>
#include <vector>

#include "leetcode.h"

using std::vector;

void sort_colors(vector<int>& nums)
{
    int n = nums.size();

    int l = 0, r = n - 1;
    int c = 0;

    while (c <= r) {
        if (nums[c] == 0) {
            std::swap(nums[c], nums[l]);
            ++l;
            ++c;
        } else if (nums[c] == 1) {
            ++c;
        } else if (nums[c] == 2) {
            std::swap(nums[c], nums[r]);
            --r;
        }
    }
}

int main () {
#ifdef LOCAL
    freopen("0075.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        sort_colors(nums);

        std::cout << nums << std::endl;
    }

    return 0;
}
