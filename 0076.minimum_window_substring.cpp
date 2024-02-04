#include <cstdio>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>

using std::string;

string min_window(string s, string t)
{
    int n = s.size();

    int l = 0;
    int r = 0;

    std::unordered_map<char, int> window;
    std::unordered_map<char, int> need;
    int valid = 0;

    for (const auto c : t) need[c]++;

    // 子串的起始坐标
    int res = 0;
    int len = std::numeric_limits<int>::max();

    while (r < n) {
        // 右扩
        char c = s[r];
        if (need.count(c)) {
            window[c]++;
            if (window[c] == need[c]) ++valid;
        }
        r++;

        while (valid == need.size()) {
            // 更新答案
            if (r - l < len) {
                res = l;
                len = r - l;
            }

            // 左缩
            char c = s[l];
            if (need.count(c)) {
                if (window[c] == need.count(c)) --valid;
                window[c]--;
            }
            l++;
        }
    }

    return len == std::numeric_limits<int>::max() ? "" : s.substr(res, len);
}

string _min_window(string s, string t)
{
    std::unordered_map<char, int> window;
    std::unordered_map<char, int> need;

    for (const auto c : t) need[c]++;

    int l = 0, r = 0;
    int n = s.size();
    int v = 0;
    int res = 0, len = std::numeric_limits<int>::max();

    while (r < n) {
        char c = s[r];
        if (need.count(c)) {
            window[c]++;
            if (window[c] == need[c]) v++;
        }
        r++;

        while (v == need.size()) {
            if (r - l < len) {
                res = l;
                len = r - l;
            }

            char c = s[l];
            if (need.count(c)) {
                if (window[c] == need[c]) v--;
                window[c]--;
            }
            l++;
        }
    }

    return len == std::numeric_limits<int>::max() ? "" : s.substr(res, len);
}

int main () {
#ifdef LOCAL
    freopen("0076.in", "r", stdin);
#endif
    string s, t;
    while (std::cin >> s >> t) {
        std::cout << min_window(s, t) << std::endl;
    }

    return 0;
}
