#include <iostream>
#include <vector>

using std::vector;

// 贪心，在每一步的时候都计算可以到达的最远点
// 如果在某一时刻，这个最远点的坐标小于当前值
// 那么，必然无法走到终点
bool can_jump(vector<int>& nums)
{
    int n = nums.size();
    int dis = 0;

    for (int i = 0; i < n; ++i) {
        if (i > dis) return false;
        dis = std::max(dis, i + nums[i]);
    }

    return true;
}

int main () {
#ifdef LOCAL
    freopen("0055.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        std::cout << can_jump(nums) << std::endl;
    }

    return 0;
}
