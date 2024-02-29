#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using std::vector, std::string;

string add_strings(string s1, string s2)
{
    std::reverse(s1.begin(), s1.end());
    std::reverse(s2.begin(), s2.end());

    int m = s1.size();
    int n = s2.size();

    int t = std::min(m, n);

    string res {""};
    int c = 0;
    for (int i = 0; i < t; ++i) {
        int x = s1[i] - '0';
        int y = s2[i] - '0';
        int s = x + y + c;
        c = s / 10;
        res.push_back(s % 10 + '0');
    }

    auto it = s1.begin();
    auto end = s1.end();
    if (t == m) {
        it = s2.begin() + t;
        end = s2.end();
    } else {
        it = s1.begin() + t;
        end = s1.end();
    }

    while (it != end) {
        int x = *it - '0';
        int s = x + c;
        c = s / 10;
        res.push_back(s % 10 + '0');
        it++;
    }

    if (c != 0) res.push_back(c + '0');

    std::reverse(res.begin(), res.end());

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0415.in", "r", stdin);
#endif
    string s1 {""};
    string s2 {""};
    while (std::cin >> s1 >> s2) {
        std::cout << add_strings(s1, s2) << std::endl;
    }

    return 0;
}
