#include <iostream>
#include <string>
#include <vector>

using std::vector, std::string;

int longest_common_subsequence(string& s1, string& s2)
{
    int m = s1.size();
    int n = s2.size();

    // f[i][j]：s1[0..i] 和 s2[0..j] 的 LCS
    vector<vector<int>> f(m+1, vector<int>(n+1, 0));

    // 对于 s1 中的每个字符，都需要和 s2 中的字符比较
    // 如果 s1[i] == s2[j] 的话，则说明 s1[i] 和 s2[j] 都是 LCS 中的
    // 那么，f[i][j] = f[i-1][j-1] + 1
    // 如果 s2[i] != s2[j] 的话，则说明 s1[i] 或 s2[j] 不是 LCS 中的
    // 那么，要么 s1[i] 不是，要么 s2[j] 不是
    // 所以 f[i][j] = std::max(f[i-1][j], f[i][j-1])
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s1[i-1] == s2[j-1]) {
                f[i][j] = f[i-1][j-1] + 1;
            } else {
                f[i][j] = std::max(f[i-1][j], f[i][j-1]);
            }
        }
    }

    return f[m][n];
}

int main () {
#ifdef LOCAL
    freopen("1143.in", "r", stdin);
#endif
    std::string s1 {""};
    std::string s2 {""};
    while (std::cin >> s1 >> s2) {
        std::cout << longest_common_subsequence(s1, s2) << std::endl;
    }

    return 0;
}
