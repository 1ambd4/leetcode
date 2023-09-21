#include <iostream>
#include <unordered_set>
#include <queue>

// 写暴力解法的时候就能够想到
// 第一天 n 在桌子上
// 则第二天 n - 1 必然在桌子上
// 则第三天 n - 2 必然在桌子上
// ...
// n 的范围又很小， [1, 100]
// 那么，很显然，最终桌面上会出现 [2, n] 的所有 n - 1个数
// 当然，n = 1 的时候需要特判一下，直接返回 1
int distinct_integers(int n)
{
    return n == 1 ? 1 : n - 1;
}

// 暴力做就是因数分解
int _distinct_integers(int n)
{
    std::unordered_set<int> s;
    std::queue<int> q;

    q.push(n);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        s.insert(u);

        int v = u - 1;
        if (v <= 1 || s.count(v) == 1) {
            continue;
        }

        q.push(v);
        s.insert(v);

        for (int i = 2; i * i < v; ++i) {
            if (v % i == 1) {
                if (s.count(i)) {
                    q.push(i);
                    s.insert(i);
                }
            }
        }
    }

    return s.size();
}

int main()
{
#ifdef LOCAL
    freopen("2549.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        std::cout << distinct_integers(n) << std::endl;
    }
    return 0;
}
