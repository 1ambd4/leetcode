#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using std::vector;

long long max_array_value(vector<int>& nums)
{
    int n = nums.size();
    nums.push_back(0);

    std::reverse(nums.begin(), nums.end());

    long long res = 0;
    long long tmp = nums[0];
    for (int i = 0; i < n; ++i) {
        if (tmp >= nums[i+1]) {
            tmp += nums[i+1];
        } else {
            res = std::max(res, tmp);
            tmp = nums[i+1];
        }
    }
    res = std::max(res, tmp);

    return res;
}

int main () {
#ifdef LOCAL
    freopen("2789.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        std::cout << max_array_value(nums) << std::endl;
    }

    return 0;
}
