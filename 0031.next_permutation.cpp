#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using std::vector;

// 从右往左，找到第一对逆序，然后交换？
void next_permutation(vector<int>& nums)
{
    int n = nums.size();
    // 两层 for 不行捏，比如：4,2,0,2,3,2,0
    // 应该是：4,2,0,3,0,2,2
    // 而不是：4,2,2,0,0,2,3
    // 即两层 for 会更偏向于让低位的交换到前面
    // 但实际上也需要考虑比地位稍微高一点的，可能交换的高位更小
    // for (int i = n - 1; i >= 0; --i) {
    //     for (int j = i - 1; j >= 0; --j) {
    //         if (nums[j] < nums[i]) {
    //             std::swap(nums[i], nums[j]);
    //             std::sort(nums.begin() + j + 1, nums.end(), std::less<int>());
    //             return ;
    //         }
    //     }
    // }

    int l = 0, r = 0;
    for (int i = n - 2; i >= 0; --i) {
        if (nums[i] < nums[i + 1]) {
            l = i;
            for (int j = n - 1; j > l; --j) {
                if (nums[j] > nums[l]) {
                    r = j;
                    break;
                }
            }
            std::swap(nums[l], nums[r]);
            std::sort(nums.begin() + l + 1, nums.end(), std::less<int>());
            return ;
        }
    }

    std::reverse(nums.begin(), nums.end());
}

int main () {
#ifdef LOCAL
    freopen("0031.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        next_permutation(nums);
        for (int i = 0; i < n; ++i) {
            printf(",%d" + !i, nums[i]);
        }
        std::cout << std::endl;
    }

    return 0;
}
