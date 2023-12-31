#include <cstdio>
#include <iostream>
#include <vector>

using std::vector;

int max_subarray(vector<int>& nums)
{
    int n = nums.size();
    int res = nums[0];

    vector<int> f(n, 0);
    f[0] = nums[0];

    for (int i = 1; i < n; ++i) {
        f[i] = std::max(f[i-1] + nums[i], nums[i]);
        res = std::max(res, f[i]);
    }

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0053.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        std::cout << max_subarray(nums) << std::endl;
    }

    return 0;
}
