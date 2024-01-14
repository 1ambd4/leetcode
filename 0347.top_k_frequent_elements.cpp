#include <algorithm>
#include <array>
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>

using std::vector, std::array;

vector<int> top_k_frequent(vector<int>& nums, int k)
{
    int n = nums.size();
    std::unordered_map<int, int> m;
    for (const auto num : nums) m[num]++;
    vector<array<int, 2>> tmp;
    for (const auto [k, v] : m) {
        tmp.push_back({k, v});
    }
    // 可以用大小为 k 的 priority_queue 代替 sort
    // 似乎能快一点？不确定
    std::sort(tmp.begin(), tmp.end(), [](const array<int, 2>& a, const array<int, 2>& b) -> bool {
            return a[1] > b[1];
    });

    vector<int> res;
    for (int i = 0; i < k; ++i) {
        res.push_back(tmp[i][0]);
    }

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0347.in", "r", stdin);
#endif
    int n = 0, k = 0;
    while (std::cin >> n >> k) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        vector<int> res = top_k_frequent(nums, k);
        for (int i = 0; i < k; ++i) {
            printf(",%d" + !i, res[i]);
        }
        std::cout << std::endl;
    }

    return 0;
}
