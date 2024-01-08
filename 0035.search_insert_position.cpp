#include <iostream>
#include <vector>

using std::vector;

// [l, m], (m, r]
int search_insert(vector<int>& nums, int t)
{
    int n = nums.size();

    int l = 0, r = n - 1;
    while (l < r) {
        int m = (l + r + 1) >> 1;
        if (nums[m] <= t) l = m;
        else r = m - 1;
    }

    if (l == 0) {
        if (nums[l] < t) l = 1;
    } else if (l == n - 1) {
        if (nums[l] < t) l = n;
    }
    return l;
}

// [l, m), [m r]
int _search_insert(vector<int>& nums, int t)
{
    int n = nums.size();

    int l = 0, r = n - 1;
    while (l < r) {
        int m = (l + r) >> 1;
        if (nums[m] >= t) r = m;
        else l = m + 1;
    }

    if (l == n - 1) {
        if (nums[l] < t) l = n;
    }
    return l;
}

int main () {
#ifdef LOCAL
    freopen("0035.in", "r", stdin);
#endif
    int n = 0, t = 0;
    while (std::cin >> n >> t) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        std::cout << search_insert(nums, t) << std::endl;
    }

    return 0;
}
