#include <cstdio>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using std::string, std::vector;

vector<int> find_anagrams(string s, string p)
{
    int n = s.size(), m = p.size();
    int l = 0, r = 0;
    int valid = 0;

    std::unordered_map<char, int> w;
    std::unordered_map<char, int> need;

    for (const auto c: p) need[c]++;

    vector<int> res;

    while (r < n) {
        // 扩张左边界
        char c = s[r];
        if (need.count(c)) {
            w[c]++;
            if (w[c] == need[c]) ++valid;
        }
        r++;

        // 收缩右边界
        // while (valid == need.size()) {
        //     if (r - l == p.size()) {
        // 这么写似乎更好理解一点
        // 只有当字符串长度大于等于匹配串长度的时候
        // 才有可能出现答案，因而这时候就尝试着去收缩左边界
        while (r - l >= p.size()) {
            if (valid == need.size()) {
                res.push_back(l);
            }

            char c = s[l];
            ++l;
            if (need.count(c)) {
                if (w[c] == need[c]) {
                    --valid;
                }
                w[c]--;
            }
        }
    }

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0438.in", "r", stdin);
#endif
    string s, p;
    while (std::cin >> s >> p) {
        vector<int> res = find_anagrams(s, p);
        for (int i = 0; i < res.size(); ++i) {
            printf(",%d" + !i, res[i]);
        }
        printf("\n");
    }

    return 0;
}
