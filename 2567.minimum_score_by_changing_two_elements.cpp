#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

int minimize_sum(vector<int>& nums)
{
    int n = nums.size();

    std::sort(nums.begin(), nums.end());

    int c = nums[n-1] - nums[2];
    int a = nums[n-2] - nums[1];
    int b = nums[n-3] - nums[0];

    return std::min(std::min(a, b), c);
}

int main()
{
#ifdef LOCAL
    freopen("2567.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        std::cout << minimize_sum(nums) << std::endl;
    }
}
