#include <iostream>
#include <vector>

long long ways_to_buy_pen_and_pencil(int total, int cost1, int cost2)
{
    long long res = 0;
    int cnt = total / cost1;

    for (int i = 0; i <= cnt; ++i) {
        res += (total - cost1 * i) / cost2 + 1;
    }

    return res;
}

int main()
{
#ifdef LOCAL
    freopen("2240.in", "r", stdin);
#endif
    int n = 0, c1 = 0, c2 = 0;
    while (std::cin >> n >> c1 >> c2) {
        std::cout << ways_to_buy_pen_and_pencil(n, c1, c2) << std::endl;
    }
    return 0;
}
