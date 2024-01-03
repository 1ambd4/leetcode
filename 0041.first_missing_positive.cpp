#include <iostream>
#include <vector>
#include <set>

using std::vector, std::set;

// n 个数字，找到第一个缺失的正整数
// 那么调整nums数组，使得第 i 个位置保存正整数 i - 1
// 即 nums[i] = i - 1
int first_missing_positive(vector<int>& nums)
{
    int n = nums.size();

    for (int i = 0; i < n; ++i) {
        while (nums[i] != i + 1) {
            // 跳过不重要的元素
            if (nums[i] <= 0 || nums[i] > n) {
                break;
            }
            // 如果所在位置已经有相同元素了，那么同样跳过
            // 避免 [1, 1] 这样的情况出现死循环
            if (nums[i] == nums[nums[i] - 1]) {
                break;
            }

            int idx = nums[i] - 1;
            // nums[i] = nums[idx];
            // nums[idx] = idx + 1;
            std::swap(nums[i], nums[idx]);
        }
    }

    for (int i = 0; i < n; ++i) {
        if (nums[i] != (i+1)) {
            return i + 1;
        }
    }

    return n + 1;
}

int _first_missing_positive(vector<int>& nums)
{
    std::set<int> s(nums.begin(), nums.end());

    int res = 1;
    for (const auto e: s) {
        if (e < 1) continue;
        if (e == res) {
            res++;
        } else {
            return res;
        }
    }

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0041.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        std::cout << first_missing_positive(nums) << std::endl;
    }

    return 0;
}
