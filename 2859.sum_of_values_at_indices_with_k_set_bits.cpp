#include <bitset>
#include <iostream>
#include <vector>

using std::vector;

int sum_indices_with_k_set_bits(vector<int>& nums, int k)
{
    int n = nums.size();
    int res = 0;

    for (int i = 0; i < n; ++i) {
        if (__builtin_popcount(i) == k) {
            res += nums[i];
        }
    }

    return res;
}

int _sum_indices_with_k_set_bits(vector<int>& nums, int k)
{
    int n = nums.size();
    int res = 0;

    for (int i = 0; i < n; ++i) {
        if (std::bitset<32>(i).count() == k) {
            res += nums[i];
        }
    }

    return res;
}

int __sum_indices_with_k_set_bits(vector<int>& nums, int k)
{
    int n = nums.size();

    auto count_bits = [](int v) -> int {
        int cnt = 0;
        while (v > 0) {
            int a = v / 2;
            int b = v - a * 2;
            v /= 2;
            cnt += b;
        }
        return cnt;
    };

    int res = 0;
    for (int i = 0; i < n; ++i) {
        if (count_bits(i) == k) {
            res += nums[i];
        }
    }

    return res;
}

int main () {
#ifdef LOCAL
    freopen("2859.in", "r", stdin);
#endif
    int n = 0, k = 0;
    while (std::cin >> n >> k) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        std::cout << sum_indices_with_k_set_bits(nums, k) << std::endl;
    }

    return 0;
}
