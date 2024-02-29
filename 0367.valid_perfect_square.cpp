#include <iostream>

// 二分
bool is_perfect_square(int n)
{
    long long l = 0;
    long long r = n;

    while (l < r) {
        long long m = (l + r + 1) >> 1;
        if (m * m <= n) l = m;
        else r = m - 1;
    }

    return l * l == n;
}

// 1 + 3 + 5 + .. + (2n-1) = n^2
// 即完全平方数必然是前 n 个连续奇数的和
bool _is_perfect_square(int n)
{
    if (n == 1) return true;
    long long m = 0;
    for (int i = 1; i <= n/2 + 1; i += 2) {
        m += i;
        if (n == m) return true;
    }
    return false;
}

int main () {
#ifdef LOCAL
    freopen("0367.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        std::cout << is_perfect_square(n) << std::endl;
    }

    return 0;
}
