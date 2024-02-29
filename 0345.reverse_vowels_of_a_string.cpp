#include <iostream>
#include <string>

using std::string;

string reverse_vowels(string s)
{
    int n = s.size();
    int l = 0;
    int r = n - 1;

    auto f = [](char c) -> bool {
        switch (c) {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
            case 'A':
            case 'E':
            case 'I':
            case 'O':
            case 'U':
                return true;
            default:
                return false;
        }
    };

    while (l < r) {
        while (l < r && !f(s[l])) ++l;
        while (l < r && !f(s[r])) --r;
        std::swap(s[l], s[r]);
        ++l; --r;
    }

    return s;
}

int main () {
#ifdef LOCAL
    freopen("0345.in", "r", stdin);
#endif
    string s {""};
    while (std::getline(std::cin, s)) {
        std::cout << reverse_vowels(s) << std::endl;
    }

    return 0;
}
