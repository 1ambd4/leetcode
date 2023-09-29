#include <iostream>
#include <vector>

#include "leetcode.h"

using std::vector;

bool can_place_flowers(vector<int>& f, int n)
{
    int m = f.size();

    for (int i = 0; i < m && n > 0; ) {
        // 因为不能有两朵相邻的花，所以遇到花就跳两格
        if (f[i] == 1) {
            i += 2;
        } else if (i == m - 1 || f[i+1] == 0) {
        // 因为遇花跳两格，且花不相邻
        // 故而遇到空格的时候，其前面一格定然是空格
        // 故而只需要判定下一格是否为空格即可
            --n;
            i += 2;
        } else {
            i += 3;
        }
    }

    return n <= 0;
}

bool _can_place_flowers(vector<int>& f, int n)
{
    int m = f.size();

    for (int i = 0; i < m; ++i) {
        if ((i == 0 || f[i-1] == 0) && f[i] == 0 && (i == m - 1 || f[i+1] == 0)) {
            --n;
            f[i] = 1;
        }
    }

    return n <= 0;
}

int main()
{
#ifdef LOCAL
    freopen("0605.in", "r", stdin);
#endif
    int m = 0, n = 0;
    while (std::cin >> m >> n) {
        vector<int> f(m, 0);
        for (int i = 0; i < m; ++i) {
            std::cin >> f[i];
        }
        std::cout << can_place_flowers(f, n) << std::endl;
    }
    return 0;
}

