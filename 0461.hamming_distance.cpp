#include <iostream>

int hamming_distance(int x, int y)
{
    int res = 0;
    for (int i = 0; i < 32; ++i) {
        int u = x & 1;
        int v = y & 1;
        res += u ^ v;

        x >>= 1;
        y >>= 1;
    }
    return res;
}

int main () {
#ifdef LOCAL
    freopen("0461.in", "r", stdin);
#endif
    int m = 0, n = 0;
    while (std::cin >> m >>  n) {
        std::cout << hamming_distance(m, n) << std::endl;
    }
    return 0;
}
