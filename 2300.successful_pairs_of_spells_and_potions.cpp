#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

#include "leetcode.h"

using std::vector;

vector<int> successful_pairs(vector<int>& spells, vector<int>& potions, long long success)
{
    int m = spells.size();
    int n = potions.size();

    auto check = [&spells, &potions, success](int k, int m) -> bool {
        return spells[k] * 1l * potions[m] >= success;
    };

    std::sort(potions.begin(), potions.end(), std::less<int>());

    vector<int> res;

    for (int i = 0; i < m; ++i) {
        int l = 0, r = n - 1;
        while (l < r) {
            int m = (l + r) >> 1;
            if (check(i, m)) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        // [l, r] 的搜索区间有一点麻烦的就是
        // 需要判断一下两端的情况
        // 当然，正常情况下只需要判断一边就成
        // 比如这里找左边界
        // 那么只需要判断 l == n - 1 的时候究竟是存在一个满足还是都不满足
        if (l == n - 1 && !check(i, l)) {
            res.push_back(0);
        } else {
            res.push_back(n - l);
        }
    }

    return res;
}

int main () {
#ifdef LOCAL
    freopen("2300.in", "r", stdin);
#endif
    int m = 0, n = 0, k = 0;
    while (std::cin >> m >> n >> k) {
        vector<int> spells(m, 0);
        vector<int> potions(n, 0);

        for (int i = 0; i < m; ++i) {
            std::cin >> spells[i];
        }
        for (int i = 0; i < n; ++i) {
            std::cin >> potions[i];
        }

        std::cout << successful_pairs(spells, potions, k) << std::endl;
    }
    return 0;
}
