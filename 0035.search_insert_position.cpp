#include <iostream>
#include <vector>

using std::vector;

// [l, m], (m, r]
int search_insert(vector<int>& nums, int t)
{
    int n = nums.size();

    int l = 0, r = n - 1;
    while (l < r) {
        int m = (l + r + 1) >> 1;
        if (nums[m] <= t) l = m;
        else r = m - 1;
    }

    // if (l == 0) {
    //     if (nums[l] < t) l = 1;
    // } else if (l == n - 1) {
    //     if (nums[l] < t) l = n;
    // }

    // 没必要像上面那么麻烦
    // 首先明确的是，如果 t 存在
    // 那么返回的是最右边界
    // 而现在需要处理一下 t 不存在的情况
    // 显然，此时返回的是小于 t 的元素中的最大的那一个
    // 因而应该判断一下 nums[l] 是否等于 t，即 t 是否存在
    // 如果不存在就 +1
    if (nums[l] < t) l++;
    return l;
}

// [l, m), [m r]
int _search_insert(vector<int>& nums, int t)
{
    int n = nums.size();

    int l = 0, r = n - 1;
    while (l < r) {
        int m = (l + r) >> 1;
        if (nums[m] >= t) r = m;
        else l = m + 1;
    }

    // if (l == n - 1) {
    //     if (nums[l] < t) l = n;
    // }

    // 此处同理
    if (nums[l] < t) l++;
    return l;
}

int main () {
#ifdef LOCAL
    freopen("0035.in", "r", stdin);
#endif
    int n = 0, t = 0;
    while (std::cin >> n >> t) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        std::cout << search_insert(nums, t) << std::endl;
    }

    return 0;
}
