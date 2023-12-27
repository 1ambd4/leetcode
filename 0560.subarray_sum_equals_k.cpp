#include <iostream>
#include <unordered_map>
#include <vector>

using std::vector;

// 思考为什么会 TLE 呢？
// 直观原因就是暴力遍历是 O(n)
// 那么，考虑暴力过程中如何优化
// 是可以的，比如这里内层循环枚举所有的 j 进行判断
// 可以使用前缀和优化
// 原先判断的条件是 [j..i] 这个子数组的和为 k
// 在有了前缀和的情况下，pre[i] = pre[i-1] + nums[i]
// 变成了 pre[i] - pre[j-1] == k
// 再做一下变形，得到：pre[j-1] == pre[i] - k
// 所以，统计以 i 结尾的和为 k 的子数组的个数转化成了
// 统计有多少个前缀和为 pre[i] - k 的 pre[j] 即可
// 那么，用哈希表来保存 pre[i] 出现的次数
// 因为统计的 j 都是小于等于 i 的，所以可以变更新哈希表边计算
int subarray_sum(vector<int>& nums, int k)
{
    std::unordered_map<int, int> m;

    // 前缀和为 0 的有一个，即空集
    m[0] = 1;

    int cnt = 0, pre = 0;
    // 枚举每一个数字
    for (const auto& x : nums) {
        // 把当前值加到前缀和上去
        pre += x;
        // 查表看之前的前缀和里有多少个等于 pre-k 的
        cnt += m[pre-k];
        // 更新前缀和个数表
        m[pre]++;
    }

    return cnt;
}


// 统计以 i 结尾的和为 k 的子数组的个数
// 即统计符合条件的下标 j 的个数，
// 其中，0 <= j <= i，且 [j, i] 这个子数组的和为 k
// 因而，暴力的枚举 [0..i] 里所有下标 j 来判断是否符合条件
//
// 当然了，暴力 TLE 了
int _subarray_sum(vector<int>& nums, int k)
{
    int n = nums.size();
    int res = 0;

    for (int i = 0; i < n; ++i) {
        int sum = 0;
        for (int j = i; j >= 0; --j) {
            sum += nums[j];
            if (sum == k) {
                // 需要注意的是，nums[i] 可能为负数
                // 故而此处即使找到了一个 j，仍旧需要将 j 遍历到头
                // 以做到不漏
                res++;
            }
        }
    }

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0560.in", "r", stdin);
#endif
    int n = 0, k = 0;
    while (std::cin >> n >> k) {
        vector<int> nums(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        std::cout << subarray_sum(nums, k) << std::endl;
    }

    return 0;
}
