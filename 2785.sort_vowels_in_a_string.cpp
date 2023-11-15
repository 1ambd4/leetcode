#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::string, std::vector;

string sort_vowels(string s)
{
    vector<char> vowels;
    for (const auto c : s) {
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
            vowels.push_back(c);
        }
    }
    std::sort(vowels.begin(), vowels.end(), [](char a, char b) -> bool {
            return a < b;
        });

    string res {""};
    int idx = 0;
    for (const auto c : s) {
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
            res.push_back(vowels[idx++]);
        } else {
            res.push_back(c);
        }
    }

    return res;
}

int main () {
#ifdef LOCAL
    freopen("2785.in", "r", stdin);
#endif
    std::string s;
    while (std::cin >> s) {
        std::cout << sort_vowels(s) << std::endl;
    }

    return 0;
}
