#include <iostream>
#include <vector>
#include <string>

using std::vector, std::string;

// f[i][j]：s1[0..i] 变换到 s2[0..j] 所需要的最少步骤数
//
// f[i-1][j-1]：替换操作
//      s1[0..i-1] 和 s2[0..j-1] 已经替换完成，那么 s1[0..i] 如何变换成 s2[0..j] 呢？
//      只能是做一次替换操作
// f[i][j-1]：  插入操作
//      s1[0..i] 和 s2[0..j-1] 已经变换完成，那么 s1[0..i] 如何变换成 s2[0..j] 呢？
//      这时候 s2 比 s1 多一个字符 s2[j]，那么需要一次插入操作
// f[i-1][j]：  删除操作
//      s1[0..i-1] 和 s2[0..j] 已经变换完成，那么 s1[0..i] 如何变换成 s2[0..j] 呢？
//      这时候 s1 比 s2 多一个字符 s1[i]，那么需要一次删除操作
//
int mini_distance(string& s1, string& s2)
{
    int m = s1.size();
    int n = s2.size();

    // f[i][j]：s1[0..i] 变换到 s2[0..j] 最少需要多少步
    vector<vector<int>> f(m+1, vector<int>(n+1, 0));

    // 初始化主要是为了 i = 0 和 j = 0 的情况吗
    // 那如果 i = 0，或者 j = 0 了
    // 拿 i = 0 来说，容易知道，f[0][j] = j，因为最少也得插入 j 个字符才能相等
    for (int i = 1; i <= m; ++i) f[i][0] = i;
    for (int j = 1; j <= n; ++j) f[0][j] = j;

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            // 相等就不操作了
            if (s1[i-1] == s2[j-1]) {
                f[i][j] = f[i-1][j-1];
            } else {
                // 否则在三种操作里选一种
                int a = f[i-1][j] + 1;    // 删除操作，问题变成 s1[0..i-1] 变换成 s2[0..j] 最少需要多少步
                int b = f[i][j-1] + 1;    // 插入操作，问题变成 s1[0..i] 变换成 s2[0..j-1] 最少需要多少步
                int c = f[i-1][j-1] + 1;  // 替换操作，无论当前总能匹配，问题变成 s1[0..i-1] 变换成 s2[0..j-1] 最少需要多少步
                f[i][j] = std::min(std::min(a, b), c);
            }
        }
    }

    return f[m][n];
}

int main () {
#ifdef LOCAL
    freopen("0072.in", "r", stdin);
#endif
    string s1 {""};
    string s2 {""};
    while (std::cin >> s1 >> s2) {
        std::cout << mini_distance(s1, s2) << std::endl;
    }

    return 0;
}
