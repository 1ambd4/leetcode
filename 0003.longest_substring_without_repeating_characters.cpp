#include <iostream>
#include <string>
#include <unordered_map>

using std::string;

// 莫名其妙的就过了
int length_of_longest_substring(string s)
{
    int n = s.size();
    int l = 0, r = 0;
    int res = 0;

    std::unordered_map<char, int> w;

    while (r < n) {
        // 扩张右边界
        int c = s[r];
        w[c]++;
        ++r;

        // 收缩左边界
        while (l < n && w[c] > 1) {
            w[s[l]]--;
            ++l;
        }

        res = std::max(res, r - l);
    }

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0003.in", "r", stdin);
#endif
    string s;
    while (std::cin >> s) {
        std::cout << length_of_longest_substring(s) << std::endl;
    }

    return 0;
}
