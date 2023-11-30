#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <array>

using std::string, std::array;

bool close_strings(string s1, string s2)
{
    // 相近的字符串值字符集相同，排序后的词频率数组相同
    int charset1 = 0;
    int charset2 = 0;

    array<int, 26> cnt1 {0};
    array<int, 26> cnt2 {0};

    std::for_each(s1.begin(), s1.end(), [&cnt1, &charset1](char c) {
        charset1 |= 1 << (c - 'a');
        cnt1[c - 'a']++;
    });
    std::for_each(s2.begin(), s2.end(), [&cnt2, &charset2](char c) {
        charset2 |= 1 << (c - 'a');
        cnt2[c - 'a']++;
    });

    if (charset1 != charset2) return false;

    std::sort(cnt1.begin(), cnt1.end(), std::greater<int>());
    std::sort(cnt2.begin(), cnt2.end(), std::greater<int>());

    for (int i = 0; i < 26; ++i) {
        if (cnt1[i] != cnt2[i]) {
            return false;
        }
    }
    return true;
}

int main () {
#ifdef LOCAL
    freopen("1657.in", "r", stdin);
#endif
    string s1, s2;
    while (std::cin >> s1 >> s2) {
        std::cout << close_strings(s1, s2) << std::endl;
    }

    return 0;
}
