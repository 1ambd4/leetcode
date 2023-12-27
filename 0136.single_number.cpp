#include <iostream>
#include <vector>

using std::vector;

int single_number(vector<int>& nums)
{
    int res = 0;

    for (const auto num : nums) {
        res ^= num;
    }

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0136.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        std::cout << single_number(nums) << std::endl;
    }

    return 0;
}
