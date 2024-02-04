#include <iostream>
#include <vector>

using std::vector;

// ref: https://leetcode.cn/problems/candy/solutions/17847/candy-cong-zuo-zhi-you-cong-you-zhi-zuo-qu-zui-da-/?envType=study-plan-v2&envId=top-interview-150
//
// 记学生 A 和学生 B 左右相邻，且 A 在 B 左边
// 则左规则：当RB > RA 时，B 的糖果比 A 的多
//   右规则：当RA > RB 时，A 的糖果比 B 的多
// 那么，所有相邻的同学中，评分高的必须获得更多的糖果
// 等价于所有的学生满足左规则且满足右规则
int candy(vector<int>& ratings)
{
    int n = ratings.size();
    // 先给每个人分一颗糖果
    vector<int> candy(n, 1);

    for (int i = 1; i < n; ++i) {
        // 左规则
        if (ratings[i-1] < ratings[i]) {
            candy[i] = candy[i-1] + 1;
        }
    }

    int count = candy[n-1];
    for (int i = n-2; i >= 0; --i) {
        // 右规则
        if (ratings[i] > ratings[i+1] && candy[i] <= candy[i+1]) {
            candy[i] = candy[i+1] + 1;
        }
        count += candy[i];
    }

    return count;
}

int main () {
#ifdef LOCAL
    freopen("0135.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
            vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        std::cout << candy(nums) << std::endl;
    }

    return 0;
}
