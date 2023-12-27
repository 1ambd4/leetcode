#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

int max_area(vector<int>& h)
{
    int l = 0, r = h.size() - 1;
    int res = 0;

    while (l < r) {
        res = std::max(res, std::min(h[l], h[r]) * (r - l));
        if (h[l] < h[r]) ++l;
        else --r;
    }

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0011.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> h(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> h[i];
        }
        std::cout << max_area(h) << std::endl;
    }

    return 0;
}
