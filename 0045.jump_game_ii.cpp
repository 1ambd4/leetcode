#include <iostream>
#include <vector>

using std::vector;

int jump(vector<int>& nums)
{
    int n = nums.size();

    // f[i]：跳到 nums[i] 需要的最小次数
    vector<int> f(n, n);

    f[0] = 0;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (j + nums[j] >= i) {
                f[i] = std::min(f[i], f[j] + 1);
            }
        }
    }

    return f[n-1];
}

int main () {
#ifdef LOCAL
    freopen("0045.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        std::cout << jump(nums) << std::endl;
    }

    return 0;
}
