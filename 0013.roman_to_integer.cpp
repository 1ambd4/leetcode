#include <iostream>
#include <string>
#include <unordered_map>

using std::string;

int roman_to_int(string s)
{
    std::unordered_map<char, int> m {
        {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
        {'C', 100}, {'D', 500}, {'M', 1000},
    };

    int res = 0;

    for (int i = 0, n = s.size(); i < n - 1; ++i) {
        int cur = m[s[i]];
        int nxt = m[s[i+1]];
        if (cur < nxt) {
            res -= cur;
        } else {
            res += cur;
        }
    }

    res += m[s[s.size()-1]];

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0013.in", "r", stdin);
#endif
    string s;
    while (std::cin >> s) {
        std::cout << roman_to_int(s) << std::endl;
    }

    return 0;
}
