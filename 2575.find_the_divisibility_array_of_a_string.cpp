#include <iostream>
#include <vector>
#include <string>

#include "leetcode.h"

using std::vector, std::string;

// a = k1m + r1, b = k2m + r2
// => (a + b) mod m = (r1 + r2) mod m = (a mod m + b mod m) mod m
vector<int> divisibility_array(string word, int m)
{
    int n = word.size();
    vector<int> res(n, 0);

    long long temp = 0;
    for (int i = 0; i < n; ++i) {
        // 中间就可以取模了，防止爆 long long
        temp = (temp * 10 + (word[i] - '0')) % m;
        res[i] = (temp == 0);
    }

    return res;
}

// stoll 爆 long long 了
vector<int> _divisibility_array(string word, int m)
{
    int n = word.size();
    vector<int> res(n, 0);

    for (int i = 0; i < n; ++i) {
        long long temp = std::stoll(word.substr(0, i+1), 0);
        if (temp % m == 0) res[i] = 1;
    }

    return res;
}

int main () {
#ifdef LOCAL
    freopen("2575.in", "r", stdin);
#endif
    int n = 0;
    string s {""};
    while (std::cin >> n >> s) {
        vector<int> res = divisibility_array(s, n);
        std::cout << res << std::endl;
    }

    return 0;
}
