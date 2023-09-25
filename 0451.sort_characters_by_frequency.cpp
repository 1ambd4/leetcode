#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>

#include "leetcode.h"

using std::string, std::vector, std::pair, std::unordered_map;

string frequency_sort(string s)
{
    unordered_map<char, int> m;
    for (auto c : s) m[c]++;
    std::sort(s.begin(), s.end(), [&](const char a, const char b) {
            return m[a] == m[b] ? a > b : m[a] > m[b];
            });
    return s;
}

string _frequency_sort(string s)
{
    string res {""};

    vector<pair<int, int>> cnt(62, pair<int, int>(0, 0));
    for (int i = 0; i < 62; ++i) {
        cnt[i].first = i;
    }

    for (const auto c : s) {
        if (c >= '0' && c <= '9') {
            ++cnt[c - '0'].second;
        } else if (c >= 'A' && c <= 'Z') {
            ++cnt[c - 'A' + 10].second;
        } else if (c >= 'a' && c <= 'z') {
            ++cnt[c - 'a' + 36].second;
        }
    }

    auto cmp = [](pair<int, int>& a, pair<int, int>& b) -> bool {
        return a.second > b.second;
    };
    std::sort(cnt.begin(), cnt.end(), cmp);


    for (const auto e : cnt) {
        if (e.second == 0) continue;

        if (e.first < 10) {
            res.append(e.second, e.first + '0');
        } else if (e.first < 36) {
            res.append(e.second, e.first - 10 + 'A');
        } else {
            res.append(e.second, e.first - 36 + 'a');
        }
    }

    return res;
}

int main()
{
#ifdef LOCAL
    freopen("0451.in", "r", stdin);
#endif
    string s {""};
    while (std::cin >> s) {
        std::cout << frequency_sort(s) << std::endl;
    }
    return 0;
}

