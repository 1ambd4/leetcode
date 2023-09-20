#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

#include <bitset>

int min_number(std::vector<int>& nums1, std::vector<int>& nums2)
{
    int res = 10;

    std::bitset<10> cnt1{0};
    for (auto num : nums1) cnt1[num] = 1;
    for (auto num: nums2) {
        if (cnt1.test(num)) res = std::min(res, num);
    }

    if (res > 9) res = 0;

    auto a = *std::min_element(nums1.begin(), nums1.end());
    auto b = *std::min_element(nums2.begin(), nums2.end());

    return res != 0 ? res : std::min(a * 10 + b, b * 10 + a);
}

int main()
{
#ifdef LOCAL
    freopen("2605.in", "r", stdin);
#endif
    int n = 0, m = 0;
    while (std::cin >> n >> m) {
        std::vector<int> nums1(n, 0);
        std::vector<int> nums2(m, 0);

        for (int i = 0; i < n; ++i) std::cin >> nums1[i];
        for (int i = 0; i < m; ++i) std::cin >> nums2[i];

        std::cout << min_number(nums1, nums2) << std::endl;
    }
    return 0;
}

