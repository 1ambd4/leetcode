#include <iostream>
#include <vector>

using std::vector;

// 可以发现朴素方法需要三次遍历
// 一次找左边最大，一次找右边最大，一次计算
// 但实际上，只需要一次即可
int trap(vector<int>& h)
{
    int n = h.size();

    int l = 0, r = n - 1;
    int ml = 0, mr = 0;

    int res = 0;

    while (l < r) {
        ml = std::max(ml, h[l]);
        mr = std::max(mr, h[r]);

        if (h[l] < h[r]) {
            res += ml - h[l];
            ++l;
        } else {
            res += mr - h[r];
            --r;
        }
    }

    return res;
}


// 朴素的思想是找到左右最大高度
// 那么两者中较小的减去当前高度，即为当前可接雨水
int _trap(vector<int>& h)
{
    int n = h.size();
    vector<int> l(n, 0), r(n, 0);

    l[0] = h[0], r[n-1] = h[n-1];
    for (int i = 1; i < n; ++i) {
        l[i] = std::max(l[i-1], h[i]);
    }
    for (int i = n - 2; i >= 0; --i) {
        r[i] = std::max(r[i+1], h[i]);
    }

    int res = 0;

    for (int i = 0; i < n; ++i) {
        res += std::min(l[i], r[i]) - h[i];
    }

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0042.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> h(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> h[i];
        }
        std::cout << trap(h) << std::endl;
    }
    return 0;
}
