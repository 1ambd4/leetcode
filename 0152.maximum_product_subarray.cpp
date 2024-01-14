#include <iostream>
#include <limits>
#include <vector>

using std::vector;

// 为啥之前写的遇到 [-2, 3, -4] 就寄了呢？
// 因为没有考虑之后有负数的情况，那么怎么整呢？
// 如果后面出现负数，那么需要前面也是一个负数，这样乘积才会变大
// 也就是说还需要记录一下出现的最小值
int max_product(vector<int>& nums)
{
    int n = nums.size();

    // f1[i]：以 nums[i] 结尾的最大连乘积
    // f2[i]：以 nums[i] 结尾的最小连乘积
    vector<int> f1(n, 1);
    vector<int> f2(n, 1);
    f1[0] = nums[0];
    f2[0] = nums[0];

    int res = nums[0];
    for (int i = 1; i < n; ++i) {
        f1[i] = std::max(f1[i-1] * nums[i], std::max(f2[i-1] * nums[i], nums[i]));
        f2[i] = std::min(f2[i-1] * nums[i], std::min(f1[i-1] * nums[i], nums[i]));
        res = std::max(res, std::max(f1[i], f2[i]));
    }

    return res;
}


// 这么写显然是不行的，比如：[-2, 3, -4]
// 在 i = 1 的时候，因为无法知悉后面是否还有负数的出现
// f[1] = 3
// 则最终无法取得真正的结果 -2 * 3 * -4 = 24
int _max_product(vector<int>& nums)
{
    int n = nums.size();

    // f[i]: 以 nums[i] 结尾的最大连乘积
    vector<int> f(n, 1);
    f[0] = nums[0];

    int res = f[0];

    for (int i = 1; i < n; ++i) {
        f[i] = std::max(f[i-1] * nums[i], nums[i]);
        res = std::max(res, f[i]);
    }

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0152.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        std::cout << max_product(nums) << std::endl;
    }

    return 0;
}
