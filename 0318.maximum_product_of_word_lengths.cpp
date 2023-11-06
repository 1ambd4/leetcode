#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using std::vector, std::string, std::unordered_map;

int max_product(vector<string>& words)
{
    int n = words.size();
    // m: (mask, len)
    unordered_map<int, int> m;
    for (int i = 0; i < n; ++i) {
        int mask = 0;
        int len = words[i].length();
        for (const auto c: words[i]) {
            mask |= (1 << (c - 'a'));
        }
        m[mask] = std::max(m[mask], len);
    }

    int res = 0;
    for (const auto& [k1, v1] : m) {
        for (const auto& [k2, v2] : m) {
            if ((k1 & k2) == 0) {
                res = std::max(res, v1 * v2);
            }
        }
    }

    return res;
}

int _max_product(vector<string>& words)
{
    int n = words.size();
    vector<int> masks(n, 0);

    for (int i = 0; i < n; ++i) {
        for (const auto c : words[i]) {
            masks[i] |= (1 << (c - 'a'));
        }
    }

    int res = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if ((masks[i] & masks[j]) == 0) {
                int cur = words[i].length() * words[j].length();
                res = std::max(res, cur);
            }
        }
    }

    return res;
}

int main()
{
#ifdef LOCAL
    freopen("0318.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<string> words(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> words[i];
        }
        std::cout << max_product(words) << std::endl;
    }
    return 0;
}
