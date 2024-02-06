#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>

using std::vector, std::string;

// 背包问题变形，和找零钱类似
bool word_break(string s, vector<string>& dict)
{
    int n = s.size();

    // f[i]: 以 s[i] 结尾的字符串是否可以由 dict 拼出来
    vector<int> f(n+1, 0);
    f[0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (const auto& word : dict) {
            int m = word.size();
            if (i >= m && word == s.substr(i-m, m)) {
                f[i] |= f[i-m];
            }
        }
    }

    return f[n];
}

int main () {
#ifdef LOCAL
    freopen("0139.in", "r", stdin);
#endif
    int n = 0;
    string s;
    while (std::cin >> n >> s) {
        vector<string> nums(n, "");
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        std::cout << word_break(s, nums) << std::endl;
    }

    return 0;
}
