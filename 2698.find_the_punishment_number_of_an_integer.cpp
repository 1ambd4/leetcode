#include <iostream>

int punishment_number(int n)
{
    // judge(v, i): 能否把 v 拆分成数值之和为 i 的子串
    auto judge = [](auto&& self, int v, int i) -> bool {
        // base case
        if (v == i) return true;
        if (v <= i) return false;

        // 显然对于当前层来说，可能的情况就是对所有位做切分
        for (int d = 10; d <= v; d *= 10) {
            if (self(self, v / d, i - (v % d))) {
                return true;
            }
        }

        return false;
    };

    int res = 0;
    for (int i = 1; i <= n; ++i) {
        if (judge(judge, i * i, i)) {
            res += i * i;
        }
    }
    return res;
}

int main()
{
#ifdef LOCAL
    freopen("2698.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        std::cout << punishment_number(n) << std::endl;
    }
    return 0;
}
