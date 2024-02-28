#include <iostream>
#include <vector>

using std::vector;

// 数状数组
// 最终得让每层上的值都相等？
// 不对
//    3
//  1    2
// 2 2  1  1
//
// 互为兄弟的叶子节点，由于除了叶子节点外，其余节点都一致
// 所以需要修改叶子节点，使得其相等，又只有增加操作，所以取较大值
//
// 而非兄弟的叶子节点，需要操作双亲
//
// 易知，从叶子节点开始往上写更方便
// 如果直接操作双亲节点，将子节点中较大的加上去，那么就更好写了
// 因为这样就相当于将双亲节点和叶子节点这一层合并了
// 然后，双亲节点就变成了逻辑上的叶子节点层
int min_increment(int n, vector<int>& cost)
{
    int res = 0;

    for (int i = n - 2; i > 0; i -= 2) {
        res += std::abs(cost[i] - cost[i+1]);
        cost[i/2] += std::max(cost[i], cost[i+1]);
    }

    return res;
}

int _min_increment(int n, vector<int>& cost)
{
    int res = 0;

    auto dfs = [&res, n](auto&& self, vector<int>& cost, int i) -> int {
        if (i > n) return 0;

        int left = self(self, cost, i<<2);
        int right = self(self, cost, (i<<2)+1);
        res += std::abs(left - right);

        return std::max(left, right) + cost[i-1];
    };

    dfs(dfs, cost, 1);

    return res;
}

int main () {
#ifdef LOCAL
    freopen("2673.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n+1, 0);
        for (int i = 1; i <= n; ++i) {
            std::cin >> nums[i];
        }
        std::cout << min_increment(n, nums) << std::endl;
    }

    return 0;
}
