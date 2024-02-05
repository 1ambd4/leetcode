#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

int find_min_arrow_shots(vector<vector<int>>& points)
{
    // 按照 x1 升序排序
    std::sort(points.begin(), points.end(), [](vector<int>& a, vector<int>& b) -> bool {
        return a[0] < b[0];
    });

    int res = 0;

    // 又是滑动窗口么
    int r = 0;

    int x1 = points[0][0];
    int x2 = points[0][1];

    // 同样的，为了不处理最后的尾巴部分，直接往 points 里插入一些无效数据
    // 我是想仍一个 (-x1, -x2) 的
    // 但测试数据：[[-2147483648,2147483647]]
    // 不做人垃
    // points.push_back({-x1, -x2});
    // 完全找不到无效数据
    int n = points.size();

    // 考虑到这题的处理逻辑很简单，就只是 res++ 罢了
    // 那就直接常规的方法吧
    // 跑完之后，让 res++ 再返回

    if (n == 1) return 1;

    while (r < n) {

        int y1 = points[r][0];
        int y2 = points[r][1];

        // 和之前的有重叠
        // 那么计算区间的交集
        if (x1 <= y1 && y1 <= x2) {
            x1 = std::max(x1, y1);
            x2 = std::min(x2, y2);
        } else {
            // 如果没有重叠的，那么就需要更新答案
            ++res;
            x1 = y1;
            x2 = y2;
        }

        ++r;
    }

    // points.pop_back();

    return res + 1;
}

int main () {
#ifdef LOCAL
    freopen("0452.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<vector<int>> nums(n, vector<int>(2, 0));
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i][0] >> nums[i][1];
        }
        std::cout << find_min_arrow_shots(nums) << std::endl;
    }

    return 0;
}
