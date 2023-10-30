#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

int h_index(vector<int>& citations)
{
    int n = citations.size();

    int l = 0, r = n - 1;
    while (l <= r) {
        int m = (l + r) >> 1;
        int h = n - m;
        if (citations[m] >= h) {
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    return n - l;
}

// h 指数：有 h 篇论文至少被引用了 h 次
// 找到第一个 n - i <= citations[i] 的 i
// 要考虑的边界条件好多啊
// 但也还好，因为很定势的就是考虑两个极端
// 即 l == 0 和 l == n - 1
int _h_index(vector<int>& citations)
{
    int n = citations.size();

    int l = 0, r = n - 1;
    while (l < r) {
        int m = (l + r) >> 1;
        int h = n - m;
        if (citations[m] >= h) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    if (l == 0 && citations[0] > 0) return n;
    return l != n - 1 ? n - l : (citations[l] > 0 ? 1 : 0);
}

int main()
{
#ifdef LOCAL
    freopen("0275.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        std::vector<int> citations(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> citations[i];
        }
        std::cout << h_index(citations) << std::endl;
    }
    return 0;
}
