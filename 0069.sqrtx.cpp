#include <iostream>

int my_sqrt(int x)
{
    int l = 0;
    int r = x;
    while (l < r) {
        int m = (l + r + 1L) >> 1;
        if (m <= x * 1.0 / m) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    return l;
}

int main () {
#ifdef LOCAL
    freopen("0069.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        std::cout << my_sqrt(n) << std::endl;
    }

    return 0;
}
