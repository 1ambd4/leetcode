#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

// [1,3] [2,6] [8,10]
vector<vector<int>> merge(vector<vector<int>>& intervals)
{
    int n = intervals.size();

    std::sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) -> bool {
            return a[0] < b[0];
    });

    vector<vector<int>> res;

    for (int i = 0, j = 0; i < n; i = j) {
        int l = intervals[i][0];
        int r = intervals[i][1];
        if (i == n - 1) {
            res.push_back({l, r});
        }

        for (j = i + 1; j < n; ++j) {
            int u = intervals[j][0];
            int v = intervals[j][1];

            if (l <= u && u <= r) {
                l = std::min(l, u);
                r = std::max(r, v);
                if (j == n - 1) {
                    res.push_back({l, r});
                }
            } else {
                res.push_back({l, r});
                break;
            }
        }
    }

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0056.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<vector<int>> intervals(n, vector<int>(2, 0));
        for (int i = 0; i < n; ++i) {
            std::cin >> intervals[i][0] >> intervals[i][1];
        }
        vector<vector<int>> res = merge(intervals);
        std::cout << "[";
        for (const auto es : res) {
            std::cout << "[" << es[0] << "," << es[1] << "] ";
        }
        std::cout << "]" << std::endl;
    }

    return 0;
}
