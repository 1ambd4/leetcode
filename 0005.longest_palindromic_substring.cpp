#include <iostream>
#include <string>

using std::string;

// 中心扩散法
string longest_palindrome(string s)
{
    int n = s.size();
    string res {""};

    auto palindrome = [&res, n](string& s, int l, int r) -> void {
        while (l >= 0 && r < n && s[l] == s[r]) {
            --l;
            ++r;
        }
        string t = s.substr(l+1, r-l-1);
        if (t.size() > res.size()) res = t;
    };

    for (int i = 0; i < n; ++i) {
        // 奇偶性讨论
        palindrome(s, i, i);
        palindrome(s, i, i+1);
    }

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0005.in", "r", stdin);
#endif
    string s;
    while (std::cin >> s) {
        std::cout << longest_palindrome(s) << std::endl;
    }

    return 0;
}
