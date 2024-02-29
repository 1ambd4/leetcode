#include <iostream>
#include <vector>
#include <string>

using std::vector, std::string;

int longest_palindrome(string s)
{
    vector<int> cnt(52, 0);

    for (auto c : s) {
        if ('a' <= c && c <= 'z') {
            cnt[c-'a']++;
        } else if ('A' <= c && c <= 'Z') {
            cnt[c-'A'+26]++;
        }
    }

    int odd = 0;
    int res = 0;
    for (int i = 0; i < 52; ++i) {
        if (cnt[i] & 1) {
            odd = 1;
            res += cnt[i] - 1;
        } else {
            res += cnt[i];
        }
    }

    return res + odd;
}

int main () {
#ifdef LOCAL
    freopen("0409.in", "r", stdin);
#endif
    string s {""};
    while (std::getline(std::cin, s)) {
        std::cout << longest_palindrome(s) << std::endl;
    }

    return 0;
}
