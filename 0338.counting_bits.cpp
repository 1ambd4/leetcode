#include <iostream>
#include <vector>

#include "leetcode.h"

using std::vector;

vector<int> count_bits(int n)
{
    vector<int> res(n+1, 0);
    for (int i = 0; i <= n; ++i) {
        int t = i;
        while (t > 0) {
            res[i] += t & 1;
            t >>= 1;
        }
    }
    return res;
}

vector<int> _count_bits(int n)
{
    vector<int> res(n+1, 0);
    for (int i = 0; i <= n; ++i) {
        res[i] = __builtin_popcount(i);
    }
    return res;
}

int main () {
#ifdef LOCAL
    freopen("0338.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> res = count_bits(n);
        std::cout << res << std::endl;
    }

    return 0;
}
