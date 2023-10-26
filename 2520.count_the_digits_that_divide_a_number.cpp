#include <iostream>
#include <string>
#include <vector>

int count_digits(int n)
{
    std::vector<int> cnt(10, 0);

    int t = n;
    while (t > 0) {
        int r = t % 10;
        cnt[r]++;
        t /= 10;
    }

    int res = 0;
    for (int i = 1; i < 10; ++i) {
        if (n % i == 0) {
            res += cnt[i];
        }
    }

    return res;
}

int _count_digits(int n)
{
    std::string s = std::to_string(n);

    int res = 0;
    for (const auto c : s) {
        if (n % (c - '0') == 0) {
            ++res;
        }
    }

    return res;
}

int main()
{
#ifdef LOCAL
    freopen("2520.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        std::cout << count_digits(n) << std::endl;
    }
    return 0;
}
