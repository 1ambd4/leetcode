#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using std::string, std::vector, std::unordered_map;

vector<vector<string>> group_anagrams(vector<string>& strs)
{
    unordered_map<string, vector<string>> m;
    for (const auto& str : strs) {
        string mask(26, (char)0);
        for (const char c : str) {
            int i = c - 'a';
            mask[i] += 1;
        }
        m[mask].push_back(str);
    }

    vector<vector<string>> res;

    for (const auto& [k, v] : m) {
        res.push_back(vector<string>());
        for (const auto& s : v) {
            res.back().push_back(s);
        }
    }

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0049.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<string> strs(n, "");
        for (int i = 0; i < n; ++i) {
            std::cin >> strs[i];
        }
        vector<vector<string>> res = group_anagrams(strs);
        for (const auto& es : res) {
            for (const auto& e : es) {
                std::cout << e << ", ";
            }
            std::cout << std::endl;
        }
    }

    return 0;
}
