#include <iostream>

int dist_money(int n, int c)
{
    if (n < c) return -1;
    if (n < c + 7) return 0;

    n -= c;
    int m = n / 7;
    int r = n % 7;

    if (r == 3 && c - m == 1) m -= 1;
    if (m > c || (m == c && r != 0)) return c - 1;
    return m;
}

int main()
{
#ifdef LOCAL
    freopen("2591.in", "r", stdin);
#endif
    int n = 0, c = 0;
    while (std::cin >> n >> c) {
        std::cout << dist_money(n, c) << std::endl;
    }
    return 0;
}
