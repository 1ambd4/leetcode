#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <vector>

using std::vector;

// 贪心 + 前缀和
// 基于暴力法里提到的直觉
// 同时这种 sati[i] * 1 + sait[i] * 2 + ... + sait[i] * n 的方式
// 像极了前缀和
//
// 贪心少不了排序，看组数据
// -1 -8 0 5 -9 => 5 0 -1 -8 -9
// 前缀和：5 5 4 -4 -13
// 显然只要能使得前缀和大于 0 的都要加上去
int max_statisfaction(vector<int>& sati)
{
    int n = sati.size();

    std::sort(sati.begin(), sati.end(), [](const int a, const int b) {
        return a > b;
    });

    int res = 0;
    int pre = 0;
    for (int i = 0; i < n; ++i) {
        pre += sati[i];
        if (pre < 0) break;
        res += pre;
    }

    return res;
}

// 暴力
//
// 基于这么一种直觉
//     sati[i] > 0 的都得加上
//     sati[i] <= 0 的都有可能加上
// 那么先排序，然后枚举每一个 sati[i] < 0
// 看是否可以最大化结果
int _max_statisfaction(vector<int>& sati)
{
    int n = sati.size();
    int res = 0;

    std::sort(sati.begin(), sati.end(), std::less<int>());
    for (int i = 0; i < n; ++i) {
        if (res != 0 && sati[i] > 0) break;
        int tmp = 0, idx = 1;
        for (int j = i; j < n; ++j, ++idx) {
            tmp += sati[j] * idx;
        }
        res = std::max(res, tmp);
    }

    return res;
}

int main()
{
#ifdef LOCAL
    freopen("1402.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        std::vector<int> v(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> v[i];
        }
        std::cout << max_statisfaction(v) << std::endl;
    }
    return 0;
}
