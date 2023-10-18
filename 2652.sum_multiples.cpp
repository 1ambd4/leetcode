#include <iostream>

// AUBUC
// P(AUBUC) =
//   P(A) * P(B) * P(C) - P(A/\B) - P(A/\C) - P(B/\C) + P(A/\B/\C)
int sum_of_multiples(int n)
{
    // 等差数列求和
    // S = (n/i) * (i + n/i * i) / 2
    //   = (n/i) * i * (n/i + 1) / 2
    auto p = [n](int i) -> int {
        return (n / i) * i * (n / i + 1) / 2;
    };

    return p(3) + p(5) + p(7) - p(3*5) - p(3*7) - p(5*7) + p(3*5*7);
}

int _sum_of_multiples(int n)
{
    int res = 0;

    for (int i = 1; i <= n; ++i) {
        if (i % 3 == 0 || i % 5 == 0 || i % 7 == 0) {
            res += i;
        }
    }

    return res;
}

int main()
{
#ifdef LOCAL
    freopen("2652.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        std::cout << sum_of_multiples(n) << std::endl;
    }
}
