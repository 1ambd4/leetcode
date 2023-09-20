#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>

#include "leetcode.h"

using std::vector;

vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& new_interval) {
    vector<vector<int>> res;

    for (auto& interval : intervals) {
        int a1 = interval[0];
        int a2 = interval[1];

        int b1 = new_interval[0];
        int b2 = new_interval[1];

        // 区间不重叠直接扔进答案里
        if (a2 < b1 || b2 < a1) {
            res.emplace_back(interval);
        } else {
        // 否则需要进行合并
            new_interval[0] = std::min(a1, b1);
            new_interval[1] = std::max(a2, b2);
        }
    }


    res.push_back(new_interval);

    std::sort(res.begin(), res.end(), [](vector<int>& a, vector<int>& b) {
        return a[0] < b[0];
    });

    return res;
}

int main()
{
#ifdef LOCAL
    freopen("0057.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> new_interval(2, 0);
        std::cin >> new_interval[0] >> new_interval[1];

        vector<vector<int>> intervals(n, vector<int>(2, 0));
        for (int i = 0; i < n; ++i) {
            std::cin >> intervals[i][0] >> intervals[i][1];
        }

        vector<vector<int>> res = insert(intervals, new_interval);

        std::cout << res << std::endl;
    }
    return 0;
}
