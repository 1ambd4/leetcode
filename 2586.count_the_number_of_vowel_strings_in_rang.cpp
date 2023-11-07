#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using std::string, std::vector;

int vowel_strings(vector<string>& words, int left, int right)
{
    int res = 0;

    for (int i = left; i <= right; ++i) {
        if (words[i].find_first_of("aeiou") == 0 &&
            words[i].find_last_of("aeiou") == words[i].size() - 1) {
            res++;
        }
    }

    return res;
}

// a e i o u
int _vowel_strings(vector<string>& words, int left, int right)
{
    auto is_vowel = [](const char c) -> bool {
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            return true;
        }
        return false;
    };

    auto check = [&is_vowel](const string& word) -> bool {
        int n = word.size();
        if (is_vowel(word[0]) && is_vowel(word[n-1])) {
            return true;
        }
        return false;
    };

    int res = 0;
    for (int i = left; i <= right; ++i) {
        if (check(words[i])) {
            res++;
        }
    }
    return res;
}


int main()
{
#ifdef LOCAL
    freopen("2586.in", "r", stdin);
#endif
    int n = 0, left = 0, right = 0;
    while (std::cin >> n) {
        std::cin >> left >> right;
        vector<string> words(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> words[i];
        }
        std::cout << vowel_strings(words, left, right) << std::endl;
    }
    return 0;
}
