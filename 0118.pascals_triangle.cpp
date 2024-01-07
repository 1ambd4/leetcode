#include <iostream>
#include <vector>

#include "leetcode.h"

using std::vector;

vector<vector<int>> generate(int rows)
{
    vector<vector<int>> res;
    res.push_back({1});
    if (rows == 1) return res;

    res.push_back({1, 1});
    if (rows == 2) return res;

    for (int i = 2; i < rows; ++i) {
        res.push_back({});
        res.back().push_back(1);
        vector<int> pre = res[i-1];
        for (int j = 1; j < pre.size(); ++j) {
            res.back().push_back(pre[j] + pre[j-1]);
        }
        res.back().push_back(1);
    }
    return res;
}

int main () {
#ifdef LOCAL
    freopen("0118.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<vector<int>> res = generate(n);
        std::cout << res << std::endl;
    }

    return 0;
}
