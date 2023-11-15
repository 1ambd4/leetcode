#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

// 没看出来这题究竟想干嘛
// 明显每次都拿最大的数啊
// 那不就是一个等差数列求和么
int maximize_sum(vector<int>& nums, int k)
{
    int max = *std::max_element(nums.begin(), nums.end());
    return k * max + (k - 1) * k / 2;
}

int main () {
#ifdef LOCAL
    freopen("2656.in", "r", stdin);
#endif
    int n = 0, k = 0;
    while (std::cin >> n >> k) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        std::cout << maximize_sum(nums, k) << std::endl;
    }

    return 0;
}
