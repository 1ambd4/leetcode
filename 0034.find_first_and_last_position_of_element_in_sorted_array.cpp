#include <iostream>
#include <vector>

using std::vector;

vector<int> search_range(vector<int>& nums, int t)
{
    int n = nums.size();
    if (n == 0) return {-1, -1};

    // 最左
    int ll = 0, lr = n - 1;
    while (ll < lr) {
        int m = (ll + lr) >> 1;
        if (nums[m] >= t) lr = m;
        else ll = m + 1;
    }

    int rl = 0, rr = n - 1;
    while (rl < rr) {
        int m = (rl + rr + 1) >> 1;
        if (nums[m] <= t) rl = m;
        else rr = m - 1;
    }

    if (nums[ll] != t) return {-1, -1};

    return {ll, rl};
}

int main () {
#ifdef LOCAL
    freopen("0034.in", "r", stdin);
#endif
    int n = 0, t = 0;
    while (std::cin >> n >> t) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        vector<int> res = search_range(nums, t);
        std::cout << res[0] << ", " << res[1] << std::endl;
    }

    return 0;
}
